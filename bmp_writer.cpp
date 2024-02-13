#include "bmp_writer.h"
#include "exceptions.h"

#include <fstream>
#include <limits.h>
#include <iostream>

constexpr uint32_t FileHeaderSize = 14;
constexpr uint32_t DIBHeaderSize = 40;  // We assume that we're working with BITMAPINFOHEADER

constexpr uint32_t IntBytes = 4;  // uint32_t has 4 bytes in it

constexpr uint32_t BitsPerPixel = 24;

Writer::Writer(const std::string& path) {
    path_ = path;
}

void Writer::Write(Image img) {
    std::ofstream output_stream(path_, std::ostream::binary);

    if (!output_stream.is_open()) {
        throw DirectoryDoesNotExistException();
    }

    // File header

    output_stream.write("BM", 2);  // First two bytes of any bitmap image should be equal to "BM"

    uint32_t row_size = (BitsPerPixel * img.GetWidth() + (IntBytes * CHAR_BIT) - 1) / (IntBytes * CHAR_BIT) * IntBytes;
    auto file_size = FileHeaderSize + DIBHeaderSize + img.GetHeight() * row_size;

    uint32_t dummy_zero = 0;

    output_stream.write(reinterpret_cast<char*>(&file_size), IntBytes);

    output_stream.write(reinterpret_cast<char*>(&dummy_zero), IntBytes);

    uint32_t pixel_array_offset = FileHeaderSize + DIBHeaderSize;

    output_stream.write(reinterpret_cast<char*>(&pixel_array_offset), IntBytes);

    // DIB header

    uint32_t dib_header = DIBHeaderSize;
    uint32_t image_width = img.GetWidth();
    uint32_t image_height = img.GetHeight();
    uint16_t color_planes = 1;
    uint16_t bits_per_pixel = BitsPerPixel;
    uint32_t compression = 0;

    output_stream.write(reinterpret_cast<char*>(&dib_header), IntBytes);
    output_stream.write(reinterpret_cast<char*>(&image_width), IntBytes);
    output_stream.write(reinterpret_cast<char*>(&image_height), IntBytes);
    output_stream.write(reinterpret_cast<char*>(&color_planes), IntBytes / 2);
    output_stream.write(reinterpret_cast<char*>(&bits_per_pixel), IntBytes / 2);
    output_stream.write(reinterpret_cast<char*>(&compression), IntBytes);
    const int dummy_zeros_cnt = 5;
    for (int i = 0; i < dummy_zeros_cnt; ++i) {
        output_stream.write(reinterpret_cast<char*>(&dummy_zero),
                            IntBytes);  // these are unnecessary fields that are zero by default
    }

    // Pixel array

    for (ssize_t i = static_cast<ssize_t>(img.GetHeight()) - 1; i >= 0; --i) {
        std::vector<uint8_t> to_write(row_size, 0);
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            Pixel cur_pix = img.GetPixel(i, j);
            // order of colors: blue, green, red
            to_write[3 * j] = cur_pix.blue;
            to_write[3 * j + 1] = cur_pix.green;
            to_write[3 * j + 2] = cur_pix.red;
        }
        output_stream.write(reinterpret_cast<char*>(to_write.data()), row_size);
    }
}
