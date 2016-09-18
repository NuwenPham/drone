//
// Created by cubla on 18.09.2016.
//

#include <windows.h>
#include <utility>
#include "screenshotMakerWindows.h"



BMPHelper* getScreenShotData() {
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
    bmi.biBitCount = 32;
    bmi.biWidth = ScreenX;
    bmi.biHeight = -ScreenY;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;
    ScreenData = new byte[4 * ScreenX * ScreenY];
    GetDIBits(hScreen, hBitmap, 0, ScreenY, ScreenData, (BITMAPINFO*) &bmi, DIB_RGB_COLORS);

    return new BMPHelper(bmi.biWidth, bmi.biHeight, ScreenData);
}
