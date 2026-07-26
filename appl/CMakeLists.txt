file(GLOB_RECURSE APPL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(NOT APPL_SOURCES)
    message(FATAL_ERROR
        "No application source files found under appl/src"
    )
endif()

target_sources(${PROJECT_NAME} PRIVATE
    ${APPL_SOURCES}
)