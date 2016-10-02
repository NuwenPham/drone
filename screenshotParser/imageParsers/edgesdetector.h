#ifndef EDGESDETECTOR_H
#define EDGESDETECTOR_H

#include <stdint.h>
#include <list>
#include <utils/bitmap.h>
#include <utils/pixel.h>
#include <utils/line.h>

class EdgesDetector
{
public:
    EdgesDetector(uint32_t p_minLength);
    
    std::pair<std::list<Line>, std::list<Line>> detect(const BitMap& bmp) const;
    
private:
    uint32_t minLength;
};

#endif // EDGESDETECTOR_H
