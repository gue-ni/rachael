cmake_minimum_required(VERSION 3.10)
project(chess_engine_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -pthread -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

add_executable(engine src/main.cpp src/Board.cpp src/Board.h
        src/Square.cpp src/Square.h src/Ply.cpp src/Ply.h src/Engine.cpp src/Engine.h
        src/Reversible.cpp src/Reversible.h src/CachedBoard.cpp src/CachedBoard.h)

add_executable(unittest test/unittest.cpp src/Board.cpp src/Board.h
        src/Square.cpp src/Square.h src/Ply.cpp src/Ply.h src/Engine.cpp src/Engine.h
        src/Reversible.cpp src/Reversible.h src/CachedBoard.cpp src/CachedBoard.h)

add_executable(benchmark test/benchmark.cpp)
