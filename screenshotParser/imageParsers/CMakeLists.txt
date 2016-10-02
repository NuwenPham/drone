cmake_minimum_required(VERSION 2.6)

set(SOURCE_FILES
#    tableParserOcv.cpp
    edgesdetector.cpp
    frameconstructor.cpp
)

set(HEADER_FILES
#    tableParserOcv.h
    edgesdetector.h
    frameconstructor.h
)

#find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui features2d xfeatures2d)

add_library(imp STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(imp utils)
#target_link_libraries(imp ${OpenCV_LIBS})
