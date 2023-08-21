/// \file ads101x/configuration.hpp
/// \brief Defines configuration enumerations and the configuration::configuration class.
#ifndef ADS101X___CONFIGURATION_H
#define ADS101X___CONFIGURATION_H

// std
#include <stdint.h>

namespace ads101x {

/// \brief Represents an ADS101X configuration.
class configuration
{
public:
    // CONSTRUCTORS
    /// \brief Creates a default ADS101X configuration.
    configuration();
    /// \brief Creates an ADS101X configuration from an existing bitfield.
    /// \param bitfield The bitfield to create the configuration from.
    configuration(uint16_t bitfield);

    // PROPERTIES
    /// \brief Enumerates the operating mode of the ADS101X.
    enum class operation : uint16_t
    {
        IDLE            = 0b0000000000000000,   ///< Do not start a conversion (WRITE), or not actively performing a conversion (READ)
        CONVERT         = 0b1000000000000000    ///< Start a conversion (WRITE), or is actively performing a conversion (READ)
    };
    /// \brief Sets the operation status.
    /// \param value The value to set.
    void set_operation(configuration::operation value);
    /// \brief Gets the operation status.
    /// \return The operation status.
    configuration::operation get_operation() const;

    /// \brief Enumerates the multiplexer settings of the ADS101X.
    enum class multiplexer : uint16_t
    {
        AIN0_AIN1       = 0b0000000000000000,   ///< Measures voltage of AIN0 in reference to AIN1.
        AIN0_AIN3       = 0b0001000000000000,   ///< Measures voltage of AIN0 in reference to AIN3.
        AIN1_AIN3       = 0b0010000000000000,   ///< Measures voltage of AIN1 in reference to AIN3.
        AIN2_AIN3       = 0b0011000000000000,   ///< Measures voltage of AIN2 in reference to AIN3.
        AIN0_GND        = 0b0100000000000000,   ///< Measures voltage of AIN0 in reference to GND.
        AIN1_GND        = 0b0101000000000000,   ///< Measures voltage of AIN1 in reference to GND.
        AIN2_GND        = 0b0110000000000000,   ///< Measures voltage of AIN2 in reference to GND.
        AIN3_GND        = 0b0111000000000000    ///< Measures voltage of AIN3 in reference to GND.
    };
    /// \brief Sets the multiplexer mode.
    /// \param value The multiplexer mode to set.
    void set_multiplexer(configuration::multiplexer value);
    /// \brief Gets the multiplexer mode.
    /// \return The multiplexer mode.
    configuration::multiplexer get_multiplexer() const;

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
    /// \brief Sets the full scale range.
    /// \param value The full scale range to set.
    void set_fsr(configuration::fsr value);
    /// \brief Gets the full scale range.
    /// \return The full scale range.
    configuration::fsr get_fsr() const;

    /// \brief Enumerates the measurement mode of the ADS101X.
    enum class mode : uint16_t
    {
        CONTINUOUS      = 0b0000000000000000,   ///< Continuous measurement mode.
        SINGLESHOT      = 0b0000000100000000    ///< Single-shot measurement mode.
    };
    /// \brief Sets the measurement mode.
    /// \param value The measurement mode to set.
    void set_mode(configuration::mode value);
    /// \brief Gets the measurement mode.
    /// \return The measurement mode.
    configuration::mode get_mode() const;
    
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
    /// \brief Sets the data rate.
    /// \param value The data rate to set.
    void set_data_rate(configuration::data_rate value);
    /// \brief Gets the data rate.
    /// \return The data rate.
    configuration::data_rate get_data_rate() const;

    /// \brief Enumerates the assertion modes of the ADS101X comparator.
    enum class comparator_mode : uint16_t
    {
        TRADITIONAL     = 0b0000000000000000,   ///< ALERT/RDY pin asserts above HI_THRESH, and deasserts below LO_THRESH.
        WINDOW          = 0b0000000000010000    ///< ALERT/RDY pin asserts outside of HI_THRESH and LO_THRESH, and deasserts within.
    };
    /// \brief Sets the comparator mode.
    /// \param value The comarator mode to set.
    void set_comparator_mode(configuration::comparator_mode value);
    /// \brief Gets the comparator mode.
    /// \return The comparator mode.
    configuration::comparator_mode get_comparator_mode() const;

    /// \brief Enumerates the assertion polarities of the ADS101X comparator.
    enum class comparator_polarity : uint16_t
    {
        ACTIVE_LOW      = 0b0000000000000000,   ///< ALERT/RDY pin driven low when asserted.
        ACTIVE_HIGH     = 0b0000000000001000    ///< ALERT/RDY pin driven high when asserted.
    };
    /// \brief Sets the comparator polarity.
    /// \param value The comparator polarity to set.
    void set_comparator_polarity(configuration::comparator_polarity value);
    /// \brief Gets the comparator polarity.
    /// \return The comparator polarity.
    configuration::comparator_polarity get_comparator_polarity() const;

    /// \brief Enumerates the latching modes of the ADS101X comparator.
    enum class comparator_latch : uint16_t
    {
        NONLATCHING     = 0b0000000000000000,   ///< ALERT/RDY pin does not latch when asserted.
        LATCHING        = 0b0000000000000100    ///< ALERT/RDY pin latches when asserted.
    };
    /// \brief Sets the comparator latch mode.
    /// \param value The comparator latch mode to set.
    void set_comparator_latch(configuration::comparator_latch value);
    /// \brief Gets the comparator latch mode.
    /// \return The comparator latch mode.
    configuration::comparator_latch get_comparator_latch() const;

    /// \brief Enumerates the queue configurations of the ADS101X comparator.
    enum class comparator_queue : uint16_t
    {
        AFTER_1         = 0b0000000000000000,   ///< ALERT/RDY pin asserts after one conversion triggers the comparator.
        AFTER_2         = 0b0000000000000001,   ///< ALERT/RDY pin asserts after two successive conversions trigger the comparator.
        AFTER_4         = 0b0000000000000010,   ///< ALERT/RDY pin asserts after four successive conversions trigger the comparator.
        DISABLED        = 0b0000000000000011    ///< Comparator is disabled and ALERT/RDY pin placed in high impedance.
    };
    /// \brief Sets the comparator queue mode.
    /// \param value The comparator queue mode to set.
    void set_comparator_queue(configuration::comparator_queue value);
    /// \brief Gets the comparator queue mode.
    /// \return The comparator queue mode.
    configuration::comparator_queue get_comparator_queue() const;

    // BITFIELD
    /// \brief Gets the bitfield representation of the configuration.
    /// \return The configuration bitfield.
    uint16_t bitfield() const;

private:
    /// \brief The bitfield representation of the configuration.
    uint16_t m_bitfield;
};

}

#endif