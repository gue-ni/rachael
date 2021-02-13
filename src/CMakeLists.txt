set(BINARY ${CMAKE_PROJECT_NAME})

#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

#set(SOURCES ${SOURCES})

set(SOURCES Board.cpp Board.h Evaluation.cpp Evaluation.h Move.cpp Move.h Search.cpp Search.h
        State.h Util.cpp Util.h)

add_executable(${BINARY} ${SOURCES} uci.cpp)
add_executable(unittest ${SOURCES} unittest.cpp)

add_library(${BINARY}_lib STATIC ${SOURCES}) # only needed for unittests
