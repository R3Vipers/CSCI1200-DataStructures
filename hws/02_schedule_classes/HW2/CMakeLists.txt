cmake_minimum_required(VERSION 3.26)
project(HW2)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW2 main.cpp
        Room.h
        Room.cpp
        course.h
        course.cpp
        Department.h
        Department.cpp
        Custom.h
        Custom.cpp)
