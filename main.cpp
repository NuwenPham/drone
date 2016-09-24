#include <iostream>
#include "screenshotParser/screenshotParser.h"

int main()
{
    ScreenshotParser* GlobalParser = new ScreenshotParser();
    GlobalParser->getScreenInfo();

    return 0;
}
