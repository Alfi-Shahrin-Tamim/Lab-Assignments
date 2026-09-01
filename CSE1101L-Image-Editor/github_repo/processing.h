#ifndef PROCESSING_H
#define PROCESSING_H

#include "image.h"

void grayscale(Image* img);
void invert(Image* img);
void brightness(Image* img, int value);
void hflip(Image* img);
void vflip(Image* img);
Image* rotate90(Image* src);
Image* crop(Image* src, int start_x, int start_y, int width, int height);
Image* blur(Image* src);

Image* sharpen(Image* src);

#endif
