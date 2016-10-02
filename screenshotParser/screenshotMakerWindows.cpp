//
// Created by cubla on 18.09.2016.
//

#include "screenshotMakerWindows.h"

ScreenshotMakerWindows::ScreenshotMakerWindows()
{
}

ScreenshotMakerWindows::~ScreenshotMakerWindows()
{
}

BitMap * ScreenshotMakerWindows::capture()
{
    byte* ScreenData = 0;
    HDC hScreen = GetDC(GetDesktopWindow());
    int ScreenX = GetDeviceCaps(hScreen, HORZRES);
    int ScreenY = GetDeviceCaps(hScreen, VERTRES);

    HDC hdcMem = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, ScreenX, ScreenY);
    HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, ScreenX, ScreenY, hScreen, 0, 0, SRCCOPY);
    SelectObject(hdcMem, hOld);

    BITMAPINFOHEADER bmi = {0};
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 24;
    bmi.biWidth = ScreenX;
    bmi.biHeight = -ScreenY;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;
    ScreenData = new byte[3 * ScreenX * ScreenY];
    GetDIBits(hScreen, hBitmap, 0, ScreenY, ScreenData, (BITMAPINFO*) &bmi, DIB_RGB_COLORS);
    
    std::vector<std::vector<Pixel*>*>* data = new std::vector<std::vector<Pixel*>*>(ScreenY, 0);

    for (int y = 0; y < ScreenY; ++y) {
        std::vector<Pixel*>* row = new std::vector<Pixel*>(bmi.biWidth, 0);
        data->at(y) = row;
        for (int x = 0; x < bmi.biWidth ; ++x) {
            uint8_t blue = ScreenData[(bmi.biWidth * y + x) * 3];
            uint8_t green = ScreenData[(bmi.biWidth * y + x) * 3 + 1];
            uint8_t red = ScreenData[(bmi.biWidth * y + x )* 3 + 2];

            row->at(x) = new Pixel(red, green, blue);
        }
    }
    
    BitMap* bm = new BitMap(data);
    return bm;
}
