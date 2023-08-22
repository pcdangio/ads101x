#include <ads101x/driver/pigpio/daemon.hpp>

// ads101x
#include <ads101x/driver/pigpio/error.hpp>

// pigpio
#include <pigpiod_if2.h>

// std
#include <endian.h>

using namespace ads101x::driver::pigpio;

// CONSTRUCTORS
daemon::daemon(int32_t daemon_handle)
    : m_daemon_handle(daemon_handle),
      m_i2c_handle(PI_NO_HANDLE)
{}
daemon::~daemon()
{
    // Stop the driver if necessary.
    daemon::close_i2c();
}

// OVERRIDES
void daemon::open_i2c(uint32_t i2c_bus, uint8_t i2c_address)
{
    // Try to open I2C.
    int32_t result = i2c_open(daemon::m_daemon_handle, i2c_bus, i2c_address, 0);

    // Handle error if present.
    ads101x::driver::pigpio::error(result);

    // Store new handle.
    daemon::m_i2c_handle = result;
}
void daemon::close_i2c()
{
    // Try to close I2C.
    int32_t result = i2c_close(daemon::m_daemon_handle, daemon::m_i2c_handle);

    // Handle error if present.
    ads101x::driver::pigpio::error(result);

    // Reset handle.
    daemon::m_i2c_handle = PI_NO_HANDLE;
}
void daemon::write_register(uint8_t register_address, uint16_t value) const
{
    // Try to write 16-bit value (big endian) to the register.
    int32_t result = i2c_write_word_data(daemon::m_daemon_handle, daemon::m_i2c_handle, register_address, htobe16(value));

    // Handle error if present.
    ads101x::driver::pigpio::error(result);
}
uint16_t daemon::read_register(uint8_t register_address) const
{
    // Try to read 16-bit value from the register.
    int32_t result = i2c_read_word_data(daemon::m_daemon_handle, daemon::m_i2c_handle, register_address);

    // Handle error if present.
    ads101x::driver::pigpio::error(result);

    // Extract 16-bit value from result, handling endianness.
    return be16toh(static_cast<uint16_t>(result));
}