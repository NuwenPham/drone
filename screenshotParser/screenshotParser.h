//
// Created by cubla on 15.09.2016.
//

#ifndef DRONE_SCREENSHOTPARSER_H
#define DRONE_SCREENSHOTPARSER_H

#include "base.h"
#include "imageParsers/edgesdetector.h"
#include "imageParsers/frameconstructor.h"

#ifdef _WIN32
    #include "screenshotMakerWindows.h"
    typedef ScreenshotMakerWindows ScreenshotMaker;
#else
    #include "screenshotMakerUnix.h"
    typedef ScreenshotMakerUnix ScreenshotMaker;
#endif


class ScreenshotParser : public Base
{
public:
    ScreenshotParser();
    ~ScreenshotParser();
    void getScreenInfo();
    
private:
    ScreenshotMaker* capturer;
    EdgesDetector* parser;
    FrameConstructor* frameConstructor;

};


#endif //DRONE_SCREENSHOTPARSER_H
