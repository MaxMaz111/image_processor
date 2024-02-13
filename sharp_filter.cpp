#include "sharp_filter.h"

SharpFilter::SharpFilter(const int32_t& required_arguments, const std::vector<std::string>& parameters)
    : BaseFilter(required_arguments, parameters) {
    matrix_[0] = {0, -1, 0};
    matrix_[1] = {-1, 5, -1};  // NOLINT
    matrix_[2] = {0, -1, 0};
}

void SharpFilter::Apply(Image& img) {
    std::vector<std::vector<Pixel>> new_pixels(img.GetHeight(), std::vector<Pixel>(img.GetWidth()));

    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            new_pixels[i][j] = img.ApplyMatrix(i, j, matrix_);
        }
    }

    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            img.SetPixel(i, j, new_pixels[i][j]);
        }
    }
}
