#pragma once

#include "base_filter.h"

#include <vector>
#include <string>
#include <memory>

class CmdParser {
public:
    CmdParser(int argc, char** argv);

    const std::string& GetArg(size_t i);

    bool Parse();

    std::string GetInputFile();

    std::string GetOutputFile();

    std::vector<std::unique_ptr<BaseFilter>> all_filters;

private:
    size_t arg_cnt_;

    std::vector<std::string> arguments_;
    std::string input_file_name_;

    std::string output_file_name_;

    const std::vector<std::string> available_filters_ = {"-crop", "-gs", "-neg", "-sharp", "-edge", "-blur"};

    void PrintHelp();
};
