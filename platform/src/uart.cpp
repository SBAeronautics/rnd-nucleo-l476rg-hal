#include "uart.hpp"

#include "stm32l4xx_ll_usart.h"

namespace platform {

Uart::Uart(USART_TypeDef* instance) : instance_{instance} {}

void Uart::write_byte(std::uint8_t byte) noexcept {
    while (LL_USART_IsActiveFlag_TXE(instance_) == 0U) {}

    LL_USART_TransmitData8(instance_, byte);
}

void Uart::write(std::string_view text) noexcept {
    for (const char character : text) {
        write_byte(static_cast<std::uint8_t>(character));
    }

    while (LL_USART_IsActiveFlag_TC(instance_) == 0U) {}
}

void Uart::write_line(std::string_view text) noexcept {
    write(text);
    write("\r\n");
}

} // namespace platform