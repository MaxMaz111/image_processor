#pragma once

#include "base_filter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(const int32_t& required_arguments, const std::vector<std::string>& parameters);

    void Apply(Image& img) override;

private:
    size_t new_height_;
    size_t new_width_;
};
