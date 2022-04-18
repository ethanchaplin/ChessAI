#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include <cstdlib>
#include <QThread>
Player::Player(PlayerTurn turn, PlayerType type, Board * board)
{
    this->turn = turn;
    this->type = type;
    this->board = board;
}

Player::~Player(){
    delete board;
}

Player::PlayerTurn Player::getTurn(){
    return turn;
}
Player::PlayerType Player::getType(){
    return type;
}
Board * Player::getBoard(){
    return board;
}

std::vector<int> Player::aiMove(){


        std::vector<int> move;

        srand(time(NULL));
        std::vector<Piece*> getPieces;
        if(turn == PLAYER_1){
            getPieces = board->getWhitePieces();
        }
        else{
            getPieces = board->getBlackPieces();
        }
        int randomPiece = rand() % getPieces.size();

        while(getPieces.at(randomPiece)->getLegalMoves().size() == 0){
            randomPiece = rand() % getPieces.size();

        }

        int randomMove = rand() % (int)getPieces.at(randomPiece)->getLegalMoves().size();

        move.push_back(getPieces.at(randomPiece)->getCompositePosition());
        move.push_back(getPieces.at(randomPiece)->getLegalMoves().at(randomMove));
        return move;


    }










bool Player::isAlive(){
    return alive;
}

