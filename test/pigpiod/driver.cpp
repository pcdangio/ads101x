// ads101x
#include <ads101x/pigpiod/driver.hpp>

// pigpio
#include <pigpio.h>

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
#ifndef TEST_ALERT_RDY_PIN
#define TEST_ALERT_RDY_PIN 25
#endif

// Create global storage for connection handle.
int32_t pigpiod_handle = PI_NO_HANDLE;

// CONNECT
TEST(pigpiod, connect)
{
    // Create driver instance.
    ads101x::pigpiod::driver driver;

    // Connect to pigpio daemon.
    driver.pigpiod_connect(TEST_DAEMON_IP, TEST_DAEMON_PORT);

    // Store handle.
    pigpiod_handle = driver.pigpiod_handle();
}

// CONFIGURATION
TEST(pigpiod, configuration)
{
    // Create driver instance.
    ads101x::pigpiod::driver driver(pigpiod_handle);

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

    // Stop the driver.
    driver.stop();
}

// CONVERSION
TEST(pigpiod, conversion)
{
    // Create driver instance.
    ads101x::pigpiod::driver driver(pigpiod_handle);

    // Start the driver.
    driver.start(TEST_I2C_BUS, static_cast<ads101x::slave_address>(TEST_I2C_ADDRESS));

    // Create a configuration to start a single-shot conversion.
    ads101x::configuration config;
    config.set_operation(ads101x::configuration::operation::CONVERT);
    config.set_multiplexer(ads101x::configuration::multiplexer::AIN0_GND);
    config.set_data_rate(ads101x::configuration::data_rate::SPS_3300);
    config.set_fsr(ads101x::configuration::fsr::FSR_6_114);

    // Write configuration to begin conversion.
    driver.write_config(config);

    // Wait for conversion to complete.
    usleep(10000);

    // Read conversion.
    uint16_t conversion = driver.read_conversion();

    // Output conversion.
    std::cout << "conversion = " << conversion << std::endl;

    // Stop the driver.
    driver.stop();
}

// THRESHOLDS
TEST(pigpiod, lo_thresh)
{
    // Create driver instance.
    ads101x::pigpiod::driver driver(pigpiod_handle);

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

    // Stop the driver.
    driver.stop();
}
TEST(pigpiod, hi_thresh)
{
    // Create driver instance.
    ads101x::pigpiod::driver driver(pigpiod_handle);

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

    // Stop the driver.
    driver.stop();
}

// ALERT_RDY
void alert_rdy_callback(bool level)
{
    std::cout << "alert_rdy callback: " << level << std::endl;
}
TEST(pigpio, alert_rdy)
{
    // Create driver.
    ads101x::pigpiod::driver driver;

    // Start the driver.
    driver.start(TEST_I2C_BUS, static_cast<ads101x::slave_address>(TEST_I2C_ADDRESS));

    // Attach alert_rdy callback.
    driver.attach_alert_rdy(TEST_ALERT_RDY_PIN, &alert_rdy_callback);

    // Write lo_thresh/hi_thresh to put alert_rdy into conversion ready mode.
    driver.write_hi_thresh(0b0000100000000000);
    driver.write_lo_thresh(0b0000000000000000);

    // Create configuration for single shot.
    ads101x::configuration config;
    config.set_operation(ads101x::configuration::operation::CONVERT);
    config.set_multiplexer(ads101x::configuration::multiplexer::AIN0_GND);
    config.set_fsr(ads101x::configuration::fsr::FSR_6_114);
    config.set_data_rate(ads101x::configuration::data_rate::SPS_128);

    // Start conversion.
    driver.write_config(config);

    // Wait for conversion to finish.
    usleep(50000);

    // Detach alert_rdy callback.
    driver.detach_alert_rdy();
}

// DISCONNECT
TEST(pigpiod, disconnect)
{
    // Create driver instance.
    ads101x::pigpiod::driver driver(pigpiod_handle);

    // Disconnect from pigpio daemon.
    driver.pigpiod_disconnect();
}