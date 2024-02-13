#include "bmp_reader.h"
#include "exceptions.h"

#include <fstream>
#include <limits.h>
#include <iostream>

constexpr size_t FileHeaderSize = 14;
constexpr size_t DIBHeaderSize = 40;  // We assume that we're working with BITMAPINFOHEADER

constexpr size_t IntBytes = 4;  // uint32_t has 4 bytes in it

constexpr size_t BitsPerPixel = 24;

Reader::Reader(const std::string& path) {
    path_ = path;
}

Image Reader::Read() {
    std::ifstream input_stream(path_, std::ifstream::binary);

    if (!input_stream.is_open()) {
        throw FileCouldNotOpenException();
    }

    input_stream.seekg(0, input_stream.end);
    auto length = static_cast<std::streamsize>(input_stream.tellg());
    input_stream.seekg(0, input_stream.beg);

    std::vector<uint8_t> bytes_vector(length);
    input_stream.read(reinterpret_cast<char*>(bytes_vector.data()), length);

    bool is_bmp = true;

    is_bmp &= ('B' == static_cast<char>(bytes_vector[0]));
    is_bmp &= ('M' == static_cast<char>(bytes_vector[1]));

    // First two bytes should be equal to "BM" for the image to be considered bitmap

    if (!is_bmp) {
        throw FileIsNotBmpException();
    }

    auto read_four_bytes = [&bytes_vector](const size_t& pos) {
        uint32_t ans = 0;
        size_t to_shift = 0;
        for (size_t i = pos; i < pos + IntBytes; ++i) {
            ans += bytes_vector[i] << to_shift;
            to_shift += CHAR_BIT;
        }
        return ans;
    };

    size_t image_width =
        read_four_bytes(FileHeaderSize + IntBytes);  // width starts with 4 bytes shift relative to File header's end
    size_t image_height =
        read_four_bytes(FileHeaderSize + 2 * IntBytes);  // height starts with 4 bytes shift relative to width

    Image img(image_height, image_width);

    size_t row_size = (BitsPerPixel * image_width + (IntBytes * CHAR_BIT) - 1) / (IntBytes * CHAR_BIT) *
                      IntBytes;  // DWORD 32 bytes long

    size_t cur_pos = FileHeaderSize + DIBHeaderSize;

    for (ssize_t row = static_cast<ssize_t>(image_height) - 1; row >= 0;
         --row) {  // image is stored reversed horizontally
        for (size_t pos = cur_pos; pos < cur_pos + image_width * 3; pos += 3) {
            // colors are stored in order: blue, green, red
            uint8_t blue = bytes_vector[pos];
            uint8_t green = bytes_vector[pos + 1];
            uint8_t red = bytes_vector[pos + 2];

            Pixel cur_pix(red, green, blue);

            size_t column = (pos - cur_pos) / 3;  // simple maths

            img.SetPixel(row, column, cur_pix);
        }
        cur_pos += row_size;
    }

    return img;
}
