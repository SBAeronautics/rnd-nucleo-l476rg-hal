#ifndef PLATFORM_INC_SPI_DEVICE_HPP
#define PLATFORM_INC_SPI_DEVICE_HPP

#include "gpio.hpp"
#include "spi.hpp"

#include <cstddef>
#include <cstdint>

namespace {

/**
 * @brief Manages an SPI device chip-select signal for one transaction.
 *
 * Selects the device when constructed and deselects it when destroyed. The
 * guard should remain in scope for the entire SPI transaction.
 */
class ChipSelectGuard final {
  public:
    // -------------------------------------------------------------------------
    // Public Constructors and Destructors

    /**
     * @brief Selects the SPI device.
     *
     * @param chip_select Active-state-aware GPIO output controlling the
     * device chip-select signal.
     */
    explicit ChipSelectGuard(platform::GpioOutput& chip_select) noexcept
        : chip_select_{chip_select} {
        chip_select_.set();
    }

    /**
     * @brief Deselects the SPI device.
     */
    ~ChipSelectGuard() {
        chip_select_.clear();
    }

    /**
     * @brief Prevents copying of the chip-select guard.
     */
    ChipSelectGuard(const ChipSelectGuard&) = delete;

    /**
     * @brief Prevents copy assignment of the chip-select guard.
     */
    ChipSelectGuard& operator=(const ChipSelectGuard&) = delete;

  private:
    platform::GpioOutput& chip_select_;
};

} // namespace

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
     */
    SpiDevice(Spi& spi,
              GpioPin chip_select_pin,
              ::ActiveLevel active_level = ::ActiveLevel::low) noexcept;

    // -------------------------------------------------------------------------
    // Public Member Methods

    /**
     * @brief Sets the chip-select output to its inactive state.
     */
    void initialize() noexcept;

    /**
     * @brief Performs one complete SPI transaction.
     *
     * Chip select remains active for the entire transfer.
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
};

} // namespace platform

#endif // PLATFORM_INC_SPI_DEVICE_HPP