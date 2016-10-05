#ifndef LINE_H
#define LINE_H

#include "pixel.h"
#include <map>

class Line
{
public:
    enum Orientation {
        Horizontal,
        Vertical
    };
    
    Line(const Pixel& p_color, uint32_t p_x, uint32_t p_y, uint32_t p_length, Orientation p_or);
    
    uint32_t getX() const;
    uint32_t getY() const;
    uint32_t getLength() const;
    Orientation getOrientation() const;
    const Pixel& getColor() const;
    
    std::pair<uint32_t, uint32_t> crossing(const Line& other) const;
    
    void setColor(const Pixel& p_color);
    
private:
    Pixel color;
    uint32_t x;
    uint32_t y;
    uint32_t length;
    Orientation orientation;
};

#endif // LINE_H
