#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include <cstdlib>
#include <QThread>
#include <thread>
#include "SuperSickAI.h"
using namespace std::chrono_literals;
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

        std::this_thread::sleep_for(100ms);
        std::vector<int> move;
        bool canMove = false;

        srand(time(NULL));
        std::vector<Piece*> getPieces;
        if(turn == PLAYER_1){
            getPieces = board->getWhitePieces();
        }
        else{
            getPieces = board->getBlackPieces();
        }

        for (int j  = 0; j < (int)getPieces.size(); j++){
            if(getPieces.at(j)->canMove()){
                canMove = true;
            }
        }

        if(canMove){

        int randomPiece = rand() % getPieces.size();

        while(getPieces.at(randomPiece)->getLegalMoves().size() == 0){
            randomPiece = rand() % getPieces.size();

        }

        int randomMove = rand() % (int)getPieces.at(randomPiece)->getLegalMoves().size();

        move.push_back(getPieces.at(randomPiece)->getCompositePosition());
        move.push_back(getPieces.at(randomPiece)->getLegalMoves().at(randomMove));
        }
        else{
            move.clear();
        }

        return move;


    }

std::vector<int> Player::negaMove(){
    SuperSickAI s;

    std::vector<int> bestMove = s.getBestMove(board, turn==Player::PLAYER_1 ? Piece::WHITE : Piece::BLACK, 2);
    return {bestMove.at(0), bestMove.at(1)};
}








bool Player::isAlive(){
    return alive;
}

