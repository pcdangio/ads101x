#include <ads101x/driver.hpp>

using namespace ads101x;

// CONTROL
void driver::start(uint32_t i2c_bus, ads101x::slave_address slave_address)
{
    // Close I2C if necessary.
    close_i2c();
    
    // Open I2C.
    open_i2c(i2c_bus, static_cast<uint8_t>(slave_address));
}
void driver::stop()
{
    // Close I2C.
    close_i2c();
}

// CONFIGURATION
void driver::write_config(const ads101x::configuration& configuration) const
{
    // Write the configuration bitfield to the config register.
    write_register(static_cast<uint8_t>(ads101x::register_address::CONFIG), configuration.bitfield());
}
ads101x::configuration driver::read_config() const
{
    // Read the config register and return a new configuration instance.
    return ads101x::configuration(read_register(static_cast<uint8_t>(ads101x::register_address::CONFIG)));
}

// CONVERSION
uint16_t driver::read_conversion() const
{
    // Read the conversion register.
    uint16_t value = read_register(static_cast<uint8_t>(ads101x::register_address::CONVERSION));

    // Conversion is stored as 12bit at MSB. Shift right 4 bits.
    return value >> 4;
}

// THRESHOLDS
void driver::write_lo_thresh(uint16_t value) const
{
    // Thresholds are stored as 12bit at MSB. Shift left 4 bits.
    value = value << 4;

    // Write threshold register.
    write_register(static_cast<uint8_t>(ads101x::register_address::LO_THRESH), value);
}
uint16_t driver::read_lo_thresh() const
{
    // Read threshold register.
    uint16_t value = read_register(static_cast<uint8_t>(ads101x::register_address::LO_THRESH));

    // Threshold is stored as 12bit at MSB. Shift right 4 bits.
    return value >> 4;
}
void driver::write_hi_thresh(uint16_t value) const
{
    // Thresholds are stored as 12bit at MSB. Shift left 4 bits.
    value = value << 4;

    // Write threshold register.
    write_register(static_cast<uint8_t>(ads101x::register_address::HI_THRESH), value);
}
uint16_t driver::read_hi_thresh() const
{
    // Read threshold register.
    uint16_t value = read_register(static_cast<uint8_t>(ads101x::register_address::HI_THRESH));

    // Threshold is stored as 12bit at MSB. Shift right 4 bits.
    return value >> 4;
}