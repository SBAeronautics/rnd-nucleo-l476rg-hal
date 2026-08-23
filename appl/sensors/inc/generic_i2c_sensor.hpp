#ifndef APPL_SENSORS_INC_GENERIC_I2C_SENSOR_HPP
#define APPL_SENSORS_INC_GENERIC_I2C_SENSOR_HPP

#include "i2c.hpp"
#include "sensor.hpp"

#include <cstdint>
#include <string_view>

namespace application::sensors {

/**
 * @brief Temperature sample produced by a generic I2C sensor.
 */
struct TemperatureSample {
    float celsius;
};

/**
 * @brief Generic I2C temperature sensor driver.
 *
 * Connects to a board socket and reads temperature data from a device register.
 */
class GenericI2cSensor final : public Sensor<TemperatureSample> {
  public:
    /**
     * @brief Constructs the I2C temperature sensor driver.
     *
     * @param i2c I2C bus instance.
     * @param address 7-bit I2C device address.
     * @param temperature_register Register containing temperature data.
     */
    GenericI2cSensor(platform::I2c& i2c,
                       std::uint8_t address,
                       std::uint8_t temperature_register = 0x00U) noexcept;

    [[nodiscard]] SensorStatus initialize() noexcept override;
    [[nodiscard]] SensorStatus read(TemperatureSample& sample) noexcept override;
    [[nodiscard]] bool initialized() const noexcept override;

  private:
    [[nodiscard]] SensorStatus convert_status(platform::I2cStatus status) const noexcept;
    [[nodiscard]] float parse_temperature(std::uint8_t msb,
                                         std::uint8_t lsb) const noexcept;

    platform::I2c& i2c_;
    std::uint8_t address_;
    std::uint8_t temperature_register_;
    bool initialized_{false};
};

[[nodiscard]] constexpr std::string_view to_string(SensorStatus status) noexcept {
    switch (status) {
    case SensorStatus::ok:
        return "ok";
    case SensorStatus::not_initialized:
        return "not initialized";
    case SensorStatus::communication_error:
        return "communication error";
    case SensorStatus::unexpected_device:
        return "unexpected device";
    case SensorStatus::configuration_error:
        return "configuration error";
    }
    return "unknown sensor status";
}

} // namespace application::sensors

#endif // APPL_SENSORS_INC_GENERIC_I2C_SENSOR_HPP
