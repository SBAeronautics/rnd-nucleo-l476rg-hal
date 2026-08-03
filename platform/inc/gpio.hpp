#ifndef PLATFORM_INC_GPIO_HPP
#define PLATFORM_INC_GPIO_HPP

#include "digital_input.hpp"
#include "digital_output.hpp"
#include "stm32l4xx.h"
#include <cstdint>

namespace platform {

/**
 * @brief STM32 GPIO implementation of a digital output.
 */
class GpioOutput final : public DigitalOutput {
  public:
    // -------------------------------------------------------------------------
    // Public Constructors and Destructors

    /**
     * @brief Constructs a GPIO-backed digital output.
     *
     * @param port GPIO peripheral containing the output pin.
     * @param pin STM32 LL pin mask identifying the output pin.
     * @param active_high `true` when a high pin level represents the active
     * state; `false` when a low pin level represents the active state.
     */
    explicit constexpr GpioOutput(GPIO_TypeDef* port, std::uint32_t pin, bool active_high = true) noexcept
        : port_{port}, pin_{pin}, active_high_{active_high} {}

    // -------------------------------------------------------------------------
    // Public Member Methods

    /**
     * @brief Sets the GPIO output to its active state.
     */
    void set() noexcept override;

    /**
     * @brief Sets the GPIO output to its inactive state.
     */
    void clear() noexcept override;

    /**
     * @brief Toggles the GPIO output between its active and inactive states.
     */
    void toggle() noexcept override;

    /**
     * @brief Writes the requested logical state to the GPIO output.
     *
     * @param active `true` to activate the output; `false` to deactivate it.
     */
    void write(bool active) noexcept override;

  private:
    GPIO_TypeDef* port_;
    std::uint32_t pin_;
    bool active_high_;
}; // class GpioOutput

/**
 * @brief STM32 GPIO implementation of a digital input.
 */
class GpioInput final : public DigitalInput {
  public:
    // -------------------------------------------------------------------------
    // Public Constructors and Destructors

    /**
     * @brief Constructs a GPIO-backed digital input.
     *
     * @param port GPIO peripheral containing the input pin.
     * @param pin STM32 LL pin mask identifying the input pin.
     * @param active_high `true` when a high pin level represents the active
     * state; `false` when a low pin level represents the active state.
     */
    explicit constexpr GpioInput(GPIO_TypeDef* port, std::uint32_t pin, bool active_high = true) noexcept
        : port_{port}, pin_{pin}, active_high_{active_high} {}

    // -------------------------------------------------------------------------
    // Public Member Methods

    /**
     * @brief Reads the logical state of the GPIO input.
     *
     * @return `true` when the input is active; otherwise `false`.
     */
    [[nodiscard]] bool read() const noexcept override;

  private:
    GPIO_TypeDef* port_;
    std::uint32_t pin_;
    bool active_high_;
}; // class GpioInput

} // namespace platform

#endif // PLATFORM_INC_GPIO_HPP