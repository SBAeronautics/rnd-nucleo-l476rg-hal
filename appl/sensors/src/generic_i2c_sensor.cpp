#include "generic_i2c_sensor.hpp"

#include <cstddef>
#include <cstdint>

namespace application::sensors {

GenericI2cSensor::GenericI2cSensor(platform::I2c& i2c,
                                   std::uint8_t address,
                                   std::uint8_t temperature_register) noexcept
    : i2c_{i2c},
      address_{address},
      temperature_register_{temperature_register} {
}

SensorStatus GenericI2cSensor::initialize() noexcept {
    if (!i2c_.initialized()) {
        return SensorStatus::not_initialized;
    }

    initialized_ = true;
    return SensorStatus::ok;
}

SensorStatus GenericI2cSensor::read(TemperatureSample& sample) noexcept {
    if (!initialized_) {
        return SensorStatus::not_initialized;
    }

    std::uint8_t register_address = temperature_register_;
    std::uint8_t temperature_data[2]{};

    const platform::I2cStatus status = i2c_.write_then_read(
        address_,
        &register_address,
        sizeof(register_address),
        temperature_data,
        sizeof(temperature_data));

    if (status != platform::I2cStatus::ok) {
        return convert_status(status);
    }

    sample.celsius = parse_temperature(temperature_data[0], temperature_data[1]);
    return SensorStatus::ok;
}

bool GenericI2cSensor::initialized() const noexcept {
    return initialized_;
}

SensorStatus GenericI2cSensor::convert_status(platform::I2cStatus status) const noexcept {
    switch (status) {
    case platform::I2cStatus::ok:
        return SensorStatus::ok;
    case platform::I2cStatus::not_initialized:
        return SensorStatus::not_initialized;
    case platform::I2cStatus::timeout:
    case platform::I2cStatus::nack:
    case platform::I2cStatus::bus_busy:
    case platform::I2cStatus::error:
    default:
        return SensorStatus::communication_error;
    }
}

float GenericI2cSensor::parse_temperature(std::uint8_t msb,
                                                  std::uint8_t lsb) const noexcept {
    const std::uint16_t raw = static_cast<std::uint16_t>(msb) << 8U |
                              static_cast<std::uint16_t>(lsb);
    return static_cast<float>(raw) / 256.0F;
}

} // namespace application::sensors
