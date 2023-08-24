cmake_minimum_required(VERSION 3.2)

# Set up project.
project(ads101x
    VERSION 0.5
    DESCRIPTION "A driver for the TI ADS101X family of analog-to-digital converters.")

# OPTIONS
option(ADS101X_BASE "Specifies if the base library will be built" OFF)
option(ADS101X_PIGPIO "Specifies if the pigpio library will be built" OFF)
option(ADS101X_PIGPIOD "Specifies if the pigpiod library will be built" OFF)
option(ADS101X_TESTS "Specifies if unit tests should be built" OFF)

# ADS101X_TEST
if(ADS101X_TESTS)
    # Print that tests are being built.
    message("-- Build tests: ON")
    # Find dependencies.
    find_package(GTest REQUIRED)
endif()

# ADS101X_BASE
# Specify base source files.
set(base_sources
    src/configuration.cpp
    src/driver.cpp)
# Specify base test files.
set(base_test_sources
    test/main.cpp
    test/configuration.cpp
    test/driver.cpp)
if(ADS101X_BASE)
    # Print that base library is begin built.
    message("-- Build base library: ON")
    # Create library.
    add_library(${PROJECT_NAME}_base STATIC ${base_sources})
    # Specify include directories.
    target_include_directories(${PROJECT_NAME}_base PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
    # Check if building tests.
    if(ADS101X_TESTS)
        # Create test executable.
        add_executable(${PROJECT_NAME}_base_test ${base_test_sources})
        # Link dependencies.
        target_link_libraries(${PROJECT_NAME}_base_test
            ${PROJECT_NAME}_base
            GTest::GTest)
    endif()
endif()

# ADS101X_PIGPIO
if(ADS101X_PIGPIO)
    # Print that pigpio library is begin built.
    message("-- Build pigpio library: ON")
    # Find pigpio library.
    find_library(PIGPIO_LIB pigpio REQUIRED)
    # Create library.
    add_library(${PROJECT_NAME}_pigpio STATIC
        ${base_sources}
        src/pigpio/error.cpp
        src/pigpio/driver.cpp)
    # Link dependencies.
    target_link_libraries(${PROJECT_NAME}_pigpio
        ${PIGPIO_LIB})
    # Specify include directories.
    target_include_directories(${PROJECT_NAME}_pigpio PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
    # Check if building tests.
    if(ADS101X_TESTS)
        # Create test executable.
        add_executable(${PROJECT_NAME}_pigpio_test
            ${base_test_sources}
            test/pigpio/driver.cpp)
        # Link dependencies.
        target_link_libraries(${PROJECT_NAME}_pigpio_test
            ${PROJECT_NAME}_pigpio
            GTest::GTest)
    endif()
endif()

# ADS101X_PIGPIOD
if(ADS101X_PIGPIOD)
    # Print that pigpiod library is begin built.
    message("-- Build pigpiod library: ON")
    # Find pigpiod library.
    find_library(PIGPIOD_LIB pigpiod_if2 REQUIRED)
    # Create library.
    add_library(${PROJECT_NAME}_pigpiod STATIC
        ${base_sources}
        src/pigpio/error.cpp
        src/pigpiod/error.cpp
        src/pigpiod/driver.cpp)
    # Link dependencies.
    target_link_libraries(${PROJECT_NAME}_pigpiod
        ${PIGPIOD_LIB})
    # Specify include directories.
    target_include_directories(${PROJECT_NAME}_pigpiod PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
    # Check if building tests.
    if(ADS101X_TESTS)
        # Create test executable.
        add_executable(${PROJECT_NAME}_pigpiod_test
            ${base_test_sources}
            test/pigpiod/driver.cpp)
        # Link dependencies.
        target_link_libraries(${PROJECT_NAME}_pigpiod_test
            ${PROJECT_NAME}_pigpiod
            GTest::GTest)
    endif()
endif()