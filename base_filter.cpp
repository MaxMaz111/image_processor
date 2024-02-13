#include "base_filter.h"
#include "exceptions.h"

BaseFilter::~BaseFilter() {
}

BaseFilter::BaseFilter(const int32_t& required_parameters, const std::vector<std::string>& parameters) {
    required_parameters_ = required_parameters;
    parameters_ = parameters;
    if (parameters.size() != required_parameters) {
        throw WrongArgumentsException();
    }
}
