#include "nucleo_l476rg.hpp"

#include "dma.hpp"
#include "gpio.hpp"
#include "spi.hpp"
#include "system_clock.hpp"
#include "uart.hpp"

extern "C" {
#include "dma.h"
#include "gpio.h"
#include "spi.h"
#include "system_stm32l4xx.h"
#include "usart.h"
}

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_utils.h"

#include <atomic>

namespace {

platform::GpioOutput status_led_device{GPIOA, LL_GPIO_PIN_5, ActiveLevel::high};
platform::GpioInput user_button_device{GPIOC, LL_GPIO_PIN_13, ActiveLevel::low};
platform::Spi spi1_device{SPI1};
platform::Uart console_device{USART2, platform::DmaChannel{DMA1, LL_DMA_CHANNEL_7}};

std::atomic_bool user_button_press_pending{false};

void cube_mx_init() noexcept {
    platform::clock::configure();

    /*
     * Required before configuring SYSCFG->EXTICR registers.
     */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();
    MX_SPI1_Init();
    LL_SPI_Enable(SPI1);

    SystemCoreClockUpdate();
    LL_Init1msTick(SystemCoreClock);

    /*
     * Remove stale pending state before enabling the interrupt.
     */
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn);

    NVIC_SetPriority(EXTI15_10_IRQn, 0U);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

} // namespace

namespace platform::nucleo_l476rg::pins {

const GpioPin pa4{GPIOA, LL_GPIO_PIN_4};

} // namespace platform::nucleo_l476rg::pins

namespace platform::nucleo_l476rg {

void initialize() noexcept {
    // CubeMX-generated clock initialization.
    cube_mx_init();

    // Start with the LED turned off.
    status_led_device.clear();
}

DigitalOutput& status_led() noexcept {
    return status_led_device;
}

DigitalInput& user_button() noexcept {
    return user_button_device;
}

Uart& console() noexcept {
    return console_device;
}

Spi& spi1() noexcept {
    return spi1_device;
}

bool take_user_button_press() noexcept {
    return user_button_press_pending.exchange(
        false,
        std::memory_order_relaxed);
}

namespace detail {

void handle_console_transmit_dma_complete() noexcept {
    console_device.handle_transmit_dma_complete();
}

void handle_console_transmit_dma_error() noexcept {
    console_device.handle_transmit_dma_error();
}

void handle_user_button_exti() noexcept {
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13) != 0U) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
        user_button_press_pending.store(
            true,
            std::memory_order_relaxed);
    }
}

} // namespace detail

} // namespace platform::nucleo_l476rg
