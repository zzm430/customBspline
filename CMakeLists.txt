cmake_minimum_required(VERSION 3.15)
project(testBspline)

set(CMAKE_CXX_STANDARD 11)

add_executable(testBspline main.cpp customBspline.h customBspline.cpp)
#add_executable(testBspline test.cpp)