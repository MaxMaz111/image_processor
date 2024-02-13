#pragma once

#include "base_filter.h"

class GrayscaleFilter : public BaseFilter {
public:
    GrayscaleFilter(const int32_t& required_parameters, const std::vector<std::string>& parameters);

    void Apply(Image& img) override;

private:
    const double red_coefficient_ = 0.299;
    const double green_coefficient_ = 0.587;
    const double blue_coefficient_ = 0.114;
};
