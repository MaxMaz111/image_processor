#include "base_filter.h"
#include "crop_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharp_filter.h"
#include "edge_filter.h"
#include "cmd_parser.h"
#include "exceptions.h"

#include <iostream>
#include <memory>
#include <algorithm>

constexpr int32_t CropFilterRequiredArguments = 2;

CmdParser::CmdParser(int argc, char** argv) {
    arg_cnt_ = static_cast<size_t>(argc);
    arguments_.resize(arg_cnt_);
    for (size_t i = 0; i < arg_cnt_; ++i) {
        arguments_[i] = argv[i];
    }
}

const std::string& CmdParser::GetArg(size_t i) {
    return arguments_[i];
}

bool CmdParser::Parse() {
    if (arg_cnt_ < 3) {
        PrintHelp();
        return false;
    }
    input_file_name_ = GetArg(1);
    output_file_name_ = GetArg(2);

    for (size_t i = 3; i < arguments_.size(); ++i) {
        if (std::find(available_filters_.begin(), available_filters_.end(), arguments_[i]) ==
            available_filters_.end()) {
            PrintHelp();
            return false;
        }

        if (arguments_[i] == "-crop") {
            std::vector<std::string> crop_arguments(2);
            for (int32_t j = 0; j < CropFilterRequiredArguments; ++j) {
                if (i + 1 == arguments_.size()) {
                    PrintHelp();
                    return false;
                }
                crop_arguments[j] = arguments_[++i];
            }
            try {
                CropFilter crop_filter(CropFilterRequiredArguments, crop_arguments);
                all_filters.push_back(std::make_unique<CropFilter>(crop_filter));
            } catch (const WrongArgumentsException& wrong_arguments_exception) {
                PrintHelp();
                return false;
            }
        } else if (arguments_[i] == "-gs") {
            GrayscaleFilter grayscale_filter(0, {});
            all_filters.push_back(std::make_unique<GrayscaleFilter>(grayscale_filter));
        } else if (arguments_[i] == "-neg") {
            NegativeFilter negative_filter(0, {});
            all_filters.push_back(std::make_unique<NegativeFilter>(negative_filter));
        } else if (arguments_[i] == "-sharp") {
            SharpFilter sharp_filter(0, {});
            all_filters.push_back(std::make_unique<SharpFilter>(sharp_filter));
        } else if (arguments_[i] == "-edge") {
            if (i + 1 == arguments_.size()) {
                PrintHelp();
                return false;
            }
            std::string threshold = arguments_[++i];
            try {
                EdgeFilter edge_filter(1, {threshold});
                all_filters.push_back(std::make_unique<EdgeFilter>(edge_filter));
            } catch (const WrongArgumentsException& wrong_arguments_exception) {
                PrintHelp();
                return false;
            }
        } else if (arguments_[i] == "-blur") {
        }
    }

    return true;
}

std::string CmdParser::GetInputFile() {
    return input_file_name_;
}

std::string CmdParser::GetOutputFile() {
    return output_file_name_;
}

void CmdParser::PrintHelp() {
    std::cout << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "{program name} {input file path} {output file path}\n"
                 "[-{filter 1 name} [filter parameter 1] [filter parameter 2] ...]\n"
                 "[-{filter 2 name} [filter parameter 1] [filter parameter 2] ...] ..."
              << std::endl;
    std::cout << std::endl;
    std::cout << "Available filters:" << std::endl;
    std::cout << std::endl;
    std::cout << "-crop {width} {height}" << std::endl;
    std::cout << "Crops the image to a certain resolution. Both arguments have to be positive integers." << std::endl;
    std::cout << std::endl;
    std::cout << "-gs" << std::endl;
    std::cout << "Turns the image to grayscale." << std::endl;
    std::cout << std::endl;
    std::cout << "-neg" << std::endl;
    std::cout << "Makes the image negative." << std::endl;
    std::cout << std::endl;
    std::cout << "-sharp" << std::endl;
    std::cout << "Makes the image more sharp." << std::endl;
    std::cout << std::endl;
    std::cout << "-edge {threshold}" << std::endl;
    std::cout << "Colors all of the edges white and anything else black. "
                 "Adjust the sensitivity via threshold parameter. It has to be a real number between 0 and 1."
              << std::endl;
    std::cout << std::endl;
    std::cout << "-blur {sigma}" << std::endl;
    std::cout << "Blurs the image. Adjust intensity via sigma parameter. Sigma has to be an integer." << std::endl;
    std::cout << std::endl;
}
