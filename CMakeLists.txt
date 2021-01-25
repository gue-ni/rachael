cmake_minimum_required(VERSION 3.15)
project(chess_engine_cpp)

set(CMAKE_CXX_STANDARD 11)

add_executable(engine src/main.cpp src/Board.cpp src/Board.h src/Algrebraic.cpp src/Algrebraic.h src/Ply.cpp src/Ply.h src/AI.cpp src/AI.h)
add_executable(unittest test/unittest.cpp src/Board.cpp src/Board.h src/Algrebraic.cpp src/Algrebraic.h src/Ply.cpp src/Ply.h src/AI.cpp src/AI.h)
