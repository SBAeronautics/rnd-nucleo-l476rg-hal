file(GLOB_RECURSE APPL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

target_sources(${PROJECT_NAME} PRIVATE
    ${APPL_SOURCES}
)

add_subdirectory(sensors)
add_subdirectory(state)

target_link_libraries(${PROJECT_NAME} PRIVATE
    appl_sensors
    appl_statemachine 
)