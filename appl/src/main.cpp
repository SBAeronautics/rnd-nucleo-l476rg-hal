#include "nucleo_l476rg.hpp"
#include "system_clock.hpp"

volatile std::uint32_t measured_clock_hz = 0;
volatile platform::clock::Source measured_clock_source{};

int main() {
    platform::nucleo_l476rg::initialize();

    measured_clock_hz = platform::clock::frequency_hz();

    measured_clock_source = platform::clock::source();

    auto& led = platform::nucleo_l476rg::status_led();

    while (true) {
        led.set();
        platform::nucleo_l476rg::delay_ms(100U);

        led.clear();
        platform::nucleo_l476rg::delay_ms(4900U);
    }
}