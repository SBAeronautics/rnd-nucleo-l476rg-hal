set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Use the same installation for C, C++, assembler, linker utilities,
# objcopy, and size.
set(ARM_GNU_BIN
    "C:/Arm/GNU_Toolchain_mingw-w64-x86_64-arm-none-eabi/bin"
)

set(CMAKE_C_COMPILER
    "${ARM_GNU_BIN}/arm-none-eabi-gcc.exe"
    CACHE FILEPATH "ARM C compiler"
)

set(CMAKE_CXX_COMPILER
    "${ARM_GNU_BIN}/arm-none-eabi-g++.exe"
    CACHE FILEPATH "ARM C++ compiler"
)

set(CMAKE_ASM_COMPILER
    "${ARM_GNU_BIN}/arm-none-eabi-gcc.exe"
    CACHE FILEPATH "ARM assembler"
)

set(CMAKE_AR
    "${ARM_GNU_BIN}/arm-none-eabi-ar.exe"
    CACHE FILEPATH "ARM archiver"
)

set(CMAKE_RANLIB
    "${ARM_GNU_BIN}/arm-none-eabi-ranlib.exe"
    CACHE FILEPATH "ARM ranlib"
)

set(CMAKE_OBJCOPY
    "${ARM_GNU_BIN}/arm-none-eabi-objcopy.exe"
    CACHE FILEPATH "ARM objcopy"
)

set(CMAKE_SIZE
    "${ARM_GNU_BIN}/arm-none-eabi-size.exe"
    CACHE FILEPATH "ARM size"
)