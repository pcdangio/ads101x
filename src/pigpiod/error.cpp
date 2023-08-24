#include <ads101x/pigpiod/error.hpp>

// ads101x
#include <ads101x/pigpio/error.hpp>

// pigpio
#include <pigpiod_if2.h>

// std
#include <string>
#include <stdexcept>

void ads101x::pigpiod::error(int32_t result)
{
    // Check if this result needs to be handled by the pigpiod handler.
    if(result > PI_PIGIF_ERR_0)
    {
        // Use pigpio error handler.
        return ads101x::pigpio::error(result);
    }

    // Create base string for excepion message.
    std::string message = "pigpiod error: ";

    // Handle pigpiod error.
    switch(result)
    {
        case pigif_bad_send:
        {
            message += "failed to transmit to daemon";
            break;
        }
        case pigif_bad_recv:
        {
            message += "failed to receive from daemon";
            break;
        }
        case pigif_bad_connect:
        {
            message += "failed to connect to daemon";
            break;
        }
        case pigif_bad_socket:
        {
            message += "daemon connection socket failed";
            break;
        }
        case pigif_unconnected_pi:
        {
            message += "not connected to daemon";
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