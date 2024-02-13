#include "edge_filter.h"
#include "grayscale_filter.h"

#include <iostream>
#include "exceptions.h"

constexpr int32_t MaxColor = 255;

EdgeFilter::EdgeFilter(const int32_t& required_arguments, const std::vector<std::string>& parameters)
    : BaseFilter(required_arguments, parameters) {
    try {
        threshold_ = std::stod(parameters[0]);
    } catch (...) {
        throw WrongArgumentsException();
    }
    if (threshold_ > 1 || threshold_ < 0) {
        throw WrongArgumentsException();
    }
    matrix_[0] = {0, -1, 0};
    matrix_[1] = {-1, 4, -1};  // NOLINT
    matrix_[2] = {0, -1, 0};
}

void EdgeFilter::Apply(Image& img) {
    GrayscaleFilter grayscale_filter(0, {});

    grayscale_filter.Apply(img);

    std::vector<std::vector<Pixel>> new_pixels(img.GetHeight(), std::vector<Pixel>(img.GetWidth()));

    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            new_pixels[i][j] = img.ApplyMatrix(i, j, matrix_);
        }
    }

    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            if (static_cast<double>(new_pixels[i][j].red) / MaxColor > threshold_) {
                img.SetPixel(i, j, {MaxColor, MaxColor, MaxColor});
            } else {
                img.SetPixel(i, j, {0, 0, 0});
            }
        }
    }
}
