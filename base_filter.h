#pragma once

#include "image.h"

class BaseFilter {
public:
    BaseFilter(const int32_t& required_parameters, const std::vector<std::string>& parameters);

    virtual void Apply(Image& img) = 0;

    virtual ~BaseFilter();

private:
    std::vector<std::string> parameters_;
    int32_t required_parameters_;
};
