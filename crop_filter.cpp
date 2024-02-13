#include "crop_filter.h"
#include "exceptions.h"

CropFilter::CropFilter(const int32_t& required_arguments, const std::vector<std::string>& parameters)
    : BaseFilter(required_arguments, parameters) {
    try {
        new_width_ = std::stoi(parameters[0]);
        new_height_ = std::stoi(parameters[1]);
    } catch (...) {
        throw WrongArgumentsException();
    }
    if (new_height_ < 0 || new_width_ < 0) {
        throw WrongArgumentsException();
    }
}

void CropFilter::Apply(Image& img) {
    img.ResizeHeight(std::min(new_height_, img.GetHeight()));
    img.ResizeWidth(std::min(new_width_, img.GetWidth()));
}
