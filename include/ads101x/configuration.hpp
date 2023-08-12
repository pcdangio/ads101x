/// \file ads101x/configuration.hpp
/// \brief Defines configuration enumerations and the ads101x::configuration class.
#ifndef ADS101X___CONFIGURATION_H
#define ADS101X___CONFIGURATION_H

// std
#include <stdint.h>

namespace ads101x {

// PROPERTIES
/// \brief Enumerates the operating mode of the ADS101X.
enum class operation : uint16_t
{
    IDLE            = 0b0000000000000000,   ///< Do not start a conversion (WRITE), or not actively performing a conversion (READ)
    CONVERT         = 0b1000000000000000    ///< Start a conversion (WRITE), or is actively performing a conversion (READ)
};
/// \brief Enumerates the multiplexer settings of the ADS101X.
enum class multiplexer : uint16_t
{
    AIN0_AIN1       = 0b0000000000000000,   ///< Differential measurement between AIN0 and AIN1.
    AIN0_AIN3       = 0b0001000000000000,   ///< Differential measurement between AIN0 and AIN3.
    AIN1_AIN3       = 0b0010000000000000,   ///< Differential measurement between AIN1 and AIN3.
    AIN2_AIN3       = 0b0011000000000000,   ///< Differential measurement between AIN2 and AIN3.
    AIN0            = 0b0100000000000000,   ///< Measurement of AIN0.
    AIN1            = 0b0101000000000000,   ///< Measurement of AIN1.
    AIN2            = 0b0110000000000000,   ///< Measurement of AIN2.
    AIN3            = 0b0111000000000000    ///< Measurement of AIN3.
};
/// \brief Enumerates the full-scale range (FSR) of the ADS101X.
enum class fsr : uint16_t
{
    FSR_6_114       = 0b0000000000000000,   ///< +/- 6.114V FSR
    FSR_4_096       = 0b0000001000000000,   ///< +/- 4.096V FSR
    FSR_2_048       = 0b0000010000000000,   ///< +/- 2.048V FSR
    FSR_1_024       = 0b0000011000000000,   ///< +/- 1.024V FSR
    FSR_0_512       = 0b0000100000000000,   ///< +/- 0.512V FSR
    FSR_0_256       = 0b0000101000000000    ///< +/- 0.256V FSR
};
/// \brief Enumerates the measurement mode of the ADS101X.
enum class mode : uint16_t
{
    MODE_CONTINUOUS = 0b0000000000000000,   ///< Continuous measurement mode.
    MODE_SINGLESHOT = 0b0000000100000000    ///< Single-shot measurement mode.
};
/// \brief Enumerates the sampling data rate of the ADS101X.
enum class data_rate : uint16_t
{
    SPS_128         = 0b0000000000000000,   ///< 128 samples per second.
    SPS_250         = 0b0000000000100000,   ///< 250 samples per second.
    SPS_490         = 0b0000000001000000,   ///< 490 samples per second.
    SPS_920         = 0b0000000001100000,   ///< 920 samples per second.
    SPS_1600        = 0b0000000010000000,   ///< 1600 samples per second.
    SPS_2400        = 0b0000000010100000,   ///< 2400 samples per second.
    SPS_3300        = 0b0000000011000000    ///< 3300 samples per second.
};
/// \brief Enumerates the assertion modes of the ADS101X comparator.
enum class comparator_mode : uint16_t
{
    TRADITIONAL     = 0b0000000000000000,   ///< ALERT/RDY pin asserts above HI_THRESH, and deasserts below LO_THRESH.
    WINDOW          = 0b0000000000010000    ///< ALERT/RDY pin asserts outside of HI_THRESH and LO_THRESH, and deasserts within.
};
/// \brief Enumerates the assertion polarities of the ADS101X comparator.
enum class comparator_polarity : uint16_t
{
    ACTIVE_LOW      = 0b0000000000000000,   ///< ALERT/RDY pin driven low when asserted.
    ACTIVE_HIGH     = 0b0000000000001000    ///< ALERT/RDY pin driven high when asserted.
};
/// \brief Enumerates the latching modes of the ADS101X comparator.
enum class comparator_latch : uint16_t
{
    NONLATCHING     = 0b0000000000000000,   ///< ALERT/RDY pin does not latch when asserted.
    LATCHING        = 0b0000000000000100    ///< ALERT/RDY pin latches when asserted.
};
/// \brief Enumerates the queue configurations of the ADS101X comparator.
enum class comparator_queue : uint16_t
{
    AFTER_1         = 0b0000000000000000,   ///< ALERT/RDY pin asserts after one conversion triggers the comparator.
    AFTER_2         = 0b0000000000000001,   ///< ALERT/RDY pin asserts after two successive conversions trigger the comparator.
    AFTER_4         = 0b0000000000000010,   ///< ALERT/RDY pin asserts after four successive conversions trigger the comparator.
    DISABLED        = 0b0000000000000011    ///< Comparator is disabled and ALERT/RDY pin placed in high impedance.
};

// OBJECTS
/// \brief Represents an ADS101X configuration.
struct configuration
{
    // CONSTRUCTORS
    /// \brief Creates a default ADS101X configuration.
    configuration();
    /// \brief Creates an ADS101X configuration from a CONFIG register value.
    configuration(uint16_t value);

    // PROPERTIES
    /// \brief The operating mode of the ADS101X.
    ads101x::operation operation;
    /// \brief The multiplexer setting of the ADS101X.
    ads101x::multiplexer multiplexer;
    /// \brief The full scale range of teh ADS101X.
    ads101x::fsr fsr;
    /// \brief The measurement mode of the ADS101X.
    ads101x::mode mode;
    /// \brief The sampling data rate of the ADS101X.
    ads101x::data_rate data_rate;
    /// \brief The assertion modes of the ADS101X comparator.
    ads101x::comparator_mode comparator_mode;
    /// \brief The assertion polarities of the ADS101X comparator.
    ads101x::comparator_polarity comparator_polarity;
    /// \brief The latching modes of the ADS101X comparator.
    ads101x::comparator_latch comparator_latch;
    /// \brief The queue configurations of the ADS101X comparator.
    ads101x::comparator_queue comparator_queue;

    // IO
    /// \brief Writes the configuration to a UINT16 for use in the CONFIG register.
    /// \returns The configuration written as a UINT16 bitfield.
    uint16_t write() const;
    /// \brief Reads the configuration from a UINT16 value retrieved from the CONFIG register.
    /// \param value The UINT16 bitfield to read from.
    void read(uint16_t value);
};

}

#endif