#ifndef PLAYER_H
#define PLAYER_H


#include "Board.h"
class Player
{
public:

    enum PlayerTurn {PLAYER_1, PLAYER_2};
    enum PlayerType {HUMAN, ROBOT, SMOOTH_BRAIN};
    Player(PlayerTurn turn, PlayerType type, Board * board);
    ~Player();
    PlayerTurn getTurn();
    PlayerType getType();
    Board * getBoard();
    std::vector<int> aiMove();
    bool isAlive();
private:

    PlayerTurn turn;
    PlayerType type;
    Board * board;
    bool alive;
};

#endif // PLAYER_H
