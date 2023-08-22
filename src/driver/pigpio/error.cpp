#include <ads101x/driver/pigpio/error.hpp>

// std
#include <stdexcept>

// pigpio
#include <pigpio.h>

void ads101x::driver::pigpio::error(int32_t result)
{
    // Check if the result is not an error.
    if(result >= 0)
    {
        // No error detected, quit.
        return;
    }

    // Create base string for excepion message.
    std::string message = "pigpio error: ";

    // Handle error.
    switch(result)
    {
        case PI_NO_HANDLE:
        {
            message += "no i2c handle";
            break;
        }
        case PI_BAD_HANDLE:
        {
            message += "invalid i2c handle";
            break;
        }
        case PI_I2C_OPEN_FAILED:
        {
            message += "i2c open failed";
            break;
        }
        case PI_BAD_I2C_BUS:
        {
            message += "invalid i2c bus specified";
            break;
        }
        case PI_BAD_I2C_ADDR:
        {
            message += "invalid i2c slave address specified";
            break;
        }
        case PI_BAD_FLAGS:
        {
            message += "invalid i2c open flags specified";
            break;
        }
        case PI_BAD_PARAM:
        {
            message += "invalid parameter";
            break;
        }
        case PI_I2C_WRITE_FAILED:
        {
            message += "i2c write failed";
            break;
        }
        case PI_I2C_READ_FAILED:
        {
            message += "i2c read failed";
            break;
        }
        default:
        {
            message += std::to_string(result);
            break;
        }
    }

    // Throw exception.
    throw std::runtime_error(message);
}