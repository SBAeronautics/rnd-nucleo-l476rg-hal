# Nucleo-l476rg Hardware Abstraction Layer (HAL)

## Prerequisites

Install the following tools:

- CMake
- Ninja
- Arm GNU Toolchain
- STM32CubeProgrammer

## Build and Flash

Run all commands from the repository root.

Configure the Debug build:

```bash
cmake --preset Debug
cmake --build --preset Debug
```

Flash the NUCLEO-L476RG:

```bash
STM32_Programmer_CLI \
    -c port=SWD \
    -w build/Debug/nucleo_hal.elf \
    -v \
    -rst
```