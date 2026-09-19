#ifndef PLATFORM_INC_SPI_DEVICE_HPP
#define PLATFORM_INC_SPI_DEVICE_HPP

#include "gpio.hpp"
#include "spi.hpp"

#include <cstddef>
#include <cstdint>

namespace platform {

/**
 * @brief Represents one device connected to a shared SPI bus.
 *
 * The device owns its chip-select output while referencing a shared SPI bus.
 */
class SpiDevice final {
  public:
    // -------------------------------------------------------------------------
    // Public Constructors and Destructors

    /**
     * @brief Constructs an SPI device.
     *
     * @param spi Shared SPI bus.
     * @param chip_select_pin GPIO pin connected to the device chip-select.
     * @param active_level Electrical level that selects the device.
     * @param chip_select_hold_us Minimum delay before releasing chip select
     * after the transfer returns. Requires the platform clock to be initialized.
     */
    SpiDevice(Spi& spi,
              GpioPin chip_select_pin,
              ::ActiveLevel active_level = ::ActiveLevel::low,
              std::uint32_t chip_select_hold_us = 0U) noexcept;

    // -------------------------------------------------------------------------
    // Public Member Methods

    /**
     * @brief Sets the chip-select output to its inactive state.
     */
    void initialize() noexcept;

    /**
     * @brief Performs one complete SPI transaction.
     *
     * Chip select remains active for the entire transfer and configured hold time.
     * On success, the hold starts after the SPI peripheral becomes idle.
     * A timeout still releases chip select after the hold; it does not guarantee
     * the peripheral is idle.
     *
     * @param transmit Transmit buffer, or nullptr to send dummy bytes.
     * @param receive Receive buffer, or nullptr to discard received bytes.
     * @param size Number of bytes to transfer.
     * @return Transfer status.
     */
    [[nodiscard]] SpiStatus transfer(const std::uint8_t* transmit,
                                     std::uint8_t* receive,
                                     std::size_t size) noexcept;

    /**
     * @brief Performs two transfers during one chip-select assertion.
     *
     * This is useful for register protocols where a command is followed by a
     * separate data phase.
     *
     * @param command Command buffer.
     * @param command_size Number of command bytes.
     * @param receive Receive buffer.
     * @param receive_size Number of bytes to receive.
     * @return Transfer status.
     */
    [[nodiscard]] SpiStatus write_then_read(const std::uint8_t* command,
                                            std::size_t command_size,
                                            std::uint8_t* receive,
                                            std::size_t receive_size) noexcept;

  private:
    Spi& spi_;
    GpioOutput chip_select_;
    std::uint32_t chip_select_hold_us_;
};

} // namespace platform

#endif // PLATFORM_INC_SPI_DEVICE_HPP