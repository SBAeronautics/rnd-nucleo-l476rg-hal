#ifndef PLATFORM_INC_SYSTE_CLOCK_HPP
#define PLATFORM_INC_SYSTE_CLOCK_HPP

#include <cstdint>

namespace platform::clock {

enum class Source : std::uint8_t { msi, hsi16, hse, pll, unknown };

void configure() noexcept;

[[nodiscard]]
Source source() noexcept;

[[nodiscard]]
std::uint32_t frequency_hz() noexcept;

} // namespace platform::clock

#endif // PLATFORM_INC_SYSTE_CLOCK_HPP