//
// Created by cubla on 21.09.2016.
//

#include <iostream>
#include "tableParser.h"
#include "../../utils/color.h"


TablesParser::TablesParser(BMPHelper* bmp)
{
    this->_bmpData = bmp;
}

TablesParser::~TablesParser()
{

}
void TablesParser::Parse()
{
    //frame
    Vector2 topLeft = this->SearchTopLeft();
    if (topLeft.x != -1)
    {
        Vector2 topRight = this->SearchTopRight(&topLeft);
        if(topRight.x != -1)
        {
            Vector2 bottomLeft = this->SearchBottomLeft(&topLeft);
            if(bottomLeft.x != -1)
            {
                HWND console_handle = GetConsoleWindow();
                HDC device_context = GetDC(console_handle);
                HDC hScreen = GetDC(GetDesktopWindow());

                int b = 0;
                while(b < 20000)
                {
                    int a = topLeft.x;
                    while (a < topRight.x)
                    {

                        SetPixel(hScreen, a, topRight.y, RGB(255, 0, 0));

                        a++;
                    }


                    a = topLeft.y;
                    while (a < bottomLeft.y)
                    {

                        SetPixel(hScreen, bottomLeft.x, a, RGB(255, 0, 0));
                        a++;
                    }
                    b++;

                }

            }
        }
    }
}

Vector2 TablesParser::SearchTopLeft()
{
    int indexHeight = 0, indexWidth = 0;
    while (indexHeight < this->_bmpData->height)
    {
        indexWidth = 0;
        while (indexWidth < this->_bmpData->width)
        {
            // Ищем верхний левый уголок. :)
            Color* curColor = this->_bmpData->GetPixel(indexWidth, indexHeight, this->_bmpData->width, 3);
            if (this->IsCaldariCornerColor(curColor))
            {
                std::cout << "x=0,y=0" << std::endl;
                // left +1
                curColor = this->_bmpData->GetPixel(indexWidth + 1, indexHeight, this->_bmpData->width, 3);
                if (this->IsCaldariCornerColor(curColor))
                {
                    std::cout << "x=1,y=0" << std::endl;
                    // left +2
                    curColor = this->_bmpData->GetPixel(indexWidth + 2, indexHeight, this->_bmpData->width, 3);
                    if (this->IsCaldariCornerColor(curColor))
                    {
                        std::cout << "x=2,y=0" << std::endl;
                        // left +0, top +1
                        curColor = this->_bmpData->GetPixel(indexWidth, indexHeight + 1, this->_bmpData->width, 3);
                        if (this->IsCaldariCornerColor(curColor))
                        {
                            std::cout << "x=0,y=1" << std::endl;
                            // left +0, top +2
                            curColor = this->_bmpData->GetPixel(indexWidth, indexHeight + 2, this->_bmpData->width, 3);
                            if (this->IsCaldariCornerColor(curColor))
                            {
                                std::cout << "x=0,y=2" << std::endl;
                                return Vector2(indexWidth, indexHeight);
                            }


                        }

                    }
                }
            }
            //std::cout << indexWidth << ":" << indexHeight << " (" << curColor->getR() << ", " << curColor->getG() << ", " << curColor->getB() << ", " << std::endl;
            indexWidth++;
        }
        indexHeight++;
    }
    return Vector2(-1,-1);
    //std::cout << "end" << std::endl;
}

Vector2 TablesParser::SearchTopRight(Vector2* _topLeft)
{
    bool isInterrupt = false;
    int a = _topLeft->x + 4;
    while(a < this->_bmpData->width)
    {
        Color* curColor = this->_bmpData->GetPixel(a, _topLeft->y,  this->_bmpData->width, 3);

        std::cout << a << ":" << _topLeft->y << " (" << curColor->getR() << ", " << curColor->getG() << ", " << curColor->getB() << ", " << std::endl;

        if(this->IsCaldariLineColor(curColor))
        {
            // ну вроде все ок
        }
        else if(this->IsCaldariCornerColor(curColor))
        {
            std::cout << "x=0,y=0" << std::endl;
            // Нашли угол
            curColor = this->_bmpData->GetPixel(a + 1, _topLeft->y,  this->_bmpData->width, 3);
            if(this->IsCaldariCornerColor(curColor))
            {
                std::cout << "x=1,y=0" << std::endl;
                curColor = this->_bmpData->GetPixel(a + 2, _topLeft->y,  this->_bmpData->width, 3);
                if(this->IsCaldariCornerColor(curColor))
                {
                    std::cout << "x=2,y=0" << std::endl;
                    curColor = this->_bmpData->GetPixel(a + 2, _topLeft->y + 1,  this->_bmpData->width, 3);
                    if(this->IsCaldariCornerColor(curColor))
                    {
                        std::cout << "x=2,y=1" << std::endl;
                        curColor = this->_bmpData->GetPixel(a + 2, _topLeft->y + 2,  this->_bmpData->width, 3);
                        if(this->IsCaldariCornerColor(curColor))
                        {
                            std::cout << "x=2,y=2" << std::endl;
                            return Vector2(a + 2, _topLeft->y);
                        }
                    }
                }
            }
        }
        else
        {
            isInterrupt = true;
        }

        if(isInterrupt)
        {
            return Vector2(-1,-1);
        }

        a++;
    }
    return Vector2(-1,-1);
}

Vector2 TablesParser::SearchBottomLeft(Vector2* _topLeft)
{
    bool isInterrupt = false;
    int a = _topLeft->y + 4;
    while(a < this->_bmpData->height)
    {
        Color* curColor = this->_bmpData->GetPixel(_topLeft->x, a,  this->_bmpData->width, 3);
        if(this->IsCaldariLineColor(curColor))
        {
            // ну вроде все ок
        }
        else if(this->IsCaldariCornerColor(curColor))
        {
            std::cout << "x=0,y=0" << std::endl;
            // Нашли угол
            curColor = this->_bmpData->GetPixel(_topLeft->x, a + 1,  this->_bmpData->width, 3);
            if(this->IsCaldariCornerColor(curColor))
            {
                std::cout << "x=0,y=1" << std::endl;
                curColor = this->_bmpData->GetPixel(_topLeft->x, a + 2,  this->_bmpData->width, 3);
                if(this->IsCaldariCornerColor(curColor))
                {
                    std::cout << "x=0,y=2" << std::endl;
                    curColor = this->_bmpData->GetPixel(_topLeft->x + 1, a + 2,  this->_bmpData->width, 3);
                    if(this->IsCaldariCornerColor(curColor))
                    {
                        std::cout << "x=1,y=2" << std::endl;
                        curColor = this->_bmpData->GetPixel(_topLeft->x + 2, a + 2,  this->_bmpData->width, 3);
                        if(this->IsCaldariCornerColor(curColor))
                        {
                            std::cout << "x=2,y=2" << std::endl;
                            return Vector2(_topLeft->x, a + 2);
                        }
                    }
                }
            }
        }
        else
        {
            isInterrupt = true;
        }

        if(isInterrupt)
        {
            return Vector2(-1,-1);
        }

        a++;
    }
    return Vector2(-1,-1);
}

bool TablesParser::IsCaldariCornerColor(Color* _color){
    return _color->equals(this->color_caldariDarkII_corners_noactive) || _color->equals(this->color_caldariDarkII_corners_active);
}

bool TablesParser::IsCaldariLineColor(Color* _color){
    return this->color_caldariDarkII_line_noactive->equals(_color)
            || this->color_caldariDarkII_line_active->equals(_color)
            || this->color_caldariDarkII_edges_active->equals(_color)
            || this->color_caldariDarkII_edges_noactive->equals(_color);
}