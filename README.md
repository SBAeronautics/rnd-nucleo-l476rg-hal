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
## Hardware test firmware

Each file in `tests/hardware/` is a standalone firmware entry point with its own
`int main()`. Select one with `FIRMWARE_TEST`, using the filename without `.cpp`.
The selected test replaces all `appl/src/` sources and shares the platform,
MCAL, interrupt handlers, and sensor library with the application.

Build the UART polling smoke test:

```bash
cmake --preset HardwareTest -DFIRMWARE_TEST=uart
cmake --build --preset HardwareTest
```

Build the UART DMA smoke test:

```bash
cmake --preset HardwareTest -DFIRMWARE_TEST=uart_dma
cmake --build --preset HardwareTest
```

Flash the selected test:

```bash
STM32_Programmer_CLI -c port=SWD -w build/HardwareTest/nucleo_hal.elf -v -rst
```

Open the ST-LINK virtual COM port at **115200 baud, 8 data bits, no parity,
one stop bit, no flow control**. Both tests should print one complete line per
second and toggle the status LED. The DMA test prints a failure message and
holds the LED on if a transfer returns an error; a missing completion interrupt
can leave it waiting indefinitely with the LED stopped. These are manual board
smoke tests; compiling them does not verify physical UART output or DMA behavior.

To add a test, create `tests/hardware/my_feature.cpp` with its own `main()`, call
`platform::nucleo_l476rg::initialize()`, and configure with
`-DFIRMWARE_TEST=my_feature`. No CMake source-list edit is needed. Unknown names
fail during configuration. Reconfigure whenever you change the selected test;
`cmake --build` uses the last configured selection. The HardwareTest preset
defaults to `uart`, so pass the desired name each time you configure it.

Build the actual application again:

```bash
cmake --preset Debug
cmake --build --preset Debug
```

The Debug preset explicitly clears `FIRMWARE_TEST`. Application artifacts stay
in `build/Debug/`; test artifacts stay in `build/HardwareTest/`. The existing
VS Code launch configuration still builds and launches the Debug application.
To debug a hardware test, use `build/HardwareTest/nucleo_hal.elf` and a build task
that runs `cmake --build --preset HardwareTest`.
