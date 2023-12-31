// ads101x
#include <ads101x/driver.hpp>

// gtest
#include <gtest/gtest.h>

// Create test driver object.
struct test_driver
    : public ads101x::driver
{
    // CONSTRUCTORS
    test_driver()
        : i2c_bus(0),
          i2c_address(0),
          i2c_opened(false),
          i2c_closed(false),
          write_address(0),
          write_value(0),
          read_address(0),
          read_value(0),
          interrupt_pin_attach(0),
          interrupt_pin_detach(0),
          interrupt_attached(false)
    {}

    // OVERRIDES
    void open_i2c(uint32_t i2c_bus, uint8_t i2c_address) override
    {
        // Store bus/address.
        test_driver::i2c_bus = i2c_bus;
        test_driver::i2c_address = i2c_address;

        // Set I2C as open.
        test_driver::i2c_opened = true;
    }
    void close_i2c() override
    {
        // Set I2C as closed.
        test_driver::i2c_closed = true;
    }
    void write_register(uint8_t register_address, uint16_t value) const override
    {
        // Store write address and value.
        test_driver::write_address = register_address;
        test_driver::write_value = value;
    }
    uint16_t read_register(uint8_t register_address) const override
    {
        // Store read address.
        test_driver::read_address = register_address;

        // Return read value.
        return test_driver::read_value;
    }
    void attach_interrupt(uint16_t pin) override
    {
        // Store interrupt pin.
        test_driver::interrupt_pin_attach = pin;

        // Flag interrupt attached.
        test_driver::interrupt_attached = true;
    }
    void detach_interrupt(uint16_t pin) override
    {
        // Store interrupt pin.
        test_driver::interrupt_pin_detach = pin;

        // Flag interrupt attached.
        test_driver::interrupt_attached = false;
    }

    // ALERT_RDY
    void simulate_interrupt(uint16_t pin, bool level)
    {
        test_driver::raise_interrupt(pin, level);
    }

    // STATE: I2C
    uint32_t i2c_bus;
    uint8_t i2c_address;
    bool i2c_opened;
    bool i2c_closed;

    // STATE: WRITE
    mutable uint8_t write_address;
    mutable uint16_t write_value;

    // STATE: READ
    mutable uint8_t read_address;
    mutable uint16_t read_value;

    // STATE: INTERRUPT
    mutable uint16_t interrupt_pin_attach;
    mutable uint16_t interrupt_pin_detach;
    mutable bool interrupt_attached;
};

// ALERT_RDY
void alert_rdy_callback(bool level, bool* output)
{
    *output = level;
}

// CONTROL
TEST(driver, start)
{
    // Select I2C bus and address.
    uint32_t i2c_bus = 0x12345678;
    ads101x::slave_address i2c_address = ads101x::slave_address::SDA_PIN;

    // Create test driver.
    test_driver driver;

    // Start I2C.
    driver.start(i2c_bus, i2c_address);

    // Verify driver state.
    EXPECT_EQ(driver.i2c_bus, i2c_bus);
    EXPECT_EQ(driver.i2c_address, static_cast<uint8_t>(i2c_address));
    EXPECT_TRUE(driver.i2c_opened);
    EXPECT_TRUE(driver.i2c_closed);
}
TEST(driver, stop)
{
    // Create test driver.
    test_driver driver;

    // Stop I2C.
    driver.stop();

    // Verify driver state.
    EXPECT_TRUE(driver.i2c_closed);
}

// CONFIGURATION
TEST(driver, write_config)
{
    // Create test driver.
    test_driver driver;

    // Specify configuration value and create config structure from it.
    uint16_t config_value = 0x1234;
    ads101x::configuration config(config_value);

    // Write configuration.
    driver.write_config(config);

    // Verify driver state.
    EXPECT_EQ(driver.write_address, static_cast<uint8_t>(ads101x::register_address::CONFIG));
    EXPECT_EQ(driver.write_value, config_value);
}
TEST(driver, read_config)
{
    // Create test driver.
    test_driver driver;

    // Specify test config value.
    uint16_t config_value = 0x1234;

    // Configure test driver's read value.
    driver.read_value = config_value;

    // Read configuration.
    ads101x::configuration config = driver.read_config();

    // Verify driver state.
    EXPECT_EQ(driver.read_address, static_cast<uint8_t>(ads101x::register_address::CONFIG));

    // Verify read value.
    EXPECT_EQ(config.bitfield(), config_value);
}

