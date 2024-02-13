#pragma once

#include "image.h"

#include <vector>
#include <string>

class Reader {
public:
    explicit Reader(const std::string& path);

    Image Read();

private:
    std::string path_;
};
