//
// Created by cubla on 21.09.2016.
//

#include "color.h"


Color::Color(int r = 0, int g = 0, int b = 0)
{
    this->r = r;
    this->g = g;
    this->b = b;
}
Color::~Color()
{

}

int Color::getR()
{
    return this->r;
}

int Color::getG()
{
    return this->g;
}

int Color::getB()
{
    return  this->b;
}

bool Color::equals(Color* c)
{
    return this->r == c->r && this->g == c->g && this->b == c->b;
}

