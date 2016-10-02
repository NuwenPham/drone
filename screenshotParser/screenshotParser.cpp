//
// Created by cubla on 15.09.2016.
//

#include "screenshotParser.h"
//#include "parsers/blank.h"
#include "utils/bitmap.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>

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
    
//     BitMap* screenshot1 = new BitMap("1.bmp");
//     std::pair<std::list<Line>, std::list<Line>> pair = parser->detect(*screenshot1);
//     
//     std::cout << "Horizontal lines count: " << pair.first.size() << std::endl;
//     std::cout << "Vertical lines count: " << pair.second.size() << std::endl;
//     
//     std::list<BitMap*> frames = frameConstructor->construct(*screenshot1, pair);
    test();

    // Тестовый парсер скриншота
    // ---
    // Может быть стоит задуматься над тем, что вначале будет один большой чувак,
    // который как-то определить где находятся виджеты
    // ---
    //Blank* b = new Blank();
}

Pixel* subtraction(Pixel* p1, Pixel* p2)
{
    uint8_t red =  p1->red >= p2->red ? p1->red - p2->red : p2->red - p1->red;
    uint8_t green =  p1->green >= p2->green ? p1->green - p2->green : p2->green - p1->green;
    uint8_t blue =  p1->blue >= p2->blue ? p1->blue - p2->blue : p2->blue - p1->blue;
    return new Pixel(red, green, blue);
}

void ScreenshotParser::test()
{

    BitMap* screen = new BitMap("../images/screenshot.bmp");
    BitMap* bmp = new BitMap("../images/widget/corners/leftTop_inactive.bmp");

    std::vector<BitMap*>* templates = new std::vector<BitMap*>();
    templates->push_back(new BitMap("../images/widget/corners/leftTop_inactive.bmp"));
    templates->push_back(new BitMap("../images/widget/corners/rightTop_inactive.bmp"));
    templates->push_back(new BitMap("../images/widget/corners/leftBottom_inactive.bmp"));
    templates->push_back(new BitMap("../images/widget/corners/rightBottom_inactive.bmp"));
    templates->push_back(new BitMap("../images/widget/corners/leftTop_active.bmp"));
    templates->push_back(new BitMap("../images/widget/corners/rightTop_active.bmp"));
    templates->push_back(new BitMap("../images/widget/corners/leftBottom_active.bmp"));
    templates->push_back(new BitMap("../images/widget/corners/rightBottom_active.bmp"));

    int rw = screen->getWidth(), rh = screen->getHeight();
    BitMap* screenshot = screen->rect(0, 0, rw, rh);

    std::vector<std::vector<Pixel*>*>* target = new std::vector<std::vector<Pixel*>*>(screen->getHeight(), 0);


    uint32_t mx = 0, my = 0, width = screen->getWidth(), height = screen->getHeight();

    std::vector<Pixel*>* row;

    while( my < height )
    {
        mx = 0;
        row = new std::vector<Pixel*>(width, 0);
        target->at(my) = row;
        while(mx < width)
        {
            row->at(mx) = new Pixel(0,0,0);
            mx++;
        }
        my++;
    }


    mx = 0;
    my = 0;

    BitMap* current;
    std::cout<< "start" << std::endl;
    uint32_t iw, ih, amount, count, ix, iy, a;
    // main loop
    try
    {


        while (my < rh)
        {
            mx = 0;
            while (mx < rw)
            {
                //inner loop
                a = 0;
                while (a < templates->size())
                {
                    current = templates->at(a);


                    iw = current->getWidth();
                    ih = current->getHeight();
                    //printf("%i:%i\n" , iw, ih);
                    if (ih + my >= rh || iw + mx >= rw)
                    {
                        mx++;
                        a++;
                        continue;
                    }


                    amount = 0;
                    count = 0;
                    ix = 0;
                    iy = 0;
                    while (iy < ih)
                    {
                        ix = 0;
                        while (ix < iw)
                        {
                            // printf("m: %i:%i / i: %i:%i / all: %i:%i\n", my, mx, iy, ix, (iy + my), (ix + mx));
                            Pixel* res = subtraction(current->getPixel(ix, iy), screenshot->getPixel(ix + mx, iy + my));
                            //subtraction(subtraction(searchPixel, sourcePixel), new Pixel(255, 255, 255));
                            //target->at(iy + my)->at(ix + mx) = res;

                            count++;
                            amount += (res->red + res->green + res->blue) / 3;
                            delete res;
                            //std::cout << iy + my << ":" << ix + mx << " i: " << iy << ":" <<  ix << " m: " << my << ":" << mx << std::endl;
                            ix++;
                        }
                        iy++;
                    }

                    if (amount / count < 10)
                    {
                        printf("(%i) found: %i\n", a, count);

                        ix = 0;
                        iy = 0;
                        while (iy < ih)
                        {
                            ix = 0;
                            while (ix < iw)
                            {
                                // printf("m: %i:%i / i: %i:%i / all: %i:%i\n", my, mx, iy, ix, (iy + my), (ix + mx));
//                        Pixel* res = /*subtraction(searchPixel, sourcePixel);//*/subtraction(subtraction(searchPixel, sourcePixel), new Pixel(255, 255, 255));

                                target->at(iy + my)->at(ix + mx) = current->getPixel(ix, iy)->copy();

//                        count++;
//                        amount += (res->red + res->green + res->blue) / 3;

                                //std::cout << iy + my << ":" << ix + mx << " i: " << iy << ":" <<  ix << " m: " << my << ":" << mx << std::endl;
                                ix++;
                            }
                            iy++;
                        }

                    }
                    a++;
                }

                // main loop
                mx++;
            }

            my++;
        }
    }catch(int i) {
        printf("m: %i:%i / i: %i:%i / all: %i:%i\n", my, mx, iy, ix, (iy + my), (ix + mx));
        sleep(100000);
    }

    BitMap* bm = new BitMap(target);
    bm->save("compare.bmp");
    std::cout<< "end" << std::endl;
}

