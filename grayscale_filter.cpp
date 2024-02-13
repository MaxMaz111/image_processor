#include "grayscale_filter.h"

GrayscaleFilter::GrayscaleFilter(const int32_t& required_parameters, const std::vector<std::string>& parameters)
    : BaseFilter(required_parameters, parameters) {
}

void GrayscaleFilter::Apply(Image& img) {
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            Pixel cur_pix = img.GetPixel(i, j);

            uint8_t delta = static_cast<uint8_t>(red_coefficient_ * cur_pix.red + green_coefficient_ * cur_pix.green +
                                                 blue_coefficient_ * cur_pix.blue);

            cur_pix.red = delta;
            cur_pix.green = delta;
            cur_pix.blue = delta;

            img.SetPixel(i, j, cur_pix);
        }
    }
}
