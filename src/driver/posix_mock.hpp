#ifndef IOP_LIB_SENSORS_SOIL_RESISTIVITY_POSIX_MOCK_HPP
#define IOP_LIB_SENSORS_SOIL_RESISTIVITY_POSIX_MOCK_HPP

#include <soil_resistivity.hpp>

#include <random>
#include <iostream>

auto randomValue() -> uint16_t {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1024);
    return dist(rng);
}

auto randomVariation(uint16_t current) -> uint16_t {
    if (current < 200) return current = std::max(current + randomValue(), 1024);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-6,0);
    return std::max(current + dist(rng), 1024);
}

namespace sensor {
SoilResistivity::SoilResistivity(const iop_hal::PinRaw powerPin) noexcept { this->sensor = new uint16_t(randomValue()); }

auto SoilResistivity::begin() noexcept -> void {}
auto SoilResistivity::measure() noexcept -> uint16_t {
    auto *ptr = reinterpret_cast<uint16_t*>(this->sensor);
    *ptr = randomVariation(*ptr);
    return *ptr;
}

auto SoilResistivity::operator=(SoilResistivity && other) noexcept -> SoilResistivity & {
    delete this->sensor;
    this->sensor = other.sensor;
    other.sensor = nullptr;
}
SoilResistivity::~SoilResistivity() noexcept {
    delete this->sensor
}
}

#endif