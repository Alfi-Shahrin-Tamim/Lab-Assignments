#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct {
    int width;
    int height;
    Pixel *data;
} Image;

Image* create_image(int width, int height);
Image* copy_image(Image* src);
Image* load_image(const char* filename);
int    save_image(const char* filename, Image* img);
void   free_image(Image* img);

#endif
