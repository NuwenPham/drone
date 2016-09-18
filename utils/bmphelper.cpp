//
// Created by cubla on 18.09.2016.
//


#include "bmphelper.h"

BMPHelper::BMPHelper(int width, int height, byte* buffer)
{
    this->width = width;
    this->height = height;
    this->pixelBuffer = buffer;
}