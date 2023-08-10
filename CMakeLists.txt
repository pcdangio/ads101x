cmake_minimum_required(VERSION 3.2)

# Set up project.
project(ads101x
    VERSION 0.2
    DESCRIPTION "A driver for the TI ADS101X family of analog-to-digital converters.")

# TEST
# Specify build option for tests.
option(BUILD_TESTS "build tests" OFF)
# Check if option is set.
if(BUILD_TESTS)
    # Find dependencies.
    find_package(GTest REQUIRED)
    # Create test executable.
    add_executable(${PROJECT_NAME}_test
        test/main.cpp)
    # Link test executable.
    target_link_libraries(${PROJECT_NAME}_test
        GTest::gtest)
endif()