cmake_minimum_required(VERSION 3.3)
project(drone)

set(CMakeRoot "D:/others/ccp/drone")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMakeRoot}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMakeRoot}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMakeRoot}/bin)

set(SOURCE_FILES main.cpp base.cpp base.h screenshotParser/screenshotParser.cpp screenshotParser/screenshotParser.h screenshotParser/parsers/blank.cpp screenshotParser/parsers/blank.h screenshotParser/screenshotMakerWindows.cpp screenshotParser/screenshotMakerWindows.h utils/bmphelper.cpp utils/bmphelper.h)
add_executable(drone ${SOURCE_FILES})