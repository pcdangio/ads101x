/// \file ads101x/driver/pigpio/error.hpp
/// \brief Defines the ads101x::driver::pigpio::error function.
#ifndef ADS101X___DRIVER___PIGPIO___ERROR_H
#define ADS101X___DRIVER___PIGPIO___ERROR_H

// std
#include <stdint.h>

namespace ads101x {
namespace driver {
namespace pigpio {

/// \brief Checks if a pipgio result represents an error code, and throws an std::runtime_error.
/// \param result The pigpio result to handle.
/// \exception std::runtime_error if the result represents an error code.
void error(int32_t result);

}}}

#endif