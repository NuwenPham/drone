//
// Created by cubla on 15.09.2016.
//

#include "screenshotParser.h"
//#include "parsers/blank.h"
#include "utils/bitmap.h"
#include <iostream>
#include <stdio.h>

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
//    BitMap* screenshot = capturer->capture();;
//    BitMap* slice = screenshot->rect(0, 0, screenshot->getWidth(), screenshot->getHeight());
//    slice->save("screenshot.bmp");





    this->test();


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

    int rw = screen->getWidth(), rh = screen->getHeight();
    BitMap* screenshot = screen->rect(0, 0, rw, rh);

    std::vector<std::vector<Pixel*>*>* target = new std::vector<std::vector<Pixel*>*>(screen->getHeight(), 0);


    uint32_t mx = 0, my = 0, width = screen->getWidth(), height = screen->getHeight();
    uint32_t iw = bmp->getWidth(), ih = bmp->getHeight();
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

    printf("%i:%i\n" , iw, ih);

    // main loop
    while( my < rh - ih)
    {
        mx = 0;
        while(mx < rw - iw)
        {
            //inner loop

            int amount = 0, count = 0;

            uint32_t ix = 0, iy = 0;
            while (iy < ih)
            {
                ix = 0;
                while(ix < iw )
                {
                   // printf("m: %i:%i / i: %i:%i / all: %i:%i\n", my, mx, iy, ix, (iy + my), (ix + mx));
                    Pixel* searchPixel = bmp->getPixel(ix, iy);
                    Pixel* sourcePixel = screenshot->getPixel(ix + mx, iy + my);
                    Pixel* res = subtraction(searchPixel, sourcePixel);//subtraction(subtraction(searchPixel, sourcePixel), new Pixel(255, 255, 255));
                    //target->at(iy + my)->at(ix + mx) = res;

                    count++;
                    amount += (res->red + res->green + res->blue) / 3;

                    //std::cout << iy + my << ":" << ix + mx << " i: " << iy << ":" <<  ix << " m: " << my << ":" << mx << std::endl;
                    ix++;
                }
                iy++;
            }

            if(amount / count < 10){
                printf("found: %i\n", count);

                ix = 0;
                iy = 0;
                while (iy < ih)
                {
                    ix = 0;
                    while(ix < iw )
                    {
                        // printf("m: %i:%i / i: %i:%i / all: %i:%i\n", my, mx, iy, ix, (iy + my), (ix + mx));
                        Pixel* searchPixel = bmp->getPixel(ix, iy);
                        Pixel* sourcePixel = screenshot->getPixel(ix + mx, iy + my);
//                        Pixel* res = /*subtraction(searchPixel, sourcePixel);//*/subtraction(subtraction(searchPixel, sourcePixel), new Pixel(255, 255, 255));
                        Pixel* res = searchPixel->copy();
                        target->at(iy + my)->at(ix + mx) = res;

//                        count++;
//                        amount += (res->red + res->green + res->blue) / 3;

                        //std::cout << iy + my << ":" << ix + mx << " i: " << iy << ":" <<  ix << " m: " << my << ":" << mx << std::endl;
                        ix++;
                    }
                    iy++;
                }

            }


            // main loop
            mx++;
        }

        my++;
    }

    BitMap* bm = new BitMap(target);
    bm->save("compare.bmp");

    int b = 0;
}
