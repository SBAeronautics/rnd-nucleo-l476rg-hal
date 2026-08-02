#ifndef PLATFORM_INC_NUCLEO_L476RG_HPP
#define PLATFORM_INC_NUCLEO_L476RG_HPP

#include "digital_input.hpp"
#include "digital_output.hpp"
#include "stm32l4xx.h"
#include <cstdint>

#include "digital_output.hpp"

#include <cstdint>

namespace platform::nucleo_l476rg {

void initialize() noexcept;

DigitalOutput& status_led() noexcept;

void delay_ms(std::uint32_t milliseconds) noexcept;

} // namespace platform::nucleo_l476rg

#endif // PLATFORM_INC_NUCLEO_L476RG_HPP