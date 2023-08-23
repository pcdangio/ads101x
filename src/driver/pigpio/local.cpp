#include <ads101x/driver/pigpio/local.hpp>

// ads101x
#include <ads101x/driver/pigpio/error.hpp>

// pigpio
#include <pigpio.h>

// std
#include <endian.h>

using namespace ads101x::driver::pigpio;

// CONSTRUCTORS
local::local()
    : m_i2c_handle(PI_NO_HANDLE)
{}
local::~local()
{
    // Stop the driver if necessary.
    local::close_i2c();
}

// PIGPIO
void local::initialize_pigpio()
{
    // Try to initialize the library.
    int32_t result = gpioInitialise();

    // Handle error if present.
    ads101x::driver::pigpio::error(result);
}
void local::terminate_pigpio()
{
    // Terminate the library.
    gpioTerminate();
}

// OVERRIDES
void local::open_i2c(uint32_t i2c_bus, uint8_t i2c_address)
{
    // Try to open I2C.
    int32_t result = i2cOpen(i2c_bus, i2c_address, 0);

    // Handle error if present.
    ads101x::driver::pigpio::error(result);

    // Store new handle.
    local::m_i2c_handle = result;
}
void local::close_i2c()
{
    // Try to close I2C.
    int32_t result = i2cClose(local::m_i2c_handle);

    // Handle error if present.
    ads101x::driver::pigpio::error(result);

    // Reset handle.
    local::m_i2c_handle = PI_NO_HANDLE;
}
void local::write_register(uint8_t register_address, uint16_t value) const
{
    // Try to write 16-bit value (big endian) to the register.
    int32_t result = i2cWriteWordData(local::m_i2c_handle, register_address, htobe16(value));

    // Handle error if present.
    ads101x::driver::pigpio::error(result);
}
uint16_t local::read_register(uint8_t register_address) const
{
    // Try to read 16-bit value from the register.
    int32_t result = i2cReadWordData(local::m_i2c_handle, register_address);

    // Handle error if present.
    ads101x::driver::pigpio::error(result);

    // Extract 16-bit value from result, handling endianness.
    return be16toh(static_cast<uint16_t>(result));
}