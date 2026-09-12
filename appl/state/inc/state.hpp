#ifndef APPL_STATE_INC_STATE_HPP
#define APPL_STATE_INC_STATE_HPP

namespace application::statemachine {

/**
 * @brief Base interface for an application state.
 *
 * Each application state implements behavior that occurs when the state is
 * entered, while the state is active, and when the state is exited.
 */
class State {
  public:
    /**
     * @brief Destroys the state.
     */
    virtual ~State() = default;

    /**
     * @brief Called once when the state becomes active.
     */
    virtual void enter() noexcept = 0;

    /**
     * @brief Called periodically while the state is active.
     */
    virtual void update() noexcept = 0;

    /**
     * @brief Called once before the state becomes inactive.
     */
    virtual void exit() noexcept = 0;

    State(const State&) = delete;
    State& operator=(const State&) = delete;

  protected:
    /**
     * @brief Constructs a state.
     */
    State() = default;
};

} // namespace application::statemachine

#endif // APPL_STATE_INC_STATE_HPP