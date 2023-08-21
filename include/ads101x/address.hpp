/// \file ads101x/address.hpp
/// \brief Defines the ads101x::address enumeration.
#ifndef ADS101X___ADDRESS_H
#define ADS101X___ADDRESS_H

// std
#include <stdint.h>

namespace ads101x {

/// \brief An enumeration of I2C slave addresses for the ADS101x family.
enum class slave_address : uint8_t
{
    GND_PIN     = 0b01001000,   ///< Slave address when ADDR_PIN is connected to GND_PIN.
    VDD_PIN     = 0b01001001,   ///< Slave address when ADDR_PIN is connected to VDD_PIN.
    SDA_PIN     = 0b01001010,   ///< Slave address when ADDR_PIN is connected to SDA_PIN.
    SCL_PIN     = 0b01001011    ///< Slave address when ADDR_PIN is connected to SCL_PIN.
};

/// \brief An enumeration of I2C register addresses for the ADS101x family.
enum class register_address : uint8_t
{
    CONVERSION  = 0b00000000,   ///< The conversion register address.
    CONFIG      = 0b00000001,   ///< The configuration register address.
    LO_THRESH   = 0b00000010,   ///< The low threshold register address.
    HI_THRESH   = 0b00000011    ///< The high threshold register address.
};

}

#endif