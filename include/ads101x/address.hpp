/// \file ads101x/address.hpp
/// \brief Defines the ads101x::address enumeration.
#ifndef ADS101X___ADDRESS_H
#define ADS101X___ADDRESS_H

// std
#include <stdint.h>

namespace ads101x {

/// \brief An enumeration of I2C register addresses for the ADS101x family.
enum class address : uint8_t
{
    CONVERSION  = 0b00000000,   ///< The conversion register address.
    CONFIG      = 0b00000001,   ///< The configuration register address.
    LO_THRESH   = 0b00000010,   ///< The low threshold register address.
    HI_THRESH   = 0b00000011    ///< The high threshold register address.
};

}

#endif