#include <ads101x/pigpiod/driver.hpp>

// ads101x
#include <ads101x/pigpiod/error.hpp>

// pigpio
#include <pigpiod_if2.h>

// std
#include <endian.h>

using namespace ads101x::pigpiod;

// CONSTRUCTORS
driver::driver()
    : m_daemon_handle(PI_NO_HANDLE),
      m_i2c_handle(PI_NO_HANDLE)
{}
driver::driver(int32_t daemon_handle)
    : m_daemon_handle(daemon_handle),
      m_i2c_handle(PI_NO_HANDLE)
{}
driver::~driver()
{
    // Stop the driver if necessary.
    driver::close_i2c();
}

// PIGPIO
void driver::pigpiod_connect(const std::string& ip_address, uint16_t port)
{
    // Close prior connection if necessary.
    driver::pigpiod_disconnect();

    // Try to connect.
    int32_t result = pigpio_start(ip_address.c_str(), std::to_string(port).c_str());

    // Handle error if necessary.
    ads101x::pigpiod::error(result);

    // Store deamon handle.
    driver::m_daemon_handle = result;
}
void driver::pigpiod_disconnect()
{
    // Check if connected.
    if(driver::m_daemon_handle < 0)
    {
        // Deamon already disconnected.
        return;
    }

    // Disconnect from daemon.
    pigpio_stop(driver::m_daemon_handle);
}
int32_t driver::pigpiod_handle() const
{
    return driver::m_daemon_handle;
}

// OVERRIDES
void driver::open_i2c(uint32_t i2c_bus, uint8_t i2c_address)
{
    // Try to open I2C.
    int32_t result = i2c_open(driver::m_daemon_handle, i2c_bus, i2c_address, 0);

    // Handle error if present.
    ads101x::pigpiod::error(result);

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
    int32_t result = i2c_close(driver::m_daemon_handle, driver::m_i2c_handle);

    // Handle error if present.
    ads101x::pigpiod::error(result);

    // Reset handle.
    driver::m_i2c_handle = PI_NO_HANDLE;
}
void driver::write_register(uint8_t register_address, uint16_t value) const
{
    // Try to write 16-bit value (big endian) to the register.
    int32_t result = i2c_write_word_data(driver::m_daemon_handle, driver::m_i2c_handle, register_address, htobe16(value));

    // Handle error if present.
    ads101x::pigpiod::error(result);
}
uint16_t driver::read_register(uint8_t register_address) const
{
    // Try to read 16-bit value from the register.
    int32_t result = i2c_read_word_data(driver::m_daemon_handle, driver::m_i2c_handle, register_address);

    // Handle error if present.
    ads101x::pigpiod::error(result);

    // Extract 16-bit value from result, handling endianness.
    return be16toh(static_cast<uint16_t>(result));
}

void driver::attach_interrupt(uint16_t pin)
{
    // Try to set the pin for input.
    int32_t result = set_mode(driver::m_daemon_handle, pin, PI_INPUT);
    ads101x::pigpiod::error(result);

    // Try to set the input pin to pull-up.
    result = set_pull_up_down(driver::m_daemon_handle, pin, PI_PUD_UP);
    ads101x::pigpiod::error(result);

    // Try to attach interrupt.
    result = callback_ex(driver::m_daemon_handle, pin, EITHER_EDGE, &driver::interrupt_callback, this);
    ads101x::pigpiod::error(result);

    // Store the callback handle for the pin.
    driver::m_callback_handles[pin] = result;
}
void driver::detach_interrupt(uint16_t pin)
{
    // Try to find the pin in the interrupt callback handle map.
    auto handle_entry = driver::m_callback_handles.find(pin);
    if(handle_entry == driver::m_callback_handles.end())
    {
        // Pin does not have an interrupt callback, no need to detach.
        return;
    }

    // Try to detach interrupt using pin's interrupt callback handle.
    int32_t result = callback_cancel(handle_entry->second);
    ads101x::pigpiod::error(result);

    // Remove the entry from the callback handle map.
    driver::m_callback_handles.erase(handle_entry);
}
void driver::interrupt_callback(int32_t daemon_handle, uint32_t pin, uint32_t level, uint32_t tick, void* data)
{
    // Verify level is not a watchdog timeout.
    if(level == 2)
    {
        return;
    }

    // Convert user data to driver instance.
    ads101x::pigpiod::driver* driver = reinterpret_cast<ads101x::pigpiod::driver*>(data);

    // Verify driver instance.
    if(!driver)
    {
        return;
    }

    // Raise interrupt on driver.
    driver->raise_interrupt(pin, level);
}