#ifndef PLAYER_H
#define PLAYER_H


#include "Board.h"
class Player
{
public:

    enum PlayerTurn {PLAYER_1, PLAYER_2};
    enum PlayerType {HUMAN = 0, ROBOT = 1, SMOOTH_BRAIN = 2};
    Player(PlayerTurn turn, PlayerType type, Board * board);
    ~Player();
    PlayerTurn getTurn();
    PlayerType getType();
    Board * getBoard();
    std::vector<int> aiMove();
    std::vector<int> negaMove();
    bool isAlive();
private:

    PlayerTurn turn;
    PlayerType type;
    Board * board;
    bool alive;
};

#endif // PLAYER_H
