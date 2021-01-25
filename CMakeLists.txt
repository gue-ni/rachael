cmake_minimum_required(VERSION 3.15)
project(chess_engine_cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

add_executable(engine src/main.cpp src/Board.cpp src/Board.h
        src/Square.cpp src/Square.h src/Ply.cpp src/Ply.h src/AI.cpp src/AI.h)

add_executable(unittest test/unittest.cpp src/Board.cpp src/Board.h
        src/Square.cpp src/Square.h src/Ply.cpp src/Ply.h src/AI.cpp src/AI.h)
