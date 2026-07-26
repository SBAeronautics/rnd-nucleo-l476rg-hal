#include "gpio.hpp"

#include "stm32l4xx_ll_gpio.h"

namespace platform {

void GpioOutput::set() noexcept {
    write(true);
}

void GpioOutput::clear() noexcept {
    write(false);
}

void GpioOutput::toggle() noexcept {
    LL_GPIO_TogglePin(port_, pin_);
}

void GpioOutput::write(bool active) noexcept {
    const bool pin_high = active_high_ ? active : !active;

    if (pin_high) {
        LL_GPIO_SetOutputPin(port_, pin_);
    } else {
        LL_GPIO_ResetOutputPin(port_, pin_);
    }
}

bool GpioInput::read() const noexcept {
    const bool pin_high = LL_GPIO_IsInputPinSet(port_, pin_) != 0U;

    return active_high_ ? pin_high : !pin_high;
}

} // namespace platform
