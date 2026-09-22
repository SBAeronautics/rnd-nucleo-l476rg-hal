#ifndef APPL_SENSORS_INC_BMP280_HPP
#define APPL_SENSORS_INC_BMP280_HPP
// converts pressure data to altitude data 
#include "gpio.hpp"
#include "sensor.hpp"
#include "i2c_device.hpp"
// I2C up to 3.4 Mhz for bmp 280
// 2.7 uA @ 1 Hz 

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace application::sensors{


/**
 * @brief sensor data for bmp280 tempature and Pressure 
 */
struct  TempPressSample{
    std::int16_t Tempature;
    std::int16_t Pressure;
};
// FSM For BMP 280
// POWER OFF ->(vdd) SLEEP
// normal mode continously captures data then goes into a higher power sleep mode for t standby
// needs one time configuration of write registers (use with iir filter to avoid reseting it)
// from sleep -> (MODE == 11) Normal
// or
// from sleep -> (MODE == 01) Forced

// from Normal -> (MODE == 01) Forced
// from Normal -> (MODE == 00) Sleep

// forced moderetrieves a single specificed measurement based on the configuration register 
// write settings -> and then for osrs_t take n samples and for osrs_p take n samples

// the default transition to forced is sleep 

/

class bmp280 final : public Sensor<TempPressSample> {

public:
    // -------------------------------------------------------------------------
    // Public Constructors and Destructors

    /**
     * @brief Constructs an BMP280 driver.
     *
     * @param i2c i2c bus connected to the sensor.
     * @param chip_select_pin GPIO pin connected to SOO () and CSB (chip select) active high
     */
    BMP280(platform::i2c& i2c,
            platform::GpioPin chip_select_pin) noexcept;
 // -------------------------------------------------------------------------
    // Public Member Methods

    /**
     * @brief Verifies and configures the BMP280.
     *
     * Reads the device identifier (address?
     * configures the output data rate and data format, 
     * and places the sensor into measurement mode. see fsm above
     *
     * @return Status of the initialization operation.
     */
    [[nodiscard]] SensorStatus initialize() noexcept override;

    /**
     * @brief Reads one tempature or pressure sample.
     *
     * @param sample Destination for the raw sample.
     * @return Status of the read operation.
     */
    [[nodiscard]] SensorStatus read(TempSenseSample& sample) noexcept override;

    /**
     * @brief Checks whether the sensor initialized successfully.
     *
     * @return `true` when initialization completed successfully; otherwise
     * `false`.
     */
    [[nodiscard]] bool initialized() const noexcept override;

  private:
    /**
     * @brief BMP280 register addresses used by the driver.
     */
     // what  is the timing so i can meet nyquist 
    enum class Register : std::uint8_t {
        temp_xlsb = 0xFCU, // extra bits from increased sampling
        temp_lsb = 0xFBU, // default 16 bit sampling
        temp_msb = 0xFAU, 
        press_xlsb = 0xF9U, // extra bits from
        press_lsb = 0xF8U,
        press_msb = 0xF7U,
        config = 0xF5U, // configures IIR for pressure (p changes rapidly), and t standby 
        ctrl_meas = 0xF4U, // mode contrl, pressure and temp oversampling (state machine above)
        status = 0xF3U, // bit 3 high is measuring and 0 when result is 
        // tranfserdand bit 0  set to1 when nvm data is copied to image regs 0 when copying is done
        reset = 0xF2U, // 
        id = 0xD0, // the id of this device is 0x58
        reset = 0xE0 // if 0xb6 is written device is reset 
    };
    //


    // -------------------------------------------------------------------------
    // Private Member Methods

    /**
     * @brief Reads one BMP280 register.
     *
     * @param register_address Register to read.
     * @param value Destination for the register value.
     * @return Status of the register read.
     */
    [[nodiscard]] SensorStatus read_register(Register register_address,
                                             std::uint8_t& value) noexcept;

    /**
     * @brief Reads consecutive BMP280 registers.
     *
     * @param start_address First register to read.
     * @param values Destination buffer for the register values.
     * @param count Number of registers to read.
     * @return Status of the register read.
     */
    [[nodiscard]] SensorStatus read_registers(Register start_address,
                                              std::uint8_t* values,
                                              std::size_t count) noexcept;

    /**
     * @brief Writes one bmp280 register.
     *   
     * @param register_address Register to write.
     * @param value Value to write.
     * @return Status of the register write.
     */
    [[nodiscard]] SensorStatus write_register(Register register_address,
                                              std::uint8_t value) noexcept;

    /**
     * @brief Converts an I2C status into a sensor status.
     *
     * @param status I2C operation status.
     * @return Corresponding sensor operation status.
     */ 
    [[nodiscard]] static SensorStatus convert_status(platform::I2CStatus status) noexcept;

    // /**
    //  * @brief Combines two register bytes into a signed acceleration value.
    //  *
    //  * @param low Least-significant byte.
    //  * @param high Most-significant byte.
    //  * @return Signed 16-bit acceleration value.
    //  */
    // [[nodiscard]] static std::int16_t combine_bytes(std::uint8_t low,
    //                                                 std::uint8_t high) noexcept;

    platform::I2CDevice device_;
    bool initialized_{false};
        // this i2c device 
    static constexpr std::uint8_t expected_device_id{0x58};
    static constexpr std::uint8_t read_command{0x80U};
    static constexpr std::uint8_t multibyte_command{0x40U};
    static constexpr std::uint8_t standby_mode{0x00U};
    static constexpr std::uint8_t measurement_mode{0x08U};
    static constexpr std::uint8_t data_format_configuration{0x08U};
    static constexpr std::uint8_t bandwidth_configuration{0x0AU};
    static constexpr std::uint8_t 
};

/**
 * @brief Converts a sensor status into printable text.
 *
 * @param status Sensor status to convert.
 * @return Text describing the sensor status.
 */
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

/**
 * @brief Formats an  sample as printable text.
 *
 * The resulting text has the following format:
 *
 * @code
 * X: 12, Y: -35, Z: 258
 * @endcode
 *
 * The function does not append a null terminator. The returned length should
 * be used when constructing a string view over the buffer.
 *
 * @param sample Acceleration sample to format.
 * @param buffer Destination buffer.
 * @param capacity Capacity of the destination buffer.
 * @return Number of characters written to the buffer.
 */
[[nodiscard]]
std::size_t format_sample(const AccelerationSample& sample,
                          char* buffer,
                          std::size_t capacity) noexcept;

} // namespace application::sensors

#endif // APPL_SENSORS_INC_ADXL345_HPP
