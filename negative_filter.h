#pragma once

#include "base_filter.h"

class NegativeFilter : public BaseFilter {
public:
    NegativeFilter(const int32_t& required_arguments, const std::vector<std::string>& parameters);

    void Apply(Image& img) override;
};
