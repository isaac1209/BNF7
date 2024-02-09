cmake_minimum_required(VERSION 3.27)
project(BNF7)

set(CMAKE_CXX_STANDARD 17)

add_executable(BNF7 main.cpp
        lexer.cpp
        lexer.h
        parser.h
        parser.cpp)
