// ads101x
#include <ads101x/configuration.hpp>

// gtest
#include <gtest/gtest.h>

TEST(configuration, default_constructor)
{
    // Create default-constructed configuration.
    ads101x::configuration config;

    // Verify fields.
    EXPECT_EQ(config.operation, ads101x::operation::IDLE);
    EXPECT_EQ(config.multiplexer, ads101x::multiplexer::AIN0_AIN1);
    EXPECT_EQ(config.fsr, ads101x::fsr::FSR_2_048);
    EXPECT_EQ(config.mode, ads101x::mode::MODE_SINGLESHOT);
    EXPECT_EQ(config.data_rate, ads101x::data_rate::SPS_1600);
    EXPECT_EQ(config.comparator_mode, ads101x::comparator_mode::TRADITIONAL);
    EXPECT_EQ(config.comparator_polarity, ads101x::comparator_polarity::ACTIVE_LOW);
    EXPECT_EQ(config.comparator_latch, ads101x::comparator_latch::NONLATCHING);
    EXPECT_EQ(config.comparator_queue, ads101x::comparator_queue::DISABLED);
}

TEST(configuration, read_constructor)
{
    // Create simulated CONFIG register value.
    // NOTE: This is the default startup value for the ADS101X.
    uint16_t config_register = 0x8583;

    // Create read-constructed configuration.
    ads101x::configuration config(config_register);

    // Verify fields.
    EXPECT_EQ(config.operation, ads101x::operation::CONVERT);
    EXPECT_EQ(config.multiplexer, ads101x::multiplexer::AIN0_AIN1);
    EXPECT_EQ(config.fsr, ads101x::fsr::FSR_2_048);
    EXPECT_EQ(config.mode, ads101x::mode::MODE_SINGLESHOT);
    EXPECT_EQ(config.data_rate, ads101x::data_rate::SPS_1600);
    EXPECT_EQ(config.comparator_mode, ads101x::comparator_mode::TRADITIONAL);
    EXPECT_EQ(config.comparator_polarity, ads101x::comparator_polarity::ACTIVE_LOW);
    EXPECT_EQ(config.comparator_latch, ads101x::comparator_latch::NONLATCHING);
    EXPECT_EQ(config.comparator_queue, ads101x::comparator_queue::DISABLED);
}