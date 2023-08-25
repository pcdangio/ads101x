/// \file ads101x/pigpio/driver.hpp
/// \brief Defines the ads101x::pigio::driver class.
#ifndef ADS101X___PIGPIO___DRIVER_H
#define ADS101X___PIGPIO___DRIVER_H

// ads101x
#include <ads101x/driver.hpp>

namespace ads101x {
/// \brief Contains all code for ADS101X drivers built on the pigpio library.
namespace pigpio {

/// \brief An ADS101X driver implemented via pigpio.
class driver
    : public ads101x::driver
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new ADS101X driver instance.
    driver();
    ~driver();

    // PIGPIO
    /// \brief Initializes the pigpio library for use.
    /// \details Use this convenience function to initialize pigpio if not already done elsewhere in the application.
    /// \exception std::runtime_error if initialization fails.
    void initialize_pigpio();
    /// \brief Terminates the pigpio library and frees resources.
    /// \details Use this convenience function to terminate pigpio if not already done elsewhere in the application.
    void terminate_pigpio();

private:
    // I2C
    void open_i2c(uint32_t i2c_bus, uint8_t i2c_address) override;
    void close_i2c() override;
    void write_register(uint8_t register_address, uint16_t value) const override;
    uint16_t read_register(uint8_t register_address) const override;

    // ALERT_RDY
    void attach_interrupt(uint16_t pin) override;
    void detach_interrupt(uint16_t pin) override;
    /// \brief The callback for pigpio alert interrupts.
    /// \param pin The GPIO pin associated with the alert.
    /// \param level The level change.
    /// \param tick The timestamp of the alert.
    /// \param data User data to pass into the callback.
    static void interrupt_callback(int32_t pin, int32_t level, uint32_t tick, void* data);

    // HANDLES
    /// \brief Stores the handle for an open I2C connection.
    int32_t m_i2c_handle;
};

}}

#endif