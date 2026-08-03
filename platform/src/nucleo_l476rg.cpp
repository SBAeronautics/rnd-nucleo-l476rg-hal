#include "nucleo_l476rg.hpp"

#include "gpio.hpp"
#include "system_clock.hpp"

extern "C" {
#include "gpio.h"
#include "system_stm32l4xx.h"
}

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_utils.h"

#include <atomic>

namespace {

platform::GpioOutput status_led_device{
    GPIOA,
    LL_GPIO_PIN_5,
    true};

platform::GpioInput user_button_device{
    GPIOC,
    LL_GPIO_PIN_13,
    false};

std::atomic_bool user_button_press_pending{false};

void cube_mx_init() noexcept {
    platform::clock::configure();

    /*
     * Required before configuring SYSCFG->EXTICR registers.
     */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

    MX_GPIO_Init();

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

bool take_user_button_press() noexcept {
    return user_button_press_pending.exchange(
        false,
        std::memory_order_relaxed);
}

namespace detail {

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