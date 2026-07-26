file(GLOB_RECURSE PLATFORM_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(NOT PLATFORM_SOURCES)
    message(FATAL_ERROR
        "No platform source files found under platform/src"
    )
endif()

add_library(platform STATIC
    ${PLATFORM_SOURCES}
)

target_include_directories(platform PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

target_link_libraries(platform PUBLIC
    mcal_config
)

target_compile_features(platform PUBLIC
    cxx_std_20
)

target_compile_options(platform PRIVATE
    -Wall
    -Wextra
    -Wpedantic

    -fno-exceptions
    -fno-rtti
    -fno-threadsafe-statics
)