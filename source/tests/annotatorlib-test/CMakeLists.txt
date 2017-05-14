
# 
# Executable name and options
# 

# Target name
set(target annotatorlib-test)
message(STATUS "Test ${target}")

# 
# Sources
# 

set(sources
    main.cpp
    #algo_test.cpp
    algo_adjust_test.cpp
    annotation_test.cpp
    attribute_test.cpp
    command_adjustneighbors.cpp
    commands_test.cpp
    imageftp_test.cpp
    imageset_test.cpp
    object_test.cpp
    project_test.cpp
    saver_test.cpp
    session_test.cpp
    storage_json_test.cpp
    storage_mongodb_test.cpp
    storage_mysql_test.cpp
    storage_sqlite_test.cpp
    storage_xml_test.cpp
)


# 
# Create executable
# 

# Build executable
add_executable(${target}
    ${sources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})


# 
# Project options
# 

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


# 
# Include directories
# 

target_include_directories(${target}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${PROJECT_BINARY_DIR}/source/include
)


# 
# Libraries
# 
if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
include(CodeCoverage)
set(libgcov "gcov")

setup_target_for_coverage(${META_PROJECT_NAME}_coverage ${target} coverage)
endif()

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::annotatorlib
    ${META_PROJECT_NAME}::mysqlstorage
    ${META_PROJECT_NAME}::mongodbstorage
    ${META_PROJECT_NAME}::sqlitestorage
    libgmock
    ${libgcov}
)
# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)
