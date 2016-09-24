#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include <vector>

#include "pixel.h"

class BitMap
{
public:
    BitMap(const std::string& path);
    BitMap(std::vector<std::vector<Pixel*>*>* src);
    ~BitMap();
    
    uint32_t getWidth() const;
    uint32_t getHeight() const;
    void save(const std::string& path) const;
    BitMap* rect(uint32_t startx, uint32_t starty, uint32_t endx, uint32_t endy) const;
    uint32_t realSize() const;
    
private:
    void writeHeader(FILE* file) const;
    
private:
    std::vector<std::vector<Pixel*>*>* data;
    uint32_t width;
    uint32_t height;
    
};

#endif // BITMAP_H
