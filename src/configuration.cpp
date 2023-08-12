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
    : operation(ads101x::operation::IDLE),
      multiplexer(ads101x::multiplexer::AIN0_AIN1),
      fsr(ads101x::fsr::FSR_2_048),
      mode(ads101x::mode::MODE_SINGLESHOT),
      data_rate(ads101x::data_rate::SPS_1600),
      comparator_mode(ads101x::comparator_mode::TRADITIONAL),
      comparator_polarity(ads101x::comparator_polarity::ACTIVE_LOW),
      comparator_latch(ads101x::comparator_latch::NONLATCHING),
      comparator_queue(ads101x::comparator_queue::DISABLED)
{}
configuration::configuration(uint16_t value)
    : operation(static_cast<ads101x::operation>(value & MASK_OPERATION)),
      multiplexer(static_cast<ads101x::multiplexer>(value & MASK_MULTIPLEXER)),
      fsr(static_cast<ads101x::fsr>(value & MASK_FSR)),
      mode(static_cast<ads101x::mode>(value & MASK_MODE)),
      data_rate(static_cast<ads101x::data_rate>(value & MASK_DATA_RATE)),
      comparator_mode(static_cast<ads101x::comparator_mode>(value & MASK_COMPARATOR_MODE)),
      comparator_polarity(static_cast<ads101x::comparator_polarity>(value & MASK_COMPARATOR_POLARITY)),
      comparator_latch(static_cast<ads101x::comparator_latch>(value & MASK_COMPARATOR_LATCH)),
      comparator_queue(static_cast<ads101x::comparator_queue>(value & MASK_COMPARATOR_QUEUE))
{}

// IO
uint16_t configuration::write() const
{
    // Create output UINT16.
    uint16_t output = 0b0000000000000000;

    // Write properties as value bitmask.
    output |= static_cast<uint16_t>(configuration::operation);
    output |= static_cast<uint16_t>(configuration::multiplexer);
    output |= static_cast<uint16_t>(configuration::fsr);
    output |= static_cast<uint16_t>(configuration::mode);
    output |= static_cast<uint16_t>(configuration::data_rate);
    output |= static_cast<uint16_t>(configuration::comparator_mode);
    output |= static_cast<uint16_t>(configuration::comparator_polarity);
    output |= static_cast<uint16_t>(configuration::comparator_latch);
    output |= static_cast<uint16_t>(configuration::comparator_queue);

    // Return output.
    return output;
}
void configuration::read(uint16_t value)
{
    // Read properties from value bitmask.
    configuration::operation = static_cast<ads101x::operation>(value & MASK_OPERATION);
    configuration::multiplexer = static_cast<ads101x::multiplexer>(value & MASK_MULTIPLEXER);
    configuration::fsr = static_cast<ads101x::fsr>(value & MASK_FSR);
    configuration::mode = static_cast<ads101x::mode>(value & MASK_MODE);
    configuration::data_rate = static_cast<ads101x::data_rate>(value & MASK_DATA_RATE);
    configuration::comparator_mode = static_cast<ads101x::comparator_mode>(value & MASK_COMPARATOR_MODE);
    configuration::comparator_polarity = static_cast<ads101x::comparator_polarity>(value & MASK_COMPARATOR_POLARITY);
    configuration::comparator_latch = static_cast<ads101x::comparator_latch>(value & MASK_COMPARATOR_LATCH);
    configuration::comparator_queue = static_cast<ads101x::comparator_queue>(value & MASK_COMPARATOR_QUEUE);
}