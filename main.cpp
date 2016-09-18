#include <iostream>
#include <windows.h>
#include "screenshotParser/screenshotParser.h"

ScreenshotParser* GlobalParser = new ScreenshotParser();

int main()
{

    GlobalParser->getScreenInfo();

    Sleep(10000);
    return 0;
}