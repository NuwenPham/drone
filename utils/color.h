//
// Created by cubla on 21.09.2016.
//

#ifndef DRONE_COLOR_H
#define DRONE_COLOR_H


class Color
{
public:
    Color(int,int,int);
    ~Color();
    int getR();
    int getG();
    int getB();
    bool equals(Color*);
private:
    int r = 0;
    int g = 0;
    int b = 0;
};


#endif //DRONE_COLOR_H
