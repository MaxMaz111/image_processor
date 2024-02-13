#include "image.h"

constexpr int32_t MaxColor = 255;

Image::Image(const size_t& height, const size_t& width, const std::vector<std::vector<Pixel>>& pixels) {
    Image(height, width);
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            SetPixel(i, j, pixels[i][j]);
        }
    }
}

Image::Image(const size_t& height, const size_t& width) {
    height_ = height;
    width_ = width;
    pixels_.resize(height_);
    for (auto& i : pixels_) {
        i.resize(width_);
    }
}

void Image::SetPixel(const size_t& ver_pos, const size_t& hor_pos, const Pixel& pix) {
    pixels_.at(ver_pos).at(hor_pos) = pix;
}

Pixel Image::GetPixel(const size_t& hor_pos, const size_t& ver_pos) {
    return pixels_.at(hor_pos).at(ver_pos);
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

void Image::ResizeHeight(const size_t& new_height) {
    pixels_.resize(new_height);
    height_ = new_height;
}

void Image::ResizeWidth(const size_t& new_width) {
    for (auto& i : pixels_) {
        i.resize(new_width);
    }
    width_ = new_width;
}

void FindClosest(int32_t& row, int32_t& column, const size_t& width, const size_t& height) {
    if (row < 0) {
        ++row;
    }
    if (row >= height) {
        --row;
    }
    if (column < 0) {
        ++column;
    }
    if (column >= width) {
        --column;
    }
}

Pixel Image::ApplyMatrix(const size_t& row, const size_t& column, const std::array<std::array<int32_t, 3>, 3>& matrix) {
    int32_t new_val_red = 0;
    int32_t new_val_green = 0;
    int32_t new_val_blue = 0;

    for (int32_t i = -1; i <= 1; ++i) {
        for (int32_t j = -1; j <= 1; ++j) {
            auto new_row = static_cast<int32_t>(row) + i;
            auto new_column = static_cast<int32_t>(column) + j;

            FindClosest(new_row, new_column, width_, height_);

            new_val_red += matrix[i + 1][j + 1] * pixels_[new_row][new_column].red;
            new_val_green += matrix[i + 1][j + 1] * pixels_[new_row][new_column].green;
            new_val_blue += matrix[i + 1][j + 1] * pixels_[new_row][new_column].blue;
        }
    }

    new_val_red = std::max(0, std::min(MaxColor, new_val_red));
    new_val_green = std::max(0, std::min(MaxColor, new_val_green));
    new_val_blue = std::max(0, std::min(MaxColor, new_val_blue));

    return {new_val_red, new_val_green, new_val_blue};
}
