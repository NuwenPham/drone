#ifndef LINE_H
#define LINE_H

#include "pixel.h"

class Line
{
public:
    enum Orientation {
        Horizontal,
        Vertical
    };
    
    Line(const Pixel& p_color, uint32_t p_x, uint32_t p_y, uint32_t p_length, Orientation p_or);
    
    
private:
    Pixel color;
    uint32_t x;
    uint32_t y;
    uint32_t length;
    Orientation orientation;
};

#endif // LINE_H
