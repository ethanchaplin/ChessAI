#include "SuperSickAI.h"
#include <climits>
#include <QDebug>
SuperSickAI::SuperSickAI()
{

}

SuperSickAI::~SuperSickAI()
{

}

std::vector<int> SuperSickAI::getBestMove(Board * b, Piece::Color color, int depth){


    std::vector<int> returnVec;
    int currPos;
    int bestPiecePos;
    int bestMove;

    int maxVal = INT_MIN;

    for(Piece* checkPiece : b->getPieces(color)){
    //test all possible first-ply moves and let negamax do the rest
        currPos = checkPiece->getCompositePosition();
        for(int move : checkPiece->getLegalMoves()){

        Board *checkBoard = new Board(false);

        //establish new phantom board
        for (Piece* piece : b->getPieces(static_cast<Piece::Color>(color))) {

         checkBoard -> setPiece(piece->getCompositePosition(), new Piece(piece));

        }

        for (Piece* piece : b->getPieces(static_cast<Piece::Color>(-color))) {

         checkBoard -> setPiece(piece->getCompositePosition(), new Piece(piece));

        }

        checkBoard->movePiece(checkBoard->getPiece(checkPiece->getCompositePosition()), move);
        checkBoard->computeAllPiecesLegalMove();

        //if checkmate!

        if(checkBoard->checkmate(checkPiece->getColor())){
            delete checkBoard;
            return {currPos, move};
        }

        int check = negamax(checkBoard, checkPiece->getColor(), depth-1);

        if(check > maxVal){
            maxVal = check;
            bestMove = move;
            bestPiecePos = currPos;
        }

        delete checkBoard;
        }




    }
    returnVec.push_back(bestPiecePos);
    returnVec.push_back(bestMove);

    return returnVec;


}


int SuperSickAI::negamax(Board *b, int color, int depth){

    if(depth == 0){
        return b->evaluate(static_cast<Piece::Color>(color)) * color;
    }

    if(b->checkmate(static_cast<Piece::Color>(color))){
        return (INT_MAX-5) * color;
    }

    int maxVal = INT_MIN;


    for(Piece* checkPiece : b->getPieces(static_cast<Piece::Color>(color))){

        for(int move : checkPiece->getLegalMoves()){

            Board *checkBoard = new Board(false);

            //establish new phantom board
            for (Piece* piece : b->getPieces(static_cast<Piece::Color>(color))) {

             checkBoard -> setPiece(piece->getCompositePosition(), new Piece(piece));

            }

            for (Piece* piece : b->getPieces(static_cast<Piece::Color>(-color))) {

             checkBoard -> setPiece(piece->getCompositePosition(), new Piece(piece));

            }
            checkBoard->movePiece(checkBoard->getPiece(checkPiece->getCompositePosition()), move);
            checkBoard->computeAllPiecesLegalMove();
            maxVal = std::max(maxVal, -negamax(checkBoard, -color, depth - 1));



        }



    }

    return maxVal;




}
