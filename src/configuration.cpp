#include <ads101x/configuration.hpp>

// BIT MASK
#define MASK_OPERATION              0b1000000000000000
#define MASK_MULTIPLEXER            0b0111000000000000
#define MASK_FSR                    0b0000111000000000
#define MASK_MODE                   0b0000000100000000
#define MASK_DATA_RATE              0b0000000011100000
#define MASK_COMPARATOR_MODE        0b0000000000010000
#define MASK_COMPARATOR_POLARITY    0b0000000000001000
#define MASK_COMPARATOR_LATCH       0b0000000000000100
#define MASK_COMPARATOR_QUEUE       0b0000000000000011

using namespace ads101x;

// CONSTRUCTORS
configuration::configuration()
    : m_bitfield(0x0583)
{}
configuration::configuration(uint16_t bitfield)
    : m_bitfield(bitfield)
{}

// PROPERTIES
void configuration::set_operation(configuration::operation value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_OPERATION) | static_cast<uint16_t>(value);
}
configuration::operation configuration::get_operation() const
{
    // Read value from bitfield.
    return static_cast<configuration::operation>(configuration::m_bitfield & MASK_OPERATION);
}
void configuration::set_multiplexer(configuration::multiplexer value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_MULTIPLEXER) | static_cast<uint16_t>(value);
}
configuration::multiplexer configuration::get_multiplexer() const
{
    // Read value from bitfield.
    return static_cast<configuration::multiplexer>(configuration::m_bitfield & MASK_MULTIPLEXER);
}
void configuration::set_fsr(configuration::fsr value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_FSR) | static_cast<uint16_t>(value);
}
configuration::fsr configuration::get_fsr() const
{
    // Read value from bitfield.
    return static_cast<configuration::fsr>(configuration::m_bitfield & MASK_FSR);
}
void configuration::set_mode(configuration::mode value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_MODE) | static_cast<uint16_t>(value);
}
configuration::mode configuration::get_mode() const
{
    // Read value from bitfield.
    return static_cast<configuration::mode>(configuration::m_bitfield & MASK_MODE);
}
void configuration::set_data_rate(configuration::data_rate value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_DATA_RATE) | static_cast<uint16_t>(value);
}
configuration::data_rate configuration::get_data_rate() const
{
    // Read value from bitfield.
    return static_cast<configuration::data_rate>(configuration::m_bitfield & MASK_DATA_RATE);
}
void configuration::set_comparator_mode(configuration::comparator_mode value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_COMPARATOR_MODE) | static_cast<uint16_t>(value);
}
configuration::comparator_mode configuration::get_comparator_mode() const
{
    // Read value from bitfield.
    return static_cast<configuration::comparator_mode>(configuration::m_bitfield & MASK_COMPARATOR_MODE);
}
void configuration::set_comparator_polarity(configuration::comparator_polarity value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_COMPARATOR_POLARITY) | static_cast<uint16_t>(value);
}
configuration::comparator_polarity configuration::get_comparator_polarity() const
{
    // Read value from bitfield.
    return static_cast<configuration::comparator_polarity>(configuration::m_bitfield & MASK_COMPARATOR_POLARITY);
}
void configuration::set_comparator_latch(configuration::comparator_latch value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_COMPARATOR_LATCH) | static_cast<uint16_t>(value);
}
configuration::comparator_latch configuration::get_comparator_latch() const
{
    // Read value from bitfield.
    return static_cast<configuration::comparator_latch>(configuration::m_bitfield & MASK_COMPARATOR_LATCH);
}
void configuration::set_comparator_queue(configuration::comparator_queue value)
{
    // Clear bits location in bitfield using mask, and then set to provided value.
    configuration::m_bitfield = (configuration::m_bitfield & !MASK_COMPARATOR_QUEUE) | static_cast<uint16_t>(value);
}
configuration::comparator_queue configuration::get_comparator_queue() const
{
    // Read value from bitfield.
    return static_cast<configuration::comparator_queue>(configuration::m_bitfield & MASK_COMPARATOR_QUEUE);
}

// BITFIELD
uint16_t configuration::bitfield() const
{
    return configuration::m_bitfield;
}