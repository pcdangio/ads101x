// ads101x
#include <ads101x/configuration.hpp>

// gtest
#include <gtest/gtest.h>

// CONSTRUCTORS
TEST(configuration, default_constructor)
{
    // Create default-constructed configuration.
    ads101x::configuration config;

    // Verify bitfield.
    EXPECT_EQ(config.bitfield(), 0x0583);
}
TEST(configuration, read_constructor)
{
    // Create simulated CONFIG register value.
    // NOTE: This is the default startup value for the ADS101X.
    uint16_t config_register = 0x8583;

    // Create read-constructed configuration.
    ads101x::configuration config(config_register);

    // Verify bitfield.
    EXPECT_EQ(config.bitfield(), config_register);
}

// PROPERTIES
TEST(configuration, operation)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::operation::CONVERT;

    // Set value and test get/bitfield.
    config.set_operation(value);
    EXPECT_EQ(config.get_operation(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}
TEST(configuration, multiplexer)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::multiplexer::AIN0_GND;

    // Set value and test get/bitfield.
    config.set_multiplexer(value);
    EXPECT_EQ(config.get_multiplexer(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}
TEST(configuration, fsr)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::fsr::FSR_4_096;

    // Set value and test get/bitfield.
    config.set_fsr(value);
    EXPECT_EQ(config.get_fsr(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}
TEST(configuration, mode)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::mode::SINGLESHOT;

    // Set value and test get/bitfield.
    config.set_mode(value);
    EXPECT_EQ(config.get_mode(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}
TEST(configuration, data_rate)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::data_rate::SPS_3300;

    // Set value and test get/bitfield.
    config.set_data_rate(value);
    EXPECT_EQ(config.get_data_rate(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}
TEST(configuration, comparator_mode)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::comparator_mode::WINDOW;

    // Set value and test get/bitfield.
    config.set_comparator_mode(value);
    EXPECT_EQ(config.get_comparator_mode(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}
TEST(configuration, comparator_polarity)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::comparator_polarity::ACTIVE_HIGH;

    // Set value and test get/bitfield.
    config.set_comparator_polarity(value);
    EXPECT_EQ(config.get_comparator_polarity(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}
TEST(configuration, comparator_latch)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::comparator_latch::LATCHING;

    // Set value and test get/bitfield.
    config.set_comparator_latch(value);
    EXPECT_EQ(config.get_comparator_latch(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}
TEST(configuration, comparator_queue)
{
    // Create empty configuration.
    ads101x::configuration config(0x0000);

    // Create non-zero value.
    auto value = ads101x::configuration::comparator_queue::DISABLED;

    // Set value and test get/bitfield.
    config.set_comparator_queue(value);
    EXPECT_EQ(config.get_comparator_queue(), value);
    EXPECT_EQ(config.bitfield(), static_cast<uint16_t>(value));
}