cmake_minimum_required(VERSION 2.6)
project(drone)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#set(CMakeRoot "D:/others/ccp/drone")
#
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMakeRoot}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMakeRoot}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMakeRoot}/bin)

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(utils)
add_subdirectory(screenshotParser)

set(SOURCE_FILES
    main.cpp
    base.cpp
)

set(HEADER_FILES
    base.h
) 

add_executable(drone ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(drone utils)
target_link_libraries(drone screenshotParser)
