#pragma once

#include <cstdint>

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    Pixel();

    Pixel(const uint8_t& r, const uint8_t& g, const uint8_t& b);
};
