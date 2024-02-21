#ifndef IOP_LIB_SENSORS_SOIL_RESISTIVITY_ARDUINO_HPP
#define IOP_LIB_SENSORS_SOIL_RESISTIVITY_ARDUINO_HPP

#include <soil_resistivity.hpp>

#include <Arduino.h>
#undef HIGH
#undef LOW
#undef OUTPUT

#include <iop-hal/panic.hpp>

namespace sensor {
SoilResistivity::SoilResistivity() noexcept: sensor() {}

auto SoilResistivity::begin() noexcept -> void {}
auto SoilResistivity::measure() noexcept -> uint16_t {
    uint16_t value1 = analogRead(A0);
    delay(500); // NOLINT *-avoid-magic-numbers
    uint16_t value2 = analogRead(A0);
    delay(500); // NOLINT *-avoid-magic-numbers
    uint16_t value = (value1 + value2 + analogRead(A0)) / 3;
    return value;
}

auto SoilResistivity::operator=(SoilResistivity && other) noexcept -> SoilResistivity & {
    this->sensor = other.sensor;
    other.sensor = nullptr;
    return *this;
}
SoilResistivity::~SoilResistivity() noexcept {}
}

#endif
