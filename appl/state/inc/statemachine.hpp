#ifndef APPL_STATE_INC_STATEMACHINE_HPP
#define APPL_STATE_INC_STATEMACHINE_HPP

#include "state.hpp"
#include <cstdint>

namespace application::statemachine {

enum class Event : std::uint8_t {
    DUMMY
};

/**
 * @brief Manages the active application state.
 *
 * The state machine does not own state objects. State objects must remain
 * valid for as long as they can be used by the state machine.
 */
class StateMachine final {
  public:
    /**
     * @brief Constructs an inactive state machine.
     */
    explicit StateMachine(State* initial) noexcept;

    /**
     * @brief Executes one update of the active state.
     */
    void update() noexcept;

    /**
     * @brief Transitions from the current state to another state.
     *
     * The current state's exit function is called before the next state's
     * enter function.
     *
     * @param next_state State that should become active.
     */
    void eventHandler(Event next_state) noexcept;

    /**
     * @brief Runs the current
     */
    void contextTick() const noexcept;

    /**
     * @brief Returns the currently active state.
     *
     * @return Pointer to the active state, or nullptr if the state machine
     * is not running.
     */
    [[nodiscard]] State* currentState() noexcept;

    /**
     * @brief Returns the currently active state.
     *
     * @return Pointer to the active state, or nullptr if the state machine
     * is not running.
     */
    [[nodiscard]] const State* currentState() const noexcept;

  private:
    State* current_state_{nullptr};
};

} // namespace application::statemachine

#endif // APPL_STATE_INC_STATEMACHINE_HPP