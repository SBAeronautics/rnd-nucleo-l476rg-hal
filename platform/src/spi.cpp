#include "spi.hpp"

#include "stm32l4xx_ll_spi.h"

namespace {

constexpr std::uint8_t dummy_byte{0xFFU};

} // namespace

namespace platform {

SpiStatus Spi::transfer(const std::uint8_t* transmit,
                        std::uint8_t* receive,
                        std::size_t size) noexcept {
    if (LL_SPI_IsEnabled(instance_) == 0U) {
        return SpiStatus::not_enabled;
    }

    while (LL_SPI_IsActiveFlag_RXNE(instance_) != 0U) {
        static_cast<void>(LL_SPI_ReceiveData8(instance_));
    }

    for (std::size_t index{0U}; index < size; ++index) {
        if (!wait_for_transmit_empty()) {
            return SpiStatus::timeout;
        }

        const std::uint8_t transmit_byte{
            transmit != nullptr ? transmit[index] : dummy_byte};

        LL_SPI_TransmitData8(instance_, transmit_byte);

        if (!wait_for_receive_ready()) {
            return SpiStatus::timeout;
        }

        const std::uint8_t receive_byte{
            LL_SPI_ReceiveData8(instance_)};

        if (receive != nullptr) {
            receive[index] = receive_byte;
        }
    }

    if (!wait_until_idle()) {
        return SpiStatus::timeout;
    }

    return SpiStatus::ok;
}

bool Spi::wait_for_transmit_empty() const noexcept {
    std::uint32_t timeout{timeout_iterations};

    while (LL_SPI_IsActiveFlag_TXE(instance_) == 0U) {
        if (timeout == 0U) {
            return false;
        }

        --timeout;
    }

    return true;
}

bool Spi::wait_for_receive_ready() const noexcept {
    std::uint32_t timeout{timeout_iterations};

    while (LL_SPI_IsActiveFlag_RXNE(instance_) == 0U) {
        if (timeout == 0U) {
            return false;
        }

        --timeout;
    }

    return true;
}

bool Spi::wait_until_idle() const noexcept {
    std::uint32_t timeout{timeout_iterations};

    while (LL_SPI_IsActiveFlag_BSY(instance_) != 0U) {
        if (timeout == 0U) {
            return false;
        }

        --timeout;
    }

    return true;
}

} // namespace platform