#include <ads101x/driver.hpp>

// std
#include <stdexcept>

using namespace ads101x;

// CONSTRUCTORS
driver::driver()
    : m_alert_rdy_pin(0),
      m_alert_rdy_callback(nullptr),
      m_alert_rdy_attached(false)
{}

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

// ALERT_RDY
void driver::attach_interrupt(uint32_t pin) const
{
    // Default / non-overridden function does not support interrupts.
    throw std::runtime_error("driver does not support interrupts");
}
void driver::detach_interrupt(uint32_t pin) const
{
    // Default / non-overriden function does nothing.
}
void driver::attach_alert_rdy(uint32_t pin, std::function<void(bool)> callback)
{
    // Verify callback.
    if(!callback)
    {
        throw std::runtime_error("alert_rdy callback is invalid");
    }

    // Detach any prior attachment.
    driver::detach_alert_rdy();

    // Try to attach interrupt.
    attach_interrupt(pin);

    // Store pin and callback.
    driver::m_alert_rdy_pin = pin;
    driver::m_alert_rdy_callback = callback;

    // Flag alert_rdy as attached.
    driver::m_alert_rdy_attached = true;
}
void driver::detach_alert_rdy()
{
    // Check if attached.
    if(!driver::m_alert_rdy_attached)
    {
        // Not attached, quit.
        return;
    }

    // Detach the interrupt.
    detach_interrupt(driver::m_alert_rdy_pin);

    // Reset pin and callback.
    driver::m_alert_rdy_pin = 0;
    driver::m_alert_rdy_callback = nullptr;

    // Flag alert_rdy as not attached.
    driver::m_alert_rdy_attached = false;
}
void driver::raise_alert_rdy(bool level)
{
    // Check if attached and validate callback.
    if(!driver::m_alert_rdy_attached || !driver::m_alert_rdy_callback)
    {
        return;
    }

    // Raise the alert_rdy callback.
    driver::m_alert_rdy_callback(level);
}