// CONVERSION
TEST(driver, read_conversion)
{
    // Create test driver.
    test_driver driver;

    // Specify 12-bit test conversion value.
    uint16_t conversion_value = 0b0000101010101010;

    // Cnfigure test driver's read value (12bit, MSB aligned)
    driver.read_value = conversion_value << 4;

    // Read conversion.
    uint16_t conversion = driver.read_conversion();

    // Verify driver state.
    EXPECT_EQ(driver.read_address, static_cast<uint8_t>(ads101x::register_address::CONVERSION));

    // Verify read value.
    EXPECT_EQ(conversion, conversion_value);
}

// THRESHOLDS
TEST(driver, write_lo_thresh)
{
    // Create test driver.
    test_driver driver;

    // Specify 12-bit test threshold value.
    uint16_t threshold_value = 0b0000101010101010;

    // Write threshold.
    driver.write_lo_thresh(threshold_value);

    // Verify driver state.
    EXPECT_EQ(driver.write_address, static_cast<uint8_t>(ads101x::register_address::LO_THRESH));
    EXPECT_EQ(driver.write_value, threshold_value << 4);
}
TEST(driver, read_lo_thresh)
{
    // Create test driver.
    test_driver driver;

    // Specify 12-bit test threshold value.
    uint16_t threshold_value = 0b0000101010101010;

    // Configure test driver read value (MSB aligned).
    driver.read_value = threshold_value << 4;

    // Read threshold.
    uint16_t threshold = driver.read_lo_thresh();

    // Verify driver state.
    EXPECT_EQ(driver.read_address, static_cast<uint8_t>(ads101x::register_address::LO_THRESH));

    // Verify read value.
    EXPECT_EQ(threshold, threshold_value);
}
TEST(driver, write_hi_thresh)
{
    // Create test driver.
    test_driver driver;

    // Specify 12-bit test threshold value.
    uint16_t threshold_value = 0b0000101010101010;

    // Write threshold.
    driver.write_hi_thresh(threshold_value);

    // Verify driver state.
    EXPECT_EQ(driver.write_address, static_cast<uint8_t>(ads101x::register_address::HI_THRESH));
    EXPECT_EQ(driver.write_value, threshold_value << 4);
}
TEST(driver, read_hi_thresh)
{
    // Create test driver.
    test_driver driver;

    // Specify 12-bit test threshold value.
    uint16_t threshold_value = 0b0000101010101010;

    // Configure test driver read value (MSB aligned).
    driver.read_value = threshold_value << 4;

    // Read threshold.
    uint16_t threshold = driver.read_hi_thresh();

    // Verify driver state.
    EXPECT_EQ(driver.read_address, static_cast<uint8_t>(ads101x::register_address::HI_THRESH));

    // Verify read value.
    EXPECT_EQ(threshold, threshold_value);
}

// ALERT_RDY
TEST(driver, alert_rdy)
{
    // Create test driver.
    test_driver driver;

    // Specify ALERT_RDY pin.
    uint32_t alert_rdy_pin = 8;

    // Create output level for capturing callback result.
    bool level_output = false;

    // Attach alert_rdy callback.
    driver.attach_alert_rdy(alert_rdy_pin, std::bind(&alert_rdy_callback, std::placeholders::_1, &level_output));

    // Verify that interrupt is attached.
    EXPECT_EQ(driver.interrupt_pin_attach, alert_rdy_pin);
    EXPECT_TRUE(driver.interrupt_attached);

    // Simulate rising edge interrupt and verify callback raised.
    driver.simulate_interrupt(alert_rdy_pin, true);
    EXPECT_TRUE(level_output);

    // Simulate falling edge interrupt and verify callback raised.
    driver.simulate_interrupt(alert_rdy_pin, false);
    EXPECT_FALSE(level_output);

    // Detach alert_rdy.
    driver.detach_alert_rdy();

    // Verify that interrupt is detached.
    EXPECT_EQ(driver.interrupt_pin_detach, alert_rdy_pin);
    EXPECT_FALSE(driver.interrupt_attached);
}