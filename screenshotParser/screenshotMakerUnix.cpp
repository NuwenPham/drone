#include "screenshotMakerUnix.h"

ScreenshotMakerUnix::ScreenshotMakerUnix():
    display(XOpenDisplay(NULL)),
    root(DefaultRootWindow(display)),
    gwa(new XWindowAttributes())
{
    XGetWindowAttributes(display, root, gwa);
    width = gwa->width;
    height = gwa->height;
}

ScreenshotMakerUnix::~ScreenshotMakerUnix()
{
    XFree(gwa);
    XFree(display);
}


BitMap * ScreenshotMakerUnix::capture()
{
    XImage *image = XGetImage(display, root, 0,0 , width, height, AllPlanes, ZPixmap);

    std::vector<std::vector<Pixel*>*>* data = new std::vector<std::vector<Pixel*>*>(height, 0);

    uint32_t red_mask = image->red_mask;
    uint32_t green_mask = image->green_mask;
    uint32_t blue_mask = image->blue_mask;

    for (int y = 0; y < height; ++y) {
        std::vector<Pixel*>* row = new std::vector<Pixel*>(width, 0);
        data->at(y) = row;
        for (int x = 0; x < width ; ++x) {
            uint32_t pixel = XGetPixel(image,x,y);

            uint8_t blue = pixel & blue_mask;
            uint8_t green = (pixel & green_mask) >> 8;
            uint8_t red = (pixel & red_mask) >> 16;

            row->at(x) = new Pixel(red, green, blue);
        }
    }
    
    BitMap* bm = new BitMap(data);
    
    XFree(image);
    return bm;
}
