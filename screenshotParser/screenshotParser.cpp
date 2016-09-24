//
// Created by cubla on 15.09.2016.
//

#include "screenshotParser.h"
//#include "parsers/blank.h"
#include "utils/bitmap.h"

ScreenshotParser::ScreenshotParser():
    Base(),
    capturer(new ScreenshotMaker())
{

}

ScreenshotParser::~ScreenshotParser()
{
    delete capturer;
}

/**
 * Возвращает все возможные результаты, которые можно получить после вызова это функции ( все что было распознано )
 */
void ScreenshotParser::getScreenInfo()
{
    // наши данные о скриноште ( ширина, высота и буфер )
    BitMap* screenshot = capturer->capture();;
    BitMap* slice = screenshot->rect(200, 200, 500, 500);
    slice->save("screenshot.bmp");
    // Тестовый парсер скриншота
    // ---
    // Может быть стоит задуматься над тем, что вначале будет один большой чувак,
    // который как-то определить где находятся виджеты
    // ---
    //Blank* b = new Blank();
}
