/// \file ads101x/pigpiod/error.hpp
/// \brief Defines the ads101x::pigpiod::error function.
#ifndef ADS101X___PIGPIOD___ERROR_H
#define ADS101X___PIGPIOD___ERROR_H

// std
#include <stdint.h>

namespace ads101x {
namespace pigpiod {

/// \brief Checks if a pipgiod result represents an error code, and throws an std::runtime_error.
/// \param result The pigpiod result to handle.
/// \exception std::runtime_error if the result represents an error code.
void error(int32_t result);

}}

#endif