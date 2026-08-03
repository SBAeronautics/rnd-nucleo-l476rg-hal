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

    volatile int x = 10;

    auto& led =
        platform::nucleo_l476rg::status_led();

    while (true) {
        if (platform::nucleo_l476rg::take_user_button_press()) {
            led.toggle();
            ++x;
        }
    }
}