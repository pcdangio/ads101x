// ads101x
#include <ads101x/driver/pigpio/local.hpp>

// gtest
#include <gtest/gtest.h>

// PARAMATERS
// NOTE: These may be overridden by compiler options.
#ifndef TEST_I2C_BUS
#define TEST_I2C_BUS 1
#endif
#ifndef TEST_I2C_ADDRESS
#define TEST_I2C_ADDRESS 0x48
#endif

// INITIALIZE
TEST(pigpio_local, initialize)
{
    // Create driver.
    ads101x::driver::pigpio::local driver;

    // Initialize pigpio.
    driver.initialize_pigpio();
}

// CONFIGURATION
TEST(pigpio_local, configuration)
{
    // Create driver.
    ads101x::driver::pigpio::local driver;

    // Start the driver.
    driver.start(TEST_I2C_BUS, static_cast<ads101x::slave_address>(TEST_I2C_ADDRESS));

    // Create a non-default configuration.
    ads101x::configuration config_write;
    config_write.set_multiplexer(ads101x::configuration::multiplexer::AIN0_GND);
    config_write.set_fsr(ads101x::configuration::fsr::FSR_6_114);
    config_write.set_data_rate(ads101x::configuration::data_rate::SPS_3300);
    config_write.set_comparator_polarity(ads101x::configuration::comparator_polarity::ACTIVE_HIGH);

    // Write configuration.
    driver.write_config(config_write);

    // Read the current configuration.
    ads101x::configuration config_read = driver.read_config();

    // Verify that the current config is the same as the modified config.
    EXPECT_EQ(config_read.bitfield(), config_write.bitfield());
}

// CONVERSION
TEST(pigpio_local, conversion)
{
    // Create driver.
    ads101x::driver::pigpio::local driver;

    // Start the driver.
    driver.start(TEST_I2C_BUS, static_cast<ads101x::slave_address>(TEST_I2C_ADDRESS));

    // Create a configuration to start a single-shot conversion.
    ads101x::configuration config;
    config.set_operation(ads101x::configuration::operation::CONVERT);
    config.set_multiplexer(ads101x::configuration::multiplexer::AIN0_GND);
    config.set_data_rate(ads101x::configuration::data_rate::SPS_3300);
    config.set_fsr(ads101x::configuration::fsr::FSR_6_114);

    // Loop to perform several conversions.
    for(uint32_t i = 0; i < 5; ++i)
    {
        // Write configuration to begin conversion.
        driver.write_config(config);

        // Wait for conversion to complete.
        usleep(10000);

        // Read conversion.
        uint16_t conversion = driver.read_conversion();

        // Output conversion.
        std::cout << "conversion " << i << " = " << conversion << std::endl;
    }
}

// THRESHOLDS
TEST(pigpio_local, lo_thresh)
{
    // Create driver.
    ads101x::driver::pigpio::local driver;

    // Start the driver.
    driver.start(TEST_I2C_BUS, static_cast<ads101x::slave_address>(TEST_I2C_ADDRESS));

    // Define lo_thresh value to write.
    uint16_t lo_thresh_write = 0b0000101010101010;

    // Write lo_thresh value.
    driver.write_lo_thresh(lo_thresh_write);

    // Read lo_threshold.
    uint16_t lo_thresh_read = driver.read_lo_thresh();

    // Verify write/read values are equal.
    EXPECT_EQ(lo_thresh_read, lo_thresh_write);
}
TEST(pigpio_local, hi_thresh)
{
    // Create driver.
    ads101x::driver::pigpio::local driver;

    // Start the driver.
    driver.start(TEST_I2C_BUS, static_cast<ads101x::slave_address>(TEST_I2C_ADDRESS));

    // Define hi_thresh value to write.
    uint16_t hi_thresh_write = 0b0000101010101010;

    // Write hi_thresh value.
    driver.write_hi_thresh(hi_thresh_write);

    // Read hi_threshold.
    uint16_t hi_thresh_read = driver.read_hi_thresh();

    // Verify write/read values are equal.
    EXPECT_EQ(hi_thresh_read, hi_thresh_write);
}

// TERMINATE
TEST(pigpio_local, terminate)
{
    // Create driver.
    ads101x::driver::pigpio::local driver;

    // Terminate pigpio.
    driver.terminate_pigpio();
}