#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image.h"
#include "stb_wrapper.h"

Image* create_image(int width, int height) {
    Image* img = (Image*)malloc(sizeof(Image));
    if (!img) return NULL;
    img->width = width;
    img->height = height;
    img->data = (Pixel*)malloc(sizeof(Pixel) * width * height);
    if (!img->data) {
        free(img);
        return NULL;
    }
    return img;
}

Image* load_image(const char* filename) {
    int width, height, channels;
    unsigned char* raw = stbi_load(filename, &width, &height, &channels, 3);
    Image* img;

    if (!raw) {
        fprintf(stderr, "Failed to load: %s\n", stbi_failure_reason());
        return NULL;
    }

    img = create_image(width, height);
    if (!img) {
        stbi_image_free(raw);
        return NULL;
    }
    memcpy(img->data, raw, (size_t)width * height * sizeof(Pixel));
    stbi_image_free(raw);
    return img;
}

int save_image(const char* filename, Image* img) {
    return stbi_write_bmp(filename, img->width, img->height, 3, img->data);
}

Image* copy_image(Image* src) {
    Image* dst = create_image(src->width, src->height);
    if (!dst) return NULL;
    for (int i = 0; i < src->width * src->height; i++) {
        dst->data[i] = src->data[i];
    }
    return dst;
}

void free_image(Image* img) {
    if (img) {
        if (img->data) free(img->data);
        free(img);
    }
}
