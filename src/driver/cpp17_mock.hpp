#ifndef IOP_LIB_SENSORS_SOIL_RESISTIVITY_CPP17_MOCK_HPP
#define IOP_LIB_SENSORS_SOIL_RESISTIVITY_CPP17_MOCK_HPP

#include <soil_resistivity.hpp>

#include <random>

namespace sensor {
auto randomValue() -> uint16_t {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1024);
    return static_cast<uint16_t>(dist(rng));
}

auto randomVariation(uint16_t current) -> uint16_t {
    if (current <= 200) return std::min(current + randomValue(), 1024);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 16);
    if (current == 1024) return current - dist(rng);
    return std::min(current + dist(rng) - 15, 1024);
}

SoilResistivity::SoilResistivity(const iop_hal::PinRaw powerPin) noexcept: sensor(new uint16_t(randomValue())) { (void) powerPin; }

auto SoilResistivity::begin() noexcept -> void {}
auto SoilResistivity::measure() noexcept -> uint16_t {
    auto *ptr = reinterpret_cast<uint16_t*>(this->sensor);
    *ptr = randomVariation(*ptr);
    return *ptr;
}

auto SoilResistivity::operator=(SoilResistivity && other) noexcept -> SoilResistivity & {
    delete reinterpret_cast<uint16_t*>(this->sensor);
    this->sensor = other.sensor;
    other.sensor = nullptr;
    return *this;
}
SoilResistivity::~SoilResistivity() noexcept {
    delete reinterpret_cast<uint16_t*>(this->sensor);
}
}

#endif