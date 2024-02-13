#include "negative_filter.h"

constexpr uint8_t MaxColor = 255;

NegativeFilter::NegativeFilter(const int32_t& required_arguments, const std::vector<std::string>& parameters)
    : BaseFilter(required_arguments, parameters) {
}

void NegativeFilter::Apply(Image& img) {
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            Pixel cur_pix = img.GetPixel(i, j);

            cur_pix.red = MaxColor - cur_pix.red;
            cur_pix.green = MaxColor - cur_pix.green;
            cur_pix.blue = MaxColor - cur_pix.blue;

            img.SetPixel(i, j, cur_pix);
        }
    }
}
