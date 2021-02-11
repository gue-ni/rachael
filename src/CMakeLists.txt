set(BINARY ${CMAKE_PROJECT_NAME})

#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

#set(SOURCES ${SOURCES})

set(SOURCES Board.cpp Board.h Evaluation.cpp Evaluation.h Move.cpp Move.h Reversible.cpp Reversible.h Search.cpp Search.h
        State.cpp State.h Util.cpp Util.h uci.cpp)

add_executable(${BINARY} ${SOURCES} Util.cpp State.cpp State.h)

add_library(${BINARY}_lib STATIC ${SOURCES}) # only needed for unittests
