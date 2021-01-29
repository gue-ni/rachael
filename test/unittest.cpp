#include <iostream>
#include "../src/Board.h"
#include "../src/CachedBoard.h"

class A {
private:
    int a;

public:
    A(int a) : a(a) {}

    void foo(){
        std::cout << "foo" << std::endl;
    }

protected:
    void bar(){
        std::cout << "bar" << std::endl;
    }
};

class B : public A {
public:
    using A::A;
    void foobar(){
        foo();
        bar();
    }

};


int main(){
    Board board(DEFAULT_BOARD, true);
    std::cout << board << std::endl;







    /*
    std::vector<Ply> history = { Ply("e2e4"), Ply("e7e5")};

    int color = WHITE;

    for (auto p : history){
        std::vector<Ply> moves = board.generate_valid_moves_cached(-color);
        for (auto m : moves) std::cout << m << " ";
        std::cout << "\nmoves: " << moves.size() << std::endl;

        board.execute_reversible_move(p);
        board.update_cache();


        std::cout << board << std::endl;
        std::cout << "exectued move: " << p << std::endl << std::endl;
        break;
    }

    std::cout << "move_history: ";
    for (auto m : board.move_history) std::cout << m << " ";
    std::cout << std::endl;
     */
}
