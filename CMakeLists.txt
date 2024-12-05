cmake_minimum_required(VERSION 3.20)
project(Advent)

set(CMAKE_CXX_STANDARD 14)

add_executable(Advent main.cpp 1.cpp 2.cpp 3.cpp 4.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Input/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Input/)
