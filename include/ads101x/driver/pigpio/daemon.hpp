/// \file ads101x/driver/pigpio/daemon.hpp
/// \brief Defines the ads101x::driver::pigpio::daemon class.
#ifndef ADS101X___DRIVER___PIGPIO___DAEMON_H
#define ADS101X___DRIVER___PIGPIO___DAEMON_H

// ads101x
#include <ads101x/driver/base.hpp>

namespace ads101x {
namespace driver {
namespace pigpio {

/// \brief An ADS101X driver via pigpio, using the pigpio daemon interface.
/// \note The user must initialize pigpio in their application before using this class.
class daemon
    : public ads101x::driver::base
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new ADS101X driver instance.
    /// \param daemon_handle The handle to the application's open pigpio daemon connection.
    /// \note The application must connect to the pigpio daemon before using this class.
    daemon(int32_t daemon_handle);
    ~daemon();

private:
    // OVERRIDES
    void open_i2c(uint32_t i2c_bus, uint8_t i2c_address) override;
    void close_i2c() override;
    void write_register(uint8_t register_address, uint16_t value) const override;
    uint16_t read_register(uint8_t register_address) const override;

    // HANDLES
    /// \brief Store the handle for an open pigpio daemon connection.
    const int32_t m_daemon_handle;
    /// \brief Stores the handle for an open I2C connection.
    int32_t m_i2c_handle;
};

}}}

#endif