//
// Created by cubla on 18.09.2016.
//

#ifndef DRONE_SCREENSHOTMAKERWINDOWS_H
#define DRONE_SCREENSHOTMAKERWINDOWS_H

#include "utils/bitmap.h"
#include "utils/pixel.h"
#include "vector"
#include <windows.h>
#include <utility>

class ScreenshotMakerWindows
{
public:
    ScreenshotMakerWindows();
    ~ScreenshotMakerWindows();
    
    BitMap* capture();
    
private:
    
};

#endif //DRONE_SCREENSHOTMAKERWINDOWS_H
