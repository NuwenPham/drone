#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>

class Pixel
{
public:
    Pixel(uint8_t r, uint8_t g, uint8_t b);
    
    Pixel* copy() const;

public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

#endif // PIXEL_H
