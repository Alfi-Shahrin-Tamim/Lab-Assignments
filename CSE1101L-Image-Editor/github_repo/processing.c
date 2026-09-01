#include <stdlib.h>
#include "processing.h"
#include "image.h"

void grayscale(Image* img) {
    for (int i = 0; i < img->width * img->height; i++) {
        unsigned char gray = (unsigned char)(
            0.299 * img->data[i].r +
            0.587 * img->data[i].g +
            0.114 * img->data[i].b
        );
        img->data[i].r = gray;
        img->data[i].g = gray;
        img->data[i].b = gray;
    }
}

void invert(Image* img) {
    for (int i = 0; i < img->width * img->height; i++) {
        img->data[i].r = 255 - img->data[i].r;
        img->data[i].g = 255 - img->data[i].g;
        img->data[i].b = 255 - img->data[i].b;
    }
}

void brightness(Image* img, int value) {
    for (int i = 0; i < img->width * img->height; i++) {
        int r = img->data[i].r + value;
        int g = img->data[i].g + value;
        int b = img->data[i].b + value;
        img->data[i].r = (r > 255) ? 255 : ((r < 0) ? 0 : r);
        img->data[i].g = (g > 255) ? 255 : ((g < 0) ? 0 : g);
        img->data[i].b = (b > 255) ? 255 : ((b < 0) ? 0 : b);
    }
}

void hflip(Image* img) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width / 2; x++) {
            int left = y * img->width + x;
            int right = y * img->width + (img->width - 1 - x);
            Pixel temp = img->data[left];
            img->data[left] = img->data[right];
            img->data[right] = temp;
        }
    }
}

void vflip(Image* img) {
    for (int y = 0; y < img->height / 2; y++) {
        for (int x = 0; x < img->width; x++) {
            int top = y * img->width + x;
            int bottom = (img->height - 1 - y) * img->width + x;
            Pixel temp = img->data[top];
            img->data[top] = img->data[bottom];
            img->data[bottom] = temp;
        }
    }
}

Image* rotate90(Image* src) {
    Image* dst = create_image(src->height, src->width);
    if (!dst) return NULL;
    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            int src_idx = y * src->width + x;
            int new_x = src->height - 1 - y;
            int new_y = x;
            int dst_idx = new_y * dst->width + new_x;
            dst->data[dst_idx] = src->data[src_idx];
        }
    }
    return dst;
}

Image* crop(Image* src, int start_x, int start_y, int width, int height) {
    if (start_x < 0 || start_y < 0 || width <= 0 || height <= 0)
        return NULL;
    if (start_x + width > src->width || start_y + height > src->height)
        return NULL;
    Image* dst = create_image(width, height);
    if (!dst) return NULL;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int src_idx = (start_y + y) * src->width + (start_x + x);
            int dst_idx = y * dst->width + x;
            dst->data[dst_idx] = src->data[src_idx];
        }
    }
    return dst;
}

Image* blur(Image* src) {
    Image* dst = create_image(src->width, src->height);
    if (!dst) return NULL;
    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            int sum_r = 0, sum_g = 0, sum_b = 0;
            int count = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0) nx = 0;
                    if (nx >= src->width) nx = src->width - 1;
                    if (ny < 0) ny = 0;
                    if (ny >= src->height) ny = src->height - 1;
                    int idx = ny * src->width + nx;
                    sum_r += src->data[idx].r;
                    sum_g += src->data[idx].g;
                    sum_b += src->data[idx].b;
                    count++;
                }
            }
            int dst_idx = y * dst->width + x;
            dst->data[dst_idx].r = sum_r / count;
            dst->data[dst_idx].g = sum_g / count;
            dst->data[dst_idx].b = sum_b / count;
        }
    }
    return dst;
}

Image* sharpen(Image* src) {
    /* Assignment kernel:  0 -1 0 / -1 5 -1 / 0 -1 0
       Same structure as blur: separate output image, edge pixels
       replicated at borders, int sums, results clamped to 0..255. */
    static const int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };
    Image* dst = create_image(src->width, src->height);
    if (!dst) return NULL;
    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            int sum_r = 0, sum_g = 0, sum_b = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0) nx = 0;
                    if (nx >= src->width)  nx = src->width - 1;
                    if (ny < 0) ny = 0;
                    if (ny >= src->height) ny = src->height - 1;
                    int w = kernel[dy + 1][dx + 1];
                    Pixel p = src->data[ny * src->width + nx];
                    sum_r += w * p.r;
                    sum_g += w * p.g;
                    sum_b += w * p.b;
                }
            }
            int di = y * dst->width + x;
            dst->data[di].r = (sum_r < 0) ? 0 : (sum_r > 255 ? 255 : sum_r);
            dst->data[di].g = (sum_g < 0) ? 0 : (sum_g > 255 ? 255 : sum_g);
            dst->data[di].b = (sum_b < 0) ? 0 : (sum_b > 255 ? 255 : sum_b);
        }
    }
    return dst;
}
