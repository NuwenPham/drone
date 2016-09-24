//
// Created by cubla on 21.09.2016.
//

#ifndef DRONE_TABLESPARSER_H
#define DRONE_TABLESPARSER_H

#include "../../utils/bmphelper.h"
#include "../../utils/color.h"
#include "../../utils/vector2.h"

class TablesParser
{
public:
    TablesParser(BMPHelper*);
    ~TablesParser();
    void Parse();

    BMPHelper* _bmpData;

    // colors of them CaldariDark II
    // no active
    Color* color_caldariDarkII_corners_noactive = new Color(120, 132, 147);
    Color* color_caldariDarkII_edges_noactive = new Color(49, 54, 58);
    Color* color_caldariDarkII_line_noactive = new Color(35, 38, 40);

    Color* color_caldariDarkII_corners_active = new Color(204, 226, 255);
    Color* color_caldariDarkII_edges_active = new Color(70, 80, 90);
    Color* color_caldariDarkII_line_active = new Color(42, 49, 57);


    bool IsCaldariCornerColor(Color* _color);
    bool IsCaldariLineColor(Color* _color);

    Vector2 SearchTopLeft();
    Vector2 SearchTopRight(Vector2*);
    Vector2 SearchBottomLeft(Vector2*);
};


#endif //DRONE_TABLESPARSER_H
