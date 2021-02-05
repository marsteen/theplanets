
#ifndef NPng_H
#define NPng_H

extern "C"
{
    int NPng_Write(const char* png_file, char* png_data, int png_width, int png_height, int png_bits);
    int NPng_Read(const char* png_file, char** png_data, int* png_width, int* png_height, int* png_bits, size_t file_offset);
}

#endif
