file(GLOB_RECURSE APPL_STATEMACHINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(appl_statemachine STATIC
    ${APPL_STATEMACHINE_SOURCES}
)

target_include_directories(appl_statemachine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

target_compile_features(appl_statemachine
    PUBLIC
        cxx_std_20
)

target_compile_options(appl_statemachine
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -fno-exceptions
        -fno-rtti
        -fno-threadsafe-statics
)