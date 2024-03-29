cmake_minimum_required(VERSION 3.10)
project(rachael)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

add_executable(engine "src/Cli.cpp"
        src/Board.cpp src/Board.h
        src/Search.cpp src/Search.h
        src/SquareClass.cpp src/SquareClass.h
        src/Ply.cpp src/Ply.h
        src/Reversible.cpp src/Reversible.h
        src/Evaluation.cpp src/Evaluation.h )

add_executable(rachael "src/main.cpp"
        src/Board.cpp src/Board.h
        src/SquareClass.cpp src/SquareClass.h
        src/Ply.cpp src/Ply.h
        src/Util.h
        src/Reversible.cpp src/Reversible.h
        src/Search.cpp src/Search.h
        src/Evaluation.cpp src/Evaluation.h )

add_executable(unittest src/unittest.cpp
        src/Board.cpp src/Board.h
        src/SquareClass.cpp src/SquareClass.h
        src/Ply.cpp src/Ply.h
        src/Search.cpp src/Search.h
        src/Reversible.cpp src/Reversible.h
        src/Evaluation.cpp src/Evaluation.h )



