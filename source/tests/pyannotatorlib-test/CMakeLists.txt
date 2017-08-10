if(NOT OPTION_BUILD_PYTHON)
    return()
endif()

# Target name
set(target pyannotatorlib-test)
message(STATUS "Test ${target}")

# Build executable
add_custom_target(${target} COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/${target}.py WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS pyannotatorlib SOURCES ${target}.py
)

