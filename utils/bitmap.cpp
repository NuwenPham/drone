#include "bitmap.h"
#include <iostream>

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

void BitMap::save(const std::string& path) const
{
    FILE* file = fopen(path.data(), "wb");
    writeHeader(file);
    
    std::vector<std::vector<Pixel*>*>::const_reverse_iterator vitr = data->rbegin();
    std::vector<std::vector<Pixel*>*>::const_reverse_iterator vend = data->rend();
    
    std::vector<Pixel*>::const_iterator hitr;
    std::vector<Pixel*>::const_iterator hend;
    Pixel* px;
    uint64_t c = 0;
    
    uint64_t padded = (width * 3 + 3) & (~3);
    uint8_t* buffer = new uint8_t[padded]{};
    for (; vitr != vend; ++vitr) {
        std::vector<Pixel*>* row = *vitr;
        hitr = row->begin();
        hend = row->end();
        c = 0;
        for (; hitr != hend; ++hitr) {
            px = *hitr;
            buffer[c * 3 + 0] = px->blue;
            buffer[c * 3 + 1] = px->green;
            buffer[c * 3 + 2] = px->red;
            ++c;
        }
        fwrite(buffer, sizeof(uint8_t), padded, file);
    }
    delete[] buffer;
    
    fclose(file);
}

void BitMap::writeHeader(FILE* file) const
{
    uint32_t t_size = realSize();
    uint16_t fileTag[1] = {19778};
    uint32_t size[1] = {t_size + 54};
    uint16_t rezerved[2] = {0, 0};
    uint32_t offset[1] = {54}; //1078???
    
    uint32_t headerSize[1] = {40};
    uint32_t wh[2] {width, height};
    uint16_t planes[1] = {1};
    uint16_t bpp[1] = {24};
    uint32_t comp[1] = {0};
    uint32_t mapSize[1] = {t_size};
    uint32_t xppm[1] = {0};
    uint32_t yppm[1] = {0};
    uint32_t numberOfColors[1] = {0};
    uint32_t importantColors[1] = {0};
    
    fwrite(fileTag, sizeof(uint16_t), 1, file);
    fwrite(size, sizeof(uint32_t), 1, file);
    fwrite(rezerved, sizeof(uint16_t), 2, file);
    fwrite(offset, sizeof(uint32_t), 1, file);
    fwrite(headerSize, sizeof(uint32_t), 1, file);
    fwrite(wh, sizeof(uint32_t), 2, file);
    fwrite(planes, sizeof(uint16_t), 1, file);
    fwrite(bpp, sizeof(uint16_t), 1, file);
    fwrite(comp, sizeof(uint32_t), 1, file);
    fwrite(mapSize, sizeof(uint32_t), 1, file);
    fwrite(xppm, sizeof(uint32_t), 1, file);
    fwrite(yppm, sizeof(uint32_t), 1, file);
    fwrite(numberOfColors, sizeof(uint32_t), 1, file);
    fwrite(importantColors, sizeof(uint32_t), 1, file);
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


