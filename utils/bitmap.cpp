#include "bitmap.h"
#include <iostream>
#include <stdio.h>

BitMap::BitMap(const std::string& path):
    data(0),
    width(0),
    height(0)
{
    FILE* file = fopen(path.data(), "rb");
    uint8_t info[54];
    fread(info, sizeof(uint8_t), 54, file); // read the 54-byte header

    width = *(uint32_t*)&info[18];
    height = *(uint32_t*)&info[22];
    
    uint64_t padded = (width * 3 + 3) & (~3);
    uint8_t* buffer = new uint8_t[padded];

    data = new std::vector<std::vector<Pixel*>*>(height, 0);
    for (int i = height - 1; i >= 0; --i) {
        std::vector<Pixel*>* row = new std::vector<Pixel*>(width, 0);
        data->at(i) = row;
        fread(buffer, sizeof(uint8_t), padded, file);
        for (int j = 0; j < width; ++j) {
            row->at(j) = new Pixel(buffer[3 * j + 2], buffer[3 * j + 1], buffer[3 * j + 0]);
        }
    }
    delete[] buffer;
    
    fclose(file);
}

BitMap::BitMap(std::vector<std::vector<Pixel *> *>* src):
    data(src),
    width(0),
    height(0)
{
    height = data->size();
    width = data->at(0)->size();
}


BitMap::~BitMap()
{
    
    Pixel* px;
    std::vector<Pixel*>* row;
    for (int i = 0; i < height; ++i) {
        row = data->at(i);
        for (int j = 0; j < width; ++j) {
            px = row->at(j);
            delete px;
        }
        delete row;
    }
    delete data;
}

uint32_t BitMap::getWidth() const
{
    return width;
}

uint32_t BitMap::getHeight() const
{
    return height;
}

Pixel* BitMap::getPixel(uint32_t x, uint32_t y) const
{
    return this->data->at(y)->at(x);
}

void BitMap::save(const std::string& path) const
{
    FILE* file = fopen(path.data(), "wb");
    uint8_t* array = getData();
    
    fwrite(array, sizeof(uint8_t), realSize() + 54, file);
    
    delete[] array;
    fclose(file);
}

void BitMap::writeHeader(uint8_t* array) const
{
    uint32_t t_size = realSize();
    
    uint16_t fileTag = 19778;
    uint32_t size = t_size + 54;
    uint16_t rezerved = 0;
    uint32_t offset = 54;
    uint32_t headerSize = 40;
    uint16_t planes = 1;
    uint16_t bpp = 24;
    uint32_t comp = 0;
    uint32_t mapSize = t_size;
    uint32_t xppm = 0;
    uint32_t yppm = 0;
    uint32_t numberOfColors = 0;
    uint32_t importantColors = 0;
    
    writeIntToArray(fileTag, array, 0);
    writeIntToArray(size, array, 2);
    writeIntToArray(rezerved, array, 6);
    writeIntToArray(rezerved, array, 8);
    writeIntToArray(offset, array, 10);
    writeIntToArray(headerSize, array, 14);
    writeIntToArray(width, array, 18);
    writeIntToArray(height, array, 22);
    writeIntToArray(planes, array, 26);
    writeIntToArray(bpp, array, 28);
    writeIntToArray(comp, array, 30);
    writeIntToArray(mapSize, array, 34);
    writeIntToArray(xppm, array, 38);
    writeIntToArray(yppm, array, 42);
    writeIntToArray(numberOfColors, array, 46);
    writeIntToArray(importantColors, array, 50);
}

uint8_t * BitMap::getData() const
{
    uint32_t size = realSize() + 54;
    uint8_t* array = new uint8_t[size]{};
    
    writeHeader(array);
    std::vector<std::vector<Pixel*>*>::const_reverse_iterator vitr = data->rbegin();
    std::vector<std::vector<Pixel*>*>::const_reverse_iterator vend = data->rend();
    
    std::vector<Pixel*>::const_iterator hitr;
    std::vector<Pixel*>::const_iterator hend;
    Pixel* px;
    uint32_t x = 0;
    uint32_t y = 0;
    
    uint32_t padded = (width * 3 + 3) & (~3);
    for (; vitr != vend; ++vitr) {
        std::vector<Pixel*>* row = *vitr;
        hitr = row->begin();
        hend = row->end();
        x = 0;
        for (; hitr != hend; ++hitr) {
            px = *hitr;
            array[54 + y * padded + x * 3 + 0] = px->blue;
            array[54 + y * padded + x * 3 + 1] = px->green;
            array[54 + y * padded + x * 3 + 2] = px->red;
            ++x;
        }
        ++y;
    }
    
    return array;
}

void BitMap::writeIntToArray(uint8_t value, uint8_t* array, uint32_t startIndex)
{
    array[startIndex] = value;
}

void BitMap::writeIntToArray(uint16_t value, uint8_t* array, uint32_t startIndex)
{
    for (int i = 0; i < 2; ++i) {
        array[startIndex + i] = ((uint8_t*)&value)[i];
    }
}

void BitMap::writeIntToArray(uint32_t value, uint8_t* array, uint32_t startIndex)
{
    for (int i = 0; i < 4; ++i) {
        array[startIndex + i] = ((uint8_t*)&value)[i];
    }
}

BitMap* BitMap::rect(uint32_t startx, uint32_t starty, uint32_t endx, uint32_t endy) const
{
    if (endx <= width && endy <= height && startx != endx && starty != endy) {
        uint32_t tW = endx - startx;
        uint32_t tH = endy - starty;
        std::vector<std::vector<Pixel *> *>* target = new std::vector<std::vector<Pixel*>*>(tH, 0);
        std::vector<Pixel*>* sRow;
        std::vector<Pixel*>* tRow;
        uint32_t it = 0;
        uint32_t jt = 0;
        
        for (uint32_t i = starty; i < endy; ++i) {
            sRow = data->at(i);
            tRow = new std::vector<Pixel*>(tW, 0);
            target->at(it++) = tRow;
            
            jt = 0;
            for (uint32_t j = startx; j < endx; ++j) {
                tRow->at(jt++) = sRow->at(j)->copy();
            }
        }
        
        return new BitMap(target);
    } else {
        throw 1;//todo
    }
}

uint32_t BitMap::realSize() const
{
    return ((width * 3 + 3) & (~3)) * height;
}

const Pixel & BitMap::at(uint32_t x, uint32_t y) const
{
    return *(data->at(y)->at(x));
}

void BitMap::draw(const Line& line)
{
    Line::Orientation orient = line.getOrientation();
    for (uint32_t i = 0; i < line.getLength(); ++i) {
        if (orient == Line::Horizontal) {
            draw(line.getX() + i, line.getY(), line.getColor());
        } else {
            draw(line.getX(), line.getY() + i, line.getColor());
        }
    }
}

void BitMap::draw(uint32_t x, uint32_t y, const Pixel& color)
{
    Pixel * px = data->at(y)->at(x);
    data->at(y)->at(x) = color.copy();
    delete px;
}
