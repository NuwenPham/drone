cmake_minimum_required(VERSION 2.6)

set(SOURCE_FILES
    screenshotParser.cpp
)

set(HEADER_FILES
    screenshotParser.h
)

if (WIN32)
    set(SSM
        screenshotMakerWindows.cpp
        screenshotMakerWindows.h
    )
endif(WIN32)

if (UNIX)
    set(SSM
        screenshotMakerUnix.cpp
        screenshotMakerUnix.h
    )
endif(UNIX)

add_library(screenshotParser STATIC ${SOURCE_FILES} ${HEADER_FILES} ${SSM})

target_link_libraries(screenshotParser utils)

if(UNIX)
    target_link_libraries(screenshotParser X11)
endif(UNIX)
