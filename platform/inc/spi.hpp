#ifndef PLATFORM_INC_SPI_HPP
#define PLATFORM_INC_SPI_HPP

#include "stm32l4xx.h"

#include <atomic>
#include <cstddef>
#include <cstdint>

namespace platform {

/**
 * @brief Result of an SPI transfer.
 */
enum class SpiStatus : std::uint8_t {
    ok,
    not_enabled,
    timeout
};

/**
 * @brief Polling full-duplex SPI master.
 */
class Spi final {
  public:
    // -------------------------------------------------------------------------
    // Public Constructors and Destructors

    /**
     * @brief Constructs an SPI master wrapper.
     *
     * @param instance STM32 SPI peripheral instance.
     */
    constexpr explicit Spi(SPI_TypeDef* instance) noexcept
        : instance_{instance} {
    }

    // -------------------------------------------------------------------------
    // Public Member Methods

    /**
     * @brief Performs a full-duplex SPI transfer.
     *
     * A null transmit buffer sends 0xFF for each byte. A null receive buffer
     * discards received data.
     *
     * @param transmit Transmit buffer, or nullptr.
     * @param receive Receive buffer, or nullptr.
     * @param size Number of bytes to transfer.
     * @return Transfer status.
     */
    [[nodiscard]] SpiStatus transfer(const std::uint8_t* transmit,
                                     std::uint8_t* receive,
                                     std::size_t size) noexcept;

  private:
    [[nodiscard]] bool wait_for_transmit_empty() const noexcept;

    [[nodiscard]] bool wait_for_receive_ready() const noexcept;

    [[nodiscard]] bool wait_until_idle() const noexcept;

    SPI_TypeDef* instance_;

    static constexpr std::uint32_t timeout_iterations{100000U};
};

} // namespace platform

#endif // PLATFORM_INC_SPI_HPP