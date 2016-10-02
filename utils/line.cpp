#include "line.h"

Line::Line(const Pixel& p_color, uint32_t p_x, uint32_t p_y, uint32_t p_length, Orientation p_or):
    color(p_color),
    x(p_x),
    y(p_y),
    length(p_length),
    orientation(p_or)
{
}
