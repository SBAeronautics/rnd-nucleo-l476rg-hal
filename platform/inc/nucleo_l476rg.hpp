#ifndef PLATFORM_INC_NUCLEO_L476RG_HPP
#define PLATFORM_INC_NUCLEO_L476RG_HPP

#include "digital_input.hpp"
#include "digital_output.hpp"
#include "gpio.hpp"
#include "i2c.hpp"
#include "spi.hpp"
#include "stm32l4xx.h"
#include "uart.hpp"
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

// -------------------------------------------------------------------------
// SPI Interface (FIX)

/**
 * @brief Gets the SPI1 master peripheral.
 *
 * @return SPI1 master interface.
 */
Spi& spi1() noexcept;

// -------------------------------------------------------------------------
// I2C1 Interface (PB6, PB7)

/**
 * @brief Gets the I2C1 master peripheral.
 *
 * @return I2C1 master interface.
 */
I2c& i2c1() noexcept;

// -------------------------------------------------------------------------
// USART2 Interface (PA2, PA3)

/**
 * @brief Gets the UART connected to the ST-LINK virtual COM port.
 *
 * @return Reference to the UART used for console communication.
 */
Uart& console() noexcept;

/**
 * @brief Consumes a pending user-button press event.
 *
 * @return `true` when a button-press event was pending; otherwise `false`.
 *
 * @note A pending event is cleared when this function returns `true`.
 */
[[nodiscard]] bool take_user_button_press() noexcept;

namespace sockets {

/**
 * @brief 7-bit I2C address used by the board's temperature sensor socket.
 *
 * Update this value to match the board socket device installed on the board.
 */
extern const std::uint8_t temperature_sensor_address;

/**
 * @brief Register address in the socket device that exposes temperature.
 */
extern const std::uint8_t temperature_sensor_register;

} // namespace sockets

namespace pins {

/**
 * @brief PA4 GPIO pin used as the ADXL345 chip-select signal.
 */
extern const GpioPin pa4;

} // namespace pins

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