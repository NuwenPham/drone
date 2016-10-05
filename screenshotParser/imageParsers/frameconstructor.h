#ifndef FRAMECONSTRUCTOR_H
#define FRAMECONSTRUCTOR_H

#include <stdint.h>
#include <list>
#include <map>

#include "utils/bitmap.h"
#include "utils/line.h"

class FrameConstructor
{
public:
    FrameConstructor(uint32_t p_minCorner, uint32_t p_maxCorner);
    
    std::list<BitMap*> construct(const BitMap& bmp, const std::pair<std::list<Line>, std::list<Line>>& lines);
    
private:
    uint32_t minCorner;
    uint32_t maxCorner;
};

#endif // FRAMECONSTRUCTOR_H
