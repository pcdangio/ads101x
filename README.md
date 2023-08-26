# ads101x

A C++ driver for the Texas Instruments [ADS101x](https://www.ti.com/lit/ds/symlink/ads1015.pdf) family of analog-to-digital converters.

## Overview

The ads101x library provides a driver that allows you to easily interface with the Texas Instruments ADS101x (ADS1013, ADS1014, ADS1015) series of analog-to-digital (ADC) converters. It offers a flexible and extensible way to communicate with the ADS101x devices, abstracting away the low-level details of I2C communication and providing a clean API for your applications. Features include:

- Abstracts I2C communication with the ADS101x devices.
- Provides a consistent API for configuration, conversion, thresholds, and alerts.
- Supports different platform-specific variants to suit your needs.

**License:** [MIT Open Source](LICENSE)

## Table of Contents

1. [Multi-Platform Support](#1-multi-platform-support)
2. [Getting Started](#2-getting-started)
3. [Usage](#3-usage)
4. [API Documentation](#4-api-documentation)
5. [Contributing](#5-contributing)

## 1: Multi-Platform Support

The ADS101x library provides multi-platform support, allowing you to use the driver on different hardware platforms with ease. The library includes multiple variants for platforms such as the Raspberry Pi, and includes a base driver class that can be overidden to support other platforms.

### 1.1: Base Driver:

The base driver offers a platform-agnostic implementation of the ADS101x driver. It serves as the foundation for the other variants and can be used with any I2C library or environment. Create a class derived from the base driver, and override the necessary platform-specific functions. If you need to do so in a separate project, compile the ads101x library using the ```-DADS101X_BASE=ON``` option when configuring with cmake to generate a static library containing the base driver functionality.

### 1.2: Raspberry Pi Drivers:

1. **pigpio**: This platform variant is based on the [pigpio](http://abyz.me.uk/rpi/pigpio/index.html) library, and uses the standard single-process implementation of pigpio. To build the library for this platform, use the ```-DADS101X_PIGPIO=ON``` option when configuring with cmake. Make sure to install pigpio beforehand as it is a dependency.

2. **pigpiod**: This platform variant is based on the [pigpio](http://abyz.me.uk/rpi/pigpio/index.html) library, and uses the daemon implementation of pigpio. To build the library for this platform, use the ```-DADS101X_PIGPIOD=ON``` option when configuring with cmake. Make sure to install pigpio beforehand as it is a dependency.

## 2: Getting Started

To use the ads101x library in your project, clone the repository and follow these steps:

```bash
# Create a build directory and change into it.
mkdir build && cd build
# Configure the project using cmake (see build options below).
cmake <options> ..
# Build the project.
make
```

### 2.1: Build Options

The following options can be used with cmake to configure which libraries and functionalities are built:

- ```-DADS101X_BASE=ON```: Builds the base driver library.
- ```-DADS101X_PIGPIO=ON```: Builds the [pigpio](#12-raspberry-pi-drivers) platform library.
- ```-DADS101X_PIGPIOD=ON```: Builds the [pigpiod](#12-raspberry-pi-drivers) platform library.
- ```-DADS101X_TESTS=ON```: Builds unit test executables for all enabled platforms.

## 3: Usage

To use the library in your code, include the necessary headers and link against the appropriate ads101x static library. See the [API Documentation](#4-api-documentation) section for instructions on how to generate and view the library's API documentation files.

**Code Example:**

```cpp
#include <ads101x/pigpio/driver.hpp>

// Create a driver instance
ads101x::pigpio::driver driver;

// Initialize the pigpio library if not done elsewhere.
driver.pigpio_initialize();

// Start the driver using default I2C bus and slave address.
driver.start();

// Create a configuration to write to the ADS101x.
ads101x::configuration config;
config.set_operation(ads101x::configuration::operation::CONVERT);
config.set_multiplexer(ads101x::configuration::multiplexer::AIN0_GND);
config.set_data_rate(ads101x::configuration::data_rate::SPS_3300);
config.set_fsr(ads101x::configuration::fsr::FSR_6_114);

// Write configuration to begin conversion.
driver.write_config(config);

// Wait for conversion to complete.
usleep(10000);

// Read a conversion value.
uint16_t conversion = driver.read_conversion();

// Stop the driver
driver.stop();

// Terminate the pigpio library if not done elsewhere.
driver.pigpio_terminate();
```

## 4: API Documentation

The library uses ```doxygen``` for API documentation. To generate and view the documentation:

```bash
# Start from the repository root directory.

# Generate the documentation files.
doxygen doxyfile

# Open the documentation using your default html application.
xdg-open doc/html/index.html
```

## 5: Contributing

Contributions to the ads101x library are welcome! If you encounter issues, have suggestions, or want to contribute enhancements, feel free to open an issue or submit a pull request.