CC:=g++
SRC_DIR := ./src
OBJ_DIR := ./obj
#SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
#OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LFLAGS:=-O3 -Wall -pthread
CFLAGS:=-std=c++17 -O3 -g -Wall

RACHAEL_OBJ:= obj/uci.o obj/Board.o obj/Ply.o obj/Square.o obj/Search.o obj/Evaluation.o obj/Reversible.o
UNITTEST_OBJ:= obj/unittest.o obj/Board.o obj/Ply.o obj/Square.o obj/Search.o obj/Evaluation.o obj/Reversible.o


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

