/// \file ads101x/driver.hpp
/// \brief Defines the ads101x::driver class.
#ifndef ADS101X___DRIVER_H
#define ADS101X___DRIVER_H

// ads101x
#include <ads101x/address.hpp>
#include <ads101x/configuration.hpp>

// std
#include <functional>

/// \brief Contains all code for the ADS101X driver.
namespace ads101x {

/// \brief An abstract, base driver class for interacting with the ADS101X analog to digital converter.
class driver
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new driver instance.
    driver();

    // CONTROL
    /// \brief Starts the driver by opening I2C communication with the ADS101X.
    /// \param i2c_bus The I2C bus to use for communication.
    /// \param slave_address The slave address assigned to the ADS101X via its ADDR_PIN connection.
    /// \exception std::runtime_error if the driver fails to open the I2C connection.
    void start(uint32_t i2c_bus = 0, ads101x::slave_address slave_address = ads101x::slave_address::GND_PIN);
    /// \brief Stops the driver by closing I2C communication with the ADS101X.
    /// \exception std::runtime_error if the driver fails to close the I2C connection.
    void stop();

    // CONFIGURATION
    /// \brief Writes a configuration to the ADS101X.
    /// \param configuration The configuration to write.
    /// \exception std::runtime_error if the write command fails.
    void write_config(const ads101x::configuration& configuration) const;
    /// \brief Reads the configuration from the ADS101X.
    /// \return The current configuration stored on the ADS101X.
    /// \exception std::runtime_error if the read command fails.
    ads101x::configuration read_config() const;

    // CONVERSION
    /// \brief Reads the conversion value from the ADS101X.
    /// \return The 12bit conversion value.
    /// \exception std::runtime_error if the read command fails.
    uint16_t read_conversion() const;

    // THRESHOLDS
    /// \brief Writes a comparator low threshold value to the ADS101X.
    /// \param value The 12-bit low threshold value to write.
    /// \exception std::runtime_error if the write command fails.
    void write_lo_thresh(uint16_t value) const;
    /// \brief Reads the comparator low threshold value from the ADS101X.
    /// \return The current 12-bit low threshold value.
    /// \exception std::runtime error if the read command fails.
    uint16_t read_lo_thresh() const;
    /// \brief Writes a comparator high threshold value to the ADS101X.
    /// \param value The 12-bit high threshold value to write.
    /// \exception std::runtime_error if the write command fails.
    void write_hi_thresh(uint16_t value) const;
    /// \brief Reads the comparator high threshold value from the ADS101X.
    /// \return The current 12-bit high threshold value.
    /// \exception std::runtime error if the read command fails.
    uint16_t read_hi_thresh() const;

    // ALERT_RDY
    /// \brief Attaches to an ALERT_RDY notification using a callback.
    /// \param pin The GPIO pin that is attached to the ADS101X ALERT_RDY pin.
    /// \param callback The callback to raise when the ALERT_RDY pin changes state.
    /// \exception std::runtime_error if attach operation fails.
    void attach_alert_rdy(uint16_t pin, std::function<void(bool)> callback);
    /// \brief Detaches from the ALERT_RDY notification.
    /// \exception std::runtime_error if the detach operation fails.
    void detach_alert_rdy();
    
protected:
    // I2C
    /// \brief Opens the I2C session.
    /// \param i2c_bus The bus number of the I2C session to open.
    /// \param i2c_address The address of the I2C device to communicate with.
    /// \exception std::runtime_error if the I2C session fails to open.
    virtual void open_i2c(uint32_t i2c_bus, uint8_t i2c_address) = 0;
    /// \brief Closes the current I2C session.
    /// \exception std::runtime_error if the I2C session fails to close.
    virtual void close_i2c() = 0;
    /// \brief Writes two bytes to an ADS1015 register over I2C.
    /// \param register_address The address of the register to write.
    /// \param value The value to write.
    /// \exception std::runtime_error if the I2C write fails.
    virtual void write_register(uint8_t register_address, uint16_t value) const = 0;
    /// \brief Reads two bytes from an ADS1015 register over I2C.
    /// \param register_address The address of the register to read.
    /// \returns The read value.
    /// \exception std::runtime_error if the I2C read fails.
    virtual uint16_t read_register(uint8_t register_address) const = 0;

    // ALERT_RDY
    /// \brief Attaches a state-change interrupt to a GPIO pin.
    /// \param pin The GPIO pin to attach the interrupt to.
    /// \exception std::runtime_error if the attach operation fails.
    virtual void attach_interrupt(uint16_t pin);
    /// \brief Detaches an interrupt from a GPIO pin.
    /// \param pin The GPIO pin to detach the interrupt from.
    /// \exception std::runtime_error if the detach operation fails.
    virtual void detach_interrupt(uint16_t pin);
    /// \brief Raises an interrupt for a GPIO pin state-change.
    /// \param pin The GPIO pin that has changed state.
    /// \param level The new level of the GPIO pin.
    void raise_interrupt(uint16_t pin, bool level);

private:
    // ALERT_RDY
    /// \brief The GPIO pin connected to the ADS101X ALERT_RDY pin.
    uint32_t m_alert_rdy_pin;
    /// \brief The user callback for ALERT_RDY state-change interrupts.
    std::function<void(bool)> m_alert_rdy_callback;
    /// \brief Indicates if the alert_rdy interrupt is attached.
    bool m_alert_rdy_attached;
};

}

#endif