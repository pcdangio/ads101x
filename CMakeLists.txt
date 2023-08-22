cmake_minimum_required(VERSION 3.2)

# Set up project.
project(ads101x
    VERSION 0.4
    DESCRIPTION "A driver for the TI ADS101X family of analog-to-digital converters.")

# OPTIONS
option(PLATFORM "Specifies which platform to build the driver for (base, pigpio)")
option(BUILD_TESTS "Specifies if unit tests should be built" OFF)

# LIBRARY
# Specify base source files.
set(driver_sources
    src/configuration.cpp
    src/driver/base.cpp)
# Specify base link libraries.
set(driver_libraries)
# Handle platforms.
if(PLATFORM STREQUAL "base")
    # No action required, base source files and link libraries already set.
elseif(PLATFORM STREQUAL "pigpio")
    # Find pigpio library and add to link library list.
    find_library(PIGPIO_LIBS pigpio REQUIRED)
    list(APPEND driver_libraries
        ${PIGPIO_LIBS})
    # Add pigpio driver sources.
    list(APPEND driver_sources
        src/driver/pigpio/error.cpp
        src/driver/pigpio/local.cpp
        src/driver/pigpio/daemon.cpp)
elseif(PLATFORM STREQUAL "OFF")
    message(FATAL_ERROR "PLATFORM option is not set")
else()
    message(FATAL_ERROR "PLATFORM option \"${PLATFORM}\" is unrecognized")
endif()
# Print platform that is being built.
message("Configured for platform \"${PLATFORM}\"")
# Create library.
add_library(${PROJECT_NAME} STATIC ${driver_sources})
# Link dependencies.
target_link_libraries(${PROJECT_NAME} ${driver_libraries})
# Specify include directories.
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

# TEST
# Check if option is set.
if(BUILD_TESTS)
    # Find dependencies.
    find_package(GTest REQUIRED)
    # Create test executable.
    add_executable(${PROJECT_NAME}_test
        test/main.cpp
        test/configuration.cpp
        test/driver/base.cpp)
    # Link test executable.
    target_link_libraries(${PROJECT_NAME}_test
        ${PROJECT_NAME}
        GTest::gtest)
endif()