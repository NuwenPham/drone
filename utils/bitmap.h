#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include <vector>

#include "pixel.h"
#include "line.h"

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
    
    Pixel* getPixel(uint32_t x, uint32_t y) const;
    //Pixel* setPixel(uint32_t x, uint32_t y, Pixel* p) const;
    
    void draw(const Line& line);
    void draw(uint32_t x, uint32_t y, const Pixel& color);
    
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
