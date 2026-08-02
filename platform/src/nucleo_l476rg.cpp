#include "nucleo_l476rg.hpp"

#include "gpio.hpp"

extern "C" {
#include "gpio.h"
#include "system_stm32l4xx.h"
}

#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_utils.h"

namespace {

platform::GpioOutput status_led_device{GPIOA, LL_GPIO_PIN_5, true};

} // namespace

namespace platform::nucleo_l476rg {

void initialize() noexcept {
    // CubeMX-generated GPIO initialization.
    MX_GPIO_Init();

    // Determine the current CPU clock and configure SysTick for
    // a one-millisecond time base.
    SystemCoreClockUpdate();
    LL_Init1msTick(SystemCoreClock);

    // Start with the LED turned off.
    status_led_device.clear();
}

DigitalOutput& status_led() noexcept {
    return status_led_device;
}

void delay_ms(std::uint32_t milliseconds) noexcept {
    LL_mDelay(milliseconds);
}

} // namespace platform::nucleo_l476rg