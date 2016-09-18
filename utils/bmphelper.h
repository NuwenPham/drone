//
// Created by cubla on 18.09.2016.
//

#ifndef DRONE_BMPHELPER_H
#define DRONE_BMPHELPER_H

#include <windows.h>

class BMPHelper
{
public:
    byte* pixelBuffer;
    int width = 0;
    int height = 0;
    BMPHelper(int width, int height, byte* buffer);
};



#endif //DRONE_BMPHELPER_H
