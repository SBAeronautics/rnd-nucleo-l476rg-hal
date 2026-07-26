#ifndef PLATFORM_INC_DIGITAL_GPIO_HPP
#define PLATFORM_INC_DIGITAL_GPIO_HPP

#include "digital_input.hpp"
#include "digital_output.hpp"
#include "stm32l4xx.h"
#include <cstdint>

namespace platform {

class GpioOutput final : public DigitalOutput {
  public:
    constexpr GpioOutput(GPIO_TypeDef* port, std::uint32_t pin, bool active_high = true) noexcept
        : port_{port}, pin_{pin}, active_high_{active_high} {}

    void set() noexcept override;
    void clear() noexcept override;
    void toggle() noexcept override;
    void write(bool active) noexcept override;

  private:
    GPIO_TypeDef* port_;
    std::uint32_t pin_;
    bool active_high_;
};

class GpioInput final : public DigitalInput {
  public:
    constexpr GpioInput(GPIO_TypeDef* port, std::uint32_t pin, bool active_high = true) noexcept
        : port_{port}, pin_{pin}, active_high_{active_high} {}

    [[nodiscard]]
    bool read() const noexcept override;

  private:
    GPIO_TypeDef* port_;
    std::uint32_t pin_;
    bool active_high_;
};

} // namespace platform

#endif // PLATFORM_INC_DIGITAL_GPIO_HPP