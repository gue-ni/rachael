
#include <iostream>
#include "../src/Board.h"

int main(){

    Board board(false);

    for (int i = 0; i < 128; i++){
        if (!board.off_the_board(i))
            printf("0x%02x, ", i);
    }

}
