#include "line.h"

Line::Line(const Pixel& p_color, uint32_t p_x, uint32_t p_y, uint32_t p_length, Orientation p_or):
    color(p_color),
    x(p_x),
    y(p_y),
    length(p_length),
    orientation(p_or)
{
}

uint32_t Line::getX() const
{
    return x;
}

uint32_t Line::getY() const
{
    return y;
}

uint32_t Line::getLength() const
{
    return length;
}

std::pair<uint32_t, uint32_t> Line::crossing(const Line& other) const
{
    if (orientation == other.orientation) {
        throw 1; //parallel
    }
    
    
    if (orientation == Horizontal) {
        return std::make_pair(other.x, y);
    } else {
        return std::make_pair(x, other.y);
    }
}

Line::Orientation Line::getOrientation() const
{
    return orientation;
}

const Pixel & Line::getColor() const
{
    return color;
}


void Line::setColor(const Pixel& p_color)
{
    color = p_color;
}
