//
// Created by cubla on 15.09.2016.
//

#include "screenshotParser.h"
//#include "parsers/blank.h"
#include "utils/bitmap.h"
#include "iostream"

ScreenshotParser::ScreenshotParser():
    Base(),
    capturer(new ScreenshotMaker()),
    parser(new EdgesDetector(100)),
    frameConstructor(new FrameConstructor(3, 50))
{

}

ScreenshotParser::~ScreenshotParser()
{
    delete capturer;
    delete parser;
}

/**
 * Возвращает все возможные результаты, которые можно получить после вызова это функции ( все что было распознано )
 */
void ScreenshotParser::getScreenInfo()
{
    // наши данные о скриноште ( ширина, высота и буфер )
//     BitMap* screenshot = capturer->capture();;
//     BitMap* slice = screenshot->rect(200, 200, 500, 500);
//     slice->save("screenshot.bmp");
    
    BitMap* screenshot1 = new BitMap("1.bmp");
    std::pair<std::list<Line>, std::list<Line>> pair = parser->detect(*screenshot1);
    
    std::cout << "Horizontal lines count: " << pair.first.size() << std::endl;
    std::cout << "Vertical lines count: " << pair.second.size() << std::endl;
    
    std::list<BitMap*> frames = frameConstructor->construct(*screenshot1, pair);
    // Тестовый парсер скриншота
    // ---
    // Может быть стоит задуматься над тем, что вначале будет один большой чувак,
    // который как-то определить где находятся виджеты
    // ---
    //Blank* b = new Blank();
}
