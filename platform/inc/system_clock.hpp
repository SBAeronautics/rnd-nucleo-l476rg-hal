#ifndef PLATFORM_INC_SYSTE_CLOCK_HPP
#define PLATFORM_INC_SYSTE_CLOCK_HPP

#include <cstdint>

namespace platform::clock {

/**
 * @brief Available system-clock sources.
 */
enum class Source : std::uint8_t {
    msi,
    hsi16,
    hse,
    pll,
    unknown
};

/**
 * @brief Configures the MCU system clock.
 *
 * @note Call this function before initializing peripherals that depend on the
 * system-clock frequency.
 */
void configure() noexcept;

/**
 * @brief Gets the currently selected system-clock source.
 *
 * @return Active system-clock source, or Source::unknown when it cannot be
 * identified.
 */
[[nodiscard]] Source source() noexcept;

/**
 * @brief Gets the current processor clock frequency.
 *
 * @return Processor clock frequency in hertz.
 */
[[nodiscard]] std::uint32_t frequency_hz() noexcept;

/**
 * @brief Blocks execution for the requested number of milliseconds.
 *
 * @param milliseconds Duration of the delay in milliseconds.
 *
 * @warning This function busy-waits and prevents the current execution context
 * from performing other work during the delay.
 */
void delay_ms(std::uint32_t milliseconds) noexcept;

} // namespace platform::clock

#endif // PLATFORM_INC_SYSTE_CLOCK_HPP