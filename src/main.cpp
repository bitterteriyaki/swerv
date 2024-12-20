#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <png.h>
#include <pngconf.h>
#include <zlib.h>

using namespace std;

int read_png(const char* filename) {
    FILE *fp = fopen(filename, "rb");

    if (not fp) {
        cerr << "Unable to open the file." << endl;
        return -1;
    }

    png_byte header[8];
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8)) {
        cerr << "Not a valid PNG file." << endl;
        fclose(fp);

        return -1;   
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if (not png) {
        cerr << "Error creating PNG structure." << endl;
        fclose(fp);

        return -1;
    }

    png_infop info = png_create_info_struct(png);

    if (not info) {
        cerr << "Error creating info structure." << endl;
        fclose(fp);

        return -1;
    }

    if (setjmp(png_jmpbuf(png))) {
        cerr << "Error reading the PNG file." << endl;
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);

        return -1;
    }

    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    png_uint_32 width, height;
    int bit_depth, color_type;
    png_get_IHDR(png, info, &width, &height, &bit_depth, &color_type, nullptr, nullptr, nullptr);

    cout << "Width: " << width << endl;
    cout << "Height: " << width << endl;
    cout << "Bit depth: " << bit_depth << endl;
    cout << "Color type: " << color_type << endl;

    png_read_update_info(png, info);
    png_bytep row = (png_bytep) malloc(png_get_rowbytes(png, info));

    for (png_uint_32 y = 0; y < height; y++) {
        png_read_row(png, row, nullptr);
    }

    free(row);
    png_destroy_read_struct(&png, &info, nullptr);
    fclose(fp);

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Incorrect usage. The correct usage is:" << endl;
        cerr << argv[0] << " [path]" << endl;

        return EXIT_FAILURE;
    }

    if (read_png(argv[1]) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}