#include "statemachine.hpp"

namespace application::statemachine {

StateMachine::StateMachine(State* initial) : current_state_{initial} {}

void StateMachine::update() noexcept {
    if (current_state_ == nullptr) return;

    current_state_->update();
}

void StateMachine::eventHandler(Event event) noexcept {
    /*
     * Ignore a transition to the state that is already active.
     */
    if (current_state_ == &next_state) {
        return;
    }

    /*
     * Exit the current state before changing states.
     */
    if (current_state_ != nullptr) {
        current_state_->exit();
    }

    /*
     * Make the next state active.
     */
    current_state_ = &next_state;

    /*
     * Perform the new state's entry behavior.
     */
    current_state_->enter();
}

bool StateMachine::contextTick() const noexcept {
    return current_state_ != nullptr;
}

State* StateMachine::currentState() noexcept {
    return current_state_;
}

const State* StateMachine::currentState() const noexcept {
    return current_state_;
}

} // namespace application::statemachine