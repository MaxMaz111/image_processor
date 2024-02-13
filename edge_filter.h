#pragma once

#include "base_filter.h"

#include <array>

class EdgeFilter : public BaseFilter {
public:
    EdgeFilter(const int32_t& required_arguments, const std::vector<std::string>& parameters);

    void Apply(Image& img) override;

private:
    std::array<std::array<int32_t, 3>, 3> matrix_;

    double threshold_;
};
