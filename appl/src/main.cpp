#include "nucleo_l476rg.hpp"
#include "system_clock.hpp"

volatile std::uint32_t measured_clock_hz = 0;
volatile platform::clock::Source measured_clock_source{};

/**
 * @brief Application entry point.
 *
 * Initializes the board and toggles the status LED whenever the user-button
 * interrupt records a press event.
 *
 * @return This function does not return.
 */
int main() {
    platform::nucleo_l476rg::initialize();

    auto& led = platform::nucleo_l476rg::status_led();
    auto& console = platform::nucleo_l476rg::console();

    console.write_line("System initialized");
    console.write_line("Press the blue button");

    while (true) {
        if (platform::nucleo_l476rg::take_user_button_press()) {
            led.toggle();
            console.write_line("Button pressed");
        }
    }
}