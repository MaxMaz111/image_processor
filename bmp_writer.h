#pragma once

#include "image.h"

#include <vector>
#include <string>

class Writer {
public:
    explicit Writer(const std::string& path);

    void Write(Image img);

private:
    std::string path_;
};
