#pragma once

#include "pixel.h"

#include <cstdint>
#include <string>
#include <vector>
#include <array>

class Image {
public:
    Image(const size_t& height, const size_t& width, const std::vector<std::vector<Pixel>>& pixels);

    Image(const size_t& height, const size_t& width);

    void SetPixel(const size_t& ver_pos, const size_t& hor_pos, const Pixel& pix);

    Pixel GetPixel(const size_t& hor_pos, const size_t& ver_pos);

    size_t GetWidth() const;

    size_t GetHeight() const;

    void ResizeWidth(const size_t& new_width);

    void ResizeHeight(const size_t& new_height);

    Pixel ApplyMatrix(const size_t& row, const size_t& column, const std::array<std::array<int32_t, 3>, 3>& matrix);

private:
    std::vector<std::vector<Pixel>> pixels_;

    size_t width_;
    size_t height_;
};
