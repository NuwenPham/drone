cmake_minimum_required(VERSION 2.6)

set(SOURCE_FILES
    pixel.cpp
    bitmap.cpp
    line.cpp
)

set(HEADER_FILES
    pixel.h
    bitmap.h
    line.h
)

add_library(utils STATIC ${SOURCE_FILES} ${HEADER_FILES})
