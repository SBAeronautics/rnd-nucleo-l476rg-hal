#ifndef PLATFORM_INC_DIGITAL_INPUT_HPP
#define PLATFORM_INC_DIGITAL_INPUT_HPP

namespace platform {

class DigitalInput {
  public:
    virtual ~DigitalInput() = default;

    [[nodiscard]] virtual bool read() const noexcept = 0;
}; // class DigitalInput

} // namespace platform

#endif