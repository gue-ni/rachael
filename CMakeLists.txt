cmake_minimum_required(VERSION 3.10)
project(chess_engine_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -pthread -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

add_executable(engine src/main.cpp src/SimpleBoard.cpp src/SimpleBoard.h
        src/Square.cpp src/Square.h src/Ply.cpp src/Ply.h src/Search.cpp src/Search.h
        src/Reversible.cpp src/Reversible.h)

add_executable(unittest test/unittest.cpp src/SimpleBoard.cpp src/SimpleBoard.h
        src/Square.cpp src/Square.h src/Ply.cpp src/Ply.h src/Search.cpp src/Search.h
        src/Reversible.cpp src/Reversible.h)

add_executable(benchmark test/benchmark.cpp src/SimpleBoard.cpp src/SimpleBoard.h
        src/Square.cpp src/Square.h src/Ply.cpp src/Ply.h src/Search.cpp src/Search.h
        src/Reversible.cpp src/Reversible.h test/util.h)
