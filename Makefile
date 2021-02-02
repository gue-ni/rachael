
SRC_DIR := ./src
OBJ_DIR := ./obj
#SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
#OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CC:=g++
FLAGS:=-O3 -Wall
LFLAGS:=$(FLAGS) -pthread
CFLAGS:=$(FLAGS) -g -std=c++17

RACHAEL_OBJ:= obj/uci.o obj/Board.o obj/Ply.o obj/Square.o obj/Search.o obj/Evaluation.o obj/Reversible.o obj/Util.o
UNITTEST_OBJ:= obj/unittest.o obj/Board.o obj/Ply.o obj/Square.o obj/Search.o obj/Evaluation.o obj/Reversible.o obj/Util.o


.PHONY: clean all

all: rachael unittest

rachael: $(RACHAEL_OBJ)
	$(CC) $(LFLAGS) -o $@ $^

unittest: $(UNITTEST_OBJ)
	$(CC) $(LFLAGS) -o $@ $^


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f $(OBJ_DIR)/*.o rachael unittest

