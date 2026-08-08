#include "spi_device.hpp"

namespace platform {

SpiDevice::SpiDevice(Spi& spi,
                     GpioPin chip_select_pin,
                     ::ActiveLevel active_level) noexcept
    : spi_{spi}, chip_select_{chip_select_pin, active_level} {
}

void SpiDevice::initialize() noexcept {
    chip_select_.clear();
}

SpiStatus SpiDevice::transfer(const std::uint8_t* transmit,
                              std::uint8_t* receive,
                              std::size_t size) noexcept {
    ChipSelectGuard chip_select_guard{chip_select_};

    return spi_.transfer(transmit, receive, size);
}

SpiStatus SpiDevice::write_then_read(const std::uint8_t* command,
                                     std::size_t command_size,
                                     std::uint8_t* receive,
                                     std::size_t receive_size) noexcept {
    ChipSelectGuard chip_select_guard{chip_select_};

    SpiStatus status = spi_.transfer(command, nullptr, command_size);

    if (status != SpiStatus::ok) {
        return status;
    }

    return spi_.transfer(nullptr, receive, receive_size);
}

} // namespace platform