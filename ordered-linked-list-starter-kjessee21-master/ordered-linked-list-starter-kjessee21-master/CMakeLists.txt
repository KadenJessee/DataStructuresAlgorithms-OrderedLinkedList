cmake_minimum_required(VERSION 3.14)
project(linked_list)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(inc)

add_executable(linked_list
        inc/LinkedList.h
        inc/MemberDO.h
        src/MemberDO.cpp
        src/LinkedListTest.cpp)
