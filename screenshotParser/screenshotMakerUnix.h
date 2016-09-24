#ifndef SCREENSHOTMAKERUNIX_H
#define SCREENSHOTMAKERUNIX_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdint.h>
#include <vector>
#include "utils/bitmap.h"
#include "utils/pixel.h"

class ScreenshotMakerUnix
{
public:
    ScreenshotMakerUnix();
    ~ScreenshotMakerUnix();
    
    BitMap* capture();
    
private:
    Display *display;
    Window root;
    XWindowAttributes* gwa;
    uint32_t width;
    uint32_t height;
};

#endif // SCREENSHOTMAKERUNIX_H
