#ifndef PLATFORM_INC_NUCLEO_L476RG_HPP
#define PLATFORM_INC_NUCLEO_L476RG_HPP

#include "digital_input.hpp"
#include "digital_output.hpp"
#include "stm32l4xx.h"
#include <cstdint>

#include "digital_output.hpp"

#include <cstdint>

namespace platform::nucleo_l476rg {

/**
 * @brief Initializes the NUCLEO-L476RG platform.
 *
 * Configures the system clock, SysTick time base, GPIO peripherals, status LED,
 * and user-button interrupt.
 *
 * @note Call this function once before accessing any board devices.
 */
void initialize() noexcept;

// -------------------------------------------------------------------------
// On-board LED (PA5)

/**
 * @brief Gets the onboard status LED.
 *
 * @return Reference to the digital output controlling the LED.
 */
DigitalOutput& status_led() noexcept;

// -------------------------------------------------------------------------
// On-board Button (PC13)

/**
 * @brief Gets the onboard user button.
 *
 * @return Reference to the digital input representing the user button.
 */
DigitalInput& user_button() noexcept;

/**
 * @brief Consumes a pending user-button press event.
 *
 * @return `true` when a button-press event was pending; otherwise `false`.
 *
 * @note A pending event is cleared when this function returns `true`.
 */
[[nodiscard]] bool take_user_button_press() noexcept;

namespace detail {

/**
 * @brief Services the user-button EXTI interrupt.
 *
 * Clears the EXTI13 pending flag and records a button-press event for the
 * application.
 *
 * @note Intended to be called only from `EXTI15_10_IRQHandler()`.
 */
void handle_user_button_exti() noexcept;

} // namespace detail

} // namespace platform::nucleo_l476rg

#endif // PLATFORM_INC_NUCLEO_L476RG_HPP