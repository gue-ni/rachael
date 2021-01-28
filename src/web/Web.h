//
// Created by jakob on 1/27/21.
//

#ifndef CHESS_ENGINE_CPP_WEB_H
#define CHESS_ENGINE_CPP_WEB_H


class Web {
public:
    Web(std::string board);
    std::string generate_best_move();
    std::string generate_valid_moves(std::string square);
};


#endif //CHESS_ENGINE_CPP_WEB_H
