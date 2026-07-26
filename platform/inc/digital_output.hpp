#ifndef PLATFORM_INC_DIGITAL_OUTPUT_HPP
#define PLATFORM_INC_DIGITAL_OUTPUT_HPP

namespace platform {

class DigitalOutput {
  public:
    virtual ~DigitalOutput() = default;

    virtual void set() noexcept = 0;
    virtual void clear() noexcept = 0;
    virtual void toggle() noexcept = 0;
    virtual void write(bool active) noexcept = 0;
};

} // namespace platform

#endif // PLATFORM_INC_DIGITAL_OUTPUT_H