// ads101x
#include <ads101x/driver/pigpio/daemon.hpp>

// gtest
#include <gtest/gtest.h>

// PARAMATERS
// NOTE: These may be overridden by compiler options.
#ifndef TEST_DAEMON_IP
#define TEST_DAEMON_IP "localhost"
#endif
#ifndef TEST_DAEMON_PORT
#define TEST_DAEMON_PORT 8888
#endif
#ifndef TEST_I2C_BUS
#define TEST_I2C_BUS 1
#endif
#ifndef TEST_I2C_ADDRESS
#define TEST_I2C_ADDRESS 0x48
#endif

class pigpio_daemon
    : public testing::Test
{
protected:
    ads101x::driver::pigpio::daemon driver;
};

// CONNECT
TEST_F(pigpio_daemon, connect)
{
    // Connect to pigpio daemon.
    driver.pigpiod_connect(TEST_DAEMON_IP, TEST_DAEMON_PORT);
}

// START
TEST_F(pigpio_daemon, start)
{
    // Start the driver.
    driver.start(TEST_I2C_BUS, static_cast<ads101x::slave_address>(TEST_I2C_ADDRESS));
}

// CONFIGURATION
TEST_F(pigpio_daemon, configuration)
{
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
TEST_F(pigpio_daemon, conversion)
{
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
TEST_F(pigpio_daemon, lo_thresh)
{
    // Define lo_thresh value to write.
    uint16_t lo_thresh_write = 0b0000101010101010;

    // Write lo_thresh value.
    driver.write_lo_thresh(lo_thresh_write);

    // Read lo_threshold.
    uint16_t lo_thresh_read = driver.read_lo_thresh();

    // Verify write/read values are equal.
    EXPECT_EQ(lo_thresh_read, lo_thresh_write);
}
TEST_F(pigpio_daemon, hi_thresh)
{
    // Define hi_thresh value to write.
    uint16_t hi_thresh_write = 0b0000101010101010;

    // Write hi_thresh value.
    driver.write_hi_thresh(hi_thresh_write);

    // Read hi_threshold.
    uint16_t hi_thresh_read = driver.read_hi_thresh();

    // Verify write/read values are equal.
    EXPECT_EQ(hi_thresh_read, hi_thresh_write);
}

// STOP
TEST_F(pigpio_daemon, stop)
{
    // Stop the driver.
    driver.stop();
}

// DISCONNECT
TEST_F(pigpio_daemon, disconnect)
{
    // Disconnect from pigpio daemon.
    driver.pigpiod_disconnect();
}