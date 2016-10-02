#include "edgesdetector.h"

EdgesDetector::EdgesDetector(uint32_t p_minLength):
    minLength(p_minLength)
{
}

std::pair<std::list<Line>, std::list<Line>> EdgesDetector::detect(const BitMap& bmp) const
{
    uint32_t width = bmp.getWidth();
    uint32_t height = bmp.getHeight();

    std::list<Line> horizontal;
    std::list<Line> vertical;
    
    for (int y = 0; y < height; ++y) {
        int x_begin = 0;
        Pixel cur_x = bmp.at(x_begin, y);
        for (int x = 1; x < width; ++x) {
            if (bmp.at(x, y) != cur_x) {
                int length = x - x_begin;
                if (length > minLength) {
                    horizontal.emplace_back(cur_x, x_begin, y, length, Line::Horizontal);
                }
                cur_x = bmp.at(x, y);
                x_begin = x;
            }
        }
    }
    
    for (int x = 0; x < width; ++x) {
        int y_begin = 0;
        Pixel cur_y = bmp.at(x, y_begin);
        for (int y = 1; y < height; ++y) {
            if (bmp.at(x, y) != cur_y) {
                int length = y - y_begin;
                if (length > minLength) {
                    vertical.emplace_back(cur_y, x, y_begin, length, Line::Vertical);
                }
                cur_y = bmp.at(x, y);
                y_begin = y;
            }
        }
    }
    std::pair<std::list<Line>, std::list<Line>> pair(horizontal, vertical);
    return pair;
}
