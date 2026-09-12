#ifndef PLATFORM_INC_UART_HPP
#define PLATFORM_INC_UART_HPP

#include "stm32l4xx.h"

#include <cstdint>
#include <string_view>

namespace platform {

/**
 * @brief Polling UART transmitter for an STM32 USART peripheral.
 */
class Uart final {
  public:
    // -------------------------------------------------------------------------
    // Public Constructors and Destructors

    /**
     * @brief Constructs a UART wrapper.
     *
     * @param instance USART peripheral instance.
     */
    constexpr explicit Uart(USART_TypeDef* instance) noexcept;

    // -------------------------------------------------------------------------
    // Public Member Methods

    /**
     * @brief Transmits one byte.
     *
     * @param byte Byte to transmit.
     */
    void write_byte(std::uint8_t byte) noexcept;

    /**
     * @brief Transmits a string.
     *
     * @param text Text to transmit.
     */
    void write(std::string_view text) noexcept;

    /**
     * @brief Transmits a string followed by a line ending.
     *
     * @param text Text to transmit.
     */
    void write_line(std::string_view text) noexcept;

  private:
    USART_TypeDef* instance_;
}; // class Uart

} // namespace platform

#endif // PLATFORM_INC_UART_HPP
