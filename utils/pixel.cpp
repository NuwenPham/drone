#include "pixel.h"

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b):
    red(r),
    green(g),
    blue(b)
{
}

Pixel * Pixel::copy() const
{
    return new Pixel(red, green, blue);
}

bool Pixel::operator==(const Pixel& other) const
{
    return red == other.red && green == other.green && blue == other.blue;
}

bool Pixel::operator!=(const Pixel& other) const
{
    return red != other.red || green != other.green || blue != other.blue;
}
