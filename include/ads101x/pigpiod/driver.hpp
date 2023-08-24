/// \file ads101x/pigpiod/driver.hpp
/// \brief Defines the ads101x::pigpiod::driver class.
#ifndef ADS101X___PIGPIOD___DRIVER_H
#define ADS101X___PIGPIOD___DRIVER_H

// ads101x
#include <ads101x/driver.hpp>

// std
#include <string>

namespace ads101x {
/// \brief Contains all code for ADS101X drivers built on the pigpiod library.
namespace pigpiod {

/// \brief An ADS101X driver implemented via pigpiod.
class driver
    : public ads101x::driver
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new ADS101X driver instance.
    driver();
    /// \brief Constructs a new ADS101X driver instance using an existing pigpio daemon connection.
    /// \param daemon_handle The handle to the application's existing pigpio daemon connection.
    driver(int32_t daemon_handle);
    ~driver();

    // PIGPIO
    /// \brief Connects to the pigpio daemon.
    /// \param ip_address The IP address of the host running the pigpio daemon.
    /// \param port The port to communicate with the pigpio daemon on the host.
    /// \exception std::runtime_error if the connection fails.
    void pigpiod_connect(const std::string& ip_address = "localhost", uint16_t port = 8888);
    /// \brief Disconnects from the pigpio daemon.
    void pigpiod_disconnect();
    /// \brief Gets the handle for the driver's pigpio daemon connection.
    /// \return If connected, returns the handle. If not connected, returns PI_NO_HANDLE.
    int32_t pigpiod_handle() const;

private:
    // OVERRIDES
    void open_i2c(uint32_t i2c_bus, uint8_t i2c_address) override;
    void close_i2c() override;
    void write_register(uint8_t register_address, uint16_t value) const override;
    uint16_t read_register(uint8_t register_address) const override;

    // HANDLES
    /// \brief Store the handle for an open pigpio daemon connection.
    int32_t m_daemon_handle;
    /// \brief Stores the handle for an open I2C connection.
    int32_t m_i2c_handle;
};

}}

#endif