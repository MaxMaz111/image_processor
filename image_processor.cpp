#include "bmp_reader.h"
#include "bmp_writer.h"
#include "cmd_parser.h"
#include "exceptions.h"

#include <iostream>

void Print(const std::string& message) {
    std::cout << std::endl;
    std::cout << message << std::endl;
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    CmdParser parser(argc, argv);
    bool parsed_successfully = parser.Parse();

    if (!parsed_successfully) {
        return 0;
    }

    try {
        Reader reader(parser.GetInputFile());
        Image img = reader.Read();

        for (auto& filter : parser.all_filters) {
            filter->Apply(img);
        }

        Writer writer(parser.GetOutputFile());
        writer.Write(img);
    } catch (const FileIsNotBmpException& bmp_exception) {
        Print("The file you are trying to open is not a bitmap image.");
    } catch (const CorruptedFileException& corrupted_exception) {
        Print("The file you are trying to open is corrupted.");
    } catch (const FileCouldNotOpenException& file_open_exception) {
        Print("The file you are trying to open doesn't exist or cannot be read.");
    } catch (const DirectoryDoesNotExistException& directory_does_not_exist_exception) {
        Print("The directory you're trying to load the file to does not exist.");
    }
    return 0;
}