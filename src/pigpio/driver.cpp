#include <ads101x/pigpio/driver.hpp>

// ads101x
#include <ads101x/pigpio/error.hpp>

// pigpio
#include <pigpio.h>

// std
#include <endian.h>

using namespace ads101x::pigpio;

// CONSTRUCTORS
driver::driver()
    : m_i2c_handle(PI_NO_HANDLE)
{}
driver::~driver()
{
    // Stop the driver if necessary.
    driver::close_i2c();
}

// PIGPIO
void driver::pigpio_initialize()
{
    // Try to initialize the library.
    int32_t result = gpioInitialise();

    // Handle error if present.
    ads101x::pigpio::error(result);
}
void driver::pigpio_terminate()
{
    // Terminate the library.
    gpioTerminate();
}

// OVERRIDES
void driver::open_i2c(uint32_t i2c_bus, uint8_t i2c_address)
{
    // Try to open I2C.
    int32_t result = i2cOpen(i2c_bus, i2c_address, 0);

    // Handle error if present.
    ads101x::pigpio::error(result);

    // Store new handle.
    driver::m_i2c_handle = result;
}
void driver::close_i2c()
{
    // Check if I2C is open.
    if(driver::m_i2c_handle < 0)
    {
        // I2C is already closed.
        return;
    }

    // Try to close I2C.
    int32_t result = i2cClose(driver::m_i2c_handle);

    // Handle error if present.
    ads101x::pigpio::error(result);

    // Reset handle.
    driver::m_i2c_handle = PI_NO_HANDLE;
}
void driver::write_register(uint8_t register_address, uint16_t value) const
{
    // Try to write 16-bit value (big endian) to the register.
    int32_t result = i2cWriteWordData(driver::m_i2c_handle, register_address, htobe16(value));

    // Handle error if present.
    ads101x::pigpio::error(result);
}
uint16_t driver::read_register(uint8_t register_address) const
{
    // Try to read 16-bit value from the register.
    int32_t result = i2cReadWordData(driver::m_i2c_handle, register_address);

    // Handle error if present.
    ads101x::pigpio::error(result);

    // Extract 16-bit value from result, handling endianness.
    return be16toh(static_cast<uint16_t>(result));
}

// ALERT_RDY
void driver::attach_interrupt(uint16_t pin)
{
    // Try to set pin to input mode.
    int32_t result = gpioSetMode(pin, PI_INPUT);
    ads101x::pigpio::error(result);

    // Try to set pin input pullup.
    result = gpioSetPullUpDown(pin, PI_PUD_UP);
    ads101x::pigpio::error(result);

    // Try to attach interrupt.
    result = gpioSetAlertFuncEx(pin, &driver::interrupt_callback, this);
    ads101x::pigpio::error(result);
}
void driver::detach_interrupt(uint16_t pin)
{
    // Try to detach interrupt.
    int32_t result = gpioSetAlertFuncEx(pin, nullptr, nullptr);

    // Handle error if present.
    ads101x::pigpio::error(result);
}
void driver::interrupt_callback(int32_t pin, int32_t level, uint32_t tick, void* data)
{
    // Verify level is not a watchdog timeout.
    if(level == 2)
    {
        return;
    }

    // Convert user data to driver instance.
    ads101x::pigpio::driver* driver = reinterpret_cast<ads101x::pigpio::driver*>(data);

    // Verify driver instance.
    if(!driver)
    {
        return;
    }

    // Raise interrupt on driver.
    driver->raise_interrupt(pin, level);
}