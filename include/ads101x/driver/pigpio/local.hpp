/// \file ads101x/driver/pigpio/local.hpp
/// \brief Defines the ads101x::driver::pigpio::local class.
#ifndef ADS101X___DRIVER___PIGPIO___LOCAL_H
#define ADS101X___DRIVER___PIGPIO___LOCAL_H

// ads101x
#include <ads101x/driver/base.hpp>

namespace ads101x {
namespace driver {
/// \brief Contains all code for ADS101X drivers built on the pigpio library.
namespace pigpio {

/// \brief An ADS101X driver via pigpio, using a pigpio instance hosted locally by the application.
class local
    : public ads101x::driver::base
{
public:
    // CONSTRUCTORS
    /// \brief Constructs a new ADS101X driver instance.
    local();
    ~local();

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

    // HANDLES
    /// \brief Stores the handle for an open I2C connection.
    int32_t m_i2c_handle;
};

}}}

#endif