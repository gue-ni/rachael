cmake_minimum_required(VERSION 3.10)
project(chess_engine_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -pthread -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

add_executable(engine_cli src/cli.cpp src/engine/SimpleBoard.cpp src/engine/SimpleBoard.h
        src/engine/Square.cpp src/engine/Square.h src/engine/Ply.cpp src/engine/Ply.h src/engine/Search.cpp src/engine/Search.h
        src/engine/Reversible.cpp src/engine/Reversible.h)

add_executable(rachael src/uci.cpp src/engine/SimpleBoard.cpp src/engine/SimpleBoard.h
        src/engine/Square.cpp src/engine/Square.h src/engine/Ply.cpp src/engine/Ply.h src/engine/Search.cpp src/engine/Search.h
        src/engine/Reversible.cpp src/engine/Reversible.h src/engine/Search2.cpp src/engine/Search2.h)

add_executable(unittest test/unittest.cpp src/engine/SimpleBoard.cpp src/engine/SimpleBoard.h
        src/engine/Square.cpp src/engine/Square.h src/engine/Ply.cpp src/engine/Ply.h src/engine/Search.cpp src/engine/Search.h
        src/engine/Search2.cpp src/engine/Search2.h
        src/engine/Reversible.cpp src/engine/Reversible.h test/util.h)

add_executable(benchmark test/benchmark.cpp src/engine/SimpleBoard.cpp src/engine/SimpleBoard.h
        src/engine/Square.cpp src/engine/Square.h src/engine/Ply.cpp src/engine/Ply.h
        src/engine/Search.cpp src/engine/Search.h src/engine/Reversible.cpp src/engine/Reversible.h test/util.h)
