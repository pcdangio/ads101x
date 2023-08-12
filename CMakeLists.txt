cmake_minimum_required(VERSION 3.2)

# Set up project.
project(ads101x
    VERSION 0.3
    DESCRIPTION "A driver for the TI ADS101X family of analog-to-digital converters.")

# LIBRARY
# Create library.
add_library(${PROJECT_NAME} STATIC
    src/configuration.cpp)
# Specify include directories.
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

# TEST
# Specify build option for tests.
option(BUILD_TESTS "build tests" OFF)
# Check if option is set.
if(BUILD_TESTS)
    # Find dependencies.
    find_package(GTest REQUIRED)
    # Create test executable.
    add_executable(${PROJECT_NAME}_test
        test/main.cpp
        test/configuration.cpp)
    # Link test executable.
    target_link_libraries(${PROJECT_NAME}_test
        ${PROJECT_NAME}
        GTest::gtest)
endif()