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
    uint8_t* getData() const;
    const Pixel& at(uint32_t x, uint32_t y) const;
    
private:
    static void writeIntToArray(uint8_t value, uint8_t* array, uint32_t startIndex);
    static void writeIntToArray(uint16_t value, uint8_t* array, uint32_t startIndex);
    static void writeIntToArray(uint32_t value, uint8_t* array, uint32_t startIndex);
    void writeHeader(uint8_t* array) const;
    
private:
    std::vector<std::vector<Pixel*>*>* data;
    uint32_t width;
    uint32_t height;
    
};

#endif // BITMAP_H
