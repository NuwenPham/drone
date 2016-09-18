//
// Created by cubla on 15.09.2016.
//

#include "screenshotParser.h"
#include "parsers/blank.h"
#include "../utils/bmphelper.h"
#include "screenshotMakerWindows.h"

ScreenshotParser::ScreenshotParser()
{

}

ScreenshotParser::~ScreenshotParser()
{

}

/**
 * Возвращает все возможные результаты, которые можно получить после вызова это функции ( все что было распознано )
 */
void ScreenshotParser::getScreenInfo()
{
    // наши данные о скриноште ( ширина, высота и буфер )
    BMPHelper* screenshot = getScreenShotData();

    // Тестовый парсер скриншота
    // ---
    // Может быть стоит задуматься над тем, что вначале будет один большой чувак,
    // который как-то определить где находятся виджеты
    // ---
    Blank* b = new Blank();
}