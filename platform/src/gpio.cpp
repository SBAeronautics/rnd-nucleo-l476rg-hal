#include "gpio.hpp"

#include "stm32l4xx_ll_gpio.h"

namespace platform {

GpioOutput::GpioOutput(GPIO_TypeDef* port,
                       std::uint32_t pin,
                       ::ActiveLevel active_level = ::ActiveLevel::high)
    : port_{port}, pin_{pin}, active_level_{active_level} {}

GpioOutput::GpioOutput(GpioPin pin,
                       ::ActiveLevel active_level = ::ActiveLevel::high)
    : GpioOutput{pin.port, pin.pin, active_level} {}

void GpioOutput::set() noexcept {
    if (active_level_ == ::ActiveLevel::high) {
        LL_GPIO_SetOutputPin(port_, pin_);
        return;
    }

    LL_GPIO_ResetOutputPin(port_, pin_);
}

void GpioOutput::clear() noexcept {
    if (active_level_ == ::ActiveLevel::high) {
        LL_GPIO_ResetOutputPin(port_, pin_);
        return;
    }

    LL_GPIO_SetOutputPin(port_, pin_);
}

void GpioOutput::toggle() noexcept {
    LL_GPIO_TogglePin(port_, pin_);
}

void GpioOutput::write(bool active) noexcept {
    if (active) {
        set();
        return;
    }

    clear();
}

bool GpioInput::read() const noexcept {
    const bool pin_is_high{
        LL_GPIO_IsInputPinSet(port_, pin_) != 0U};

    if (active_level_ == ::ActiveLevel::high) {
        return pin_is_high;
    }

    return !pin_is_high;
}

} // namespace platform
