#include "frameconstructor.h"

FrameConstructor::FrameConstructor(uint32_t p_minCorner, uint32_t p_maxCorner):
    minCorner(p_minCorner),
    maxCorner(p_maxCorner)
{
}

std::list<BitMap *> FrameConstructor::construct(const BitMap& bmp, const std::pair<std::list<Line>, std::list<Line> >& lines)
{
    std::list<BitMap* > res;
    
    std::list<Line>::const_iterator h_begin = lines.first.begin();
    std::list<Line>::const_iterator h_end = lines.first.end();
    
    for (; h_begin != h_end; ++h_begin) {
        
    }
    
    return res;
}
