#ifndef PLATFORM_INC_I2C_HPP
#define PLATFORM_INC_I2C_HPP

#include "stm32l4xx.h"

#include <cstddef>
#include <cstdint>

namespace platform {

enum class I2cStatus : std::uint8_t {
    ok,
    not_initialized,
    timeout,
    nack,
    bus_busy,
    error
};

class I2c final {
  public:
    constexpr explicit I2c(I2C_TypeDef* instance) noexcept
        : instance_{instance} {
    }

    void initialize() noexcept;
    [[nodiscard]] bool initialized() const noexcept;

    [[nodiscard]] I2cStatus write(uint8_t address,
                                 const uint8_t* data,
                                 std::size_t size) noexcept;

    [[nodiscard]] I2cStatus read(uint8_t address,
                                uint8_t* data,
                                std::size_t size) noexcept;

    [[nodiscard]] I2cStatus write_then_read(uint8_t address,
                                            const uint8_t* tx_data,
                                            std::size_t tx_size,
                                            uint8_t* rx_data,
                                            std::size_t rx_size) noexcept;

  private:
    [[nodiscard]] bool wait_until_not_busy() const noexcept;
    [[nodiscard]] I2cStatus wait_for_flag(uint32_t mask,
                                          bool set) const noexcept;
    [[nodiscard]] I2cStatus wait_for_flag_or_nack(uint32_t mask,
                                                  bool set) const noexcept;

    I2C_TypeDef* instance_;
    bool initialized_{false};
    static constexpr std::uint32_t timeout_iterations{100000U};
};

} // namespace platform

#endif // PLATFORM_INC_I2C_HPP
