/*
 * Board.cpp
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#include "Board.h"

#include <iostream>

#include <algorithm>

#include <QDebug>

#include <cmath>

Board::Board(bool real) {

    for (int i = 0; i < 64; i++) {
        pieceLocations[i] = nullptr;
    }

    this -> real = real;

    wInCheck = false;
    bInCheck = false;

}

void Board::setPiece(int pos, Piece * piece) {
    pieceLocations[pos] = piece;
}

Piece * Board::getPiece(int pos) {
    return pieceLocations[pos];
}

Piece ** Board::getPieces() {
    return pieceLocations;
}

Board::~Board() {
    for (int i = 0; i < 64; i++) {
        delete pieceLocations[i];

    }
}

void Board::computeAllPiecesLegalMove() {

    Piece * currPiece;
    std::vector < int > populateMoves;
    bCheckMoves.clear();
    wCheckMoves.clear();

    bCheckLines.clear();
    wCheckLines.clear();
    int knightMoves[8] = {
        6,
        15,
        17,
        10,
        -6,
        -15,
        -17,
        -10
    };

    int bishopMoves[] = {
        7,
        9,
        -7,
        -9
    };

    int rookMoves[] = {
        1,
        -1,
        8,
        -8
    };

    int queenMoves[] = {
        7,
        8,
        9,
        1,
        -1,
        -7,
        -8,
        -9
    };

    int kingMoves[] = {
        1,
        7,
        8,
        9,
        -1,
        -7,
        -8,
        -9
    };

    //non king move calculation
    for (int square = 0; square < 64; square++) {

        //if square contains piece

        if (pieceLocations[square] != nullptr) {

            currPiece = pieceLocations[square];

            //calculate all moves before king
            switch (currPiece -> getType()) {

            case (Piece::PAWN):

                if (currPiece -> getColor() == Piece::WHITE) {

                    //always establish that an empty square (or square with opposing color piece) is check for a king

                    //
                    if (currPiece -> getXPos() != 0 && currPiece -> getXPos() != 7) {
                        if (currPiece -> getYPos() != 0) {
                            if (!doesMoveCauseCheck(square, square - 7)) {
                                if (pieceLocations[square - 7] != nullptr) {

                                    if (pieceLocations[square - 7] -> getColor() != currPiece -> getColor()) {
                                        populateMoves.push_back(square - 7);
                                        if (pieceLocations[square - 7] -> getType() == Piece::KING) {
                                            //always allow piece in check to attack piece causing check
                                            bCheckLines.push_back(square);
                                        }
                                    }

                                }
                                addCheckMoves(currPiece -> getColor(), square - 7);
                            }
                            if (!doesMoveCauseCheck(square, square - 9)) {
                                if (pieceLocations[square - 9] != nullptr) {

                                    if (pieceLocations[square - 9] -> getColor() != currPiece -> getColor() && pieceLocations[square - 9] -> getYPos() == currPiece -> getYPos() - 1) {
                                        populateMoves.push_back(square - 9);

                                        if (pieceLocations[square - 9] -> getType() == Piece::KING) {
                                            //always allow piece in check to attack piece causing check
                                            bCheckLines.push_back(square);
                                        }

                                    }

                                }

                                addCheckMoves(currPiece -> getColor(), square - 9);
                            }
                        } else {
                            //TODO PROMOTE PROMPTING
                        }
                    } else {
                        if (currPiece -> getXPos() == 0) {
                            if (currPiece -> getYPos() != 0) {
                                if (!doesMoveCauseCheck(square, square - 7)) {
                                    if (pieceLocations[square - 7] != nullptr) {

                                        if (pieceLocations[square - 7] -> getColor() != currPiece -> getColor() && pieceLocations[square - 7] -> getYPos() == currPiece -> getYPos() - 1) {

                                            if (pieceLocations[square - 7] -> getType() == Piece::KING) {
                                                //always allow piece in check to attack piece causing check
                                                bCheckLines.push_back(square);
                                            }

                                            populateMoves.push_back(square - 7);
                                        }

                                    }
                                    addCheckMoves(currPiece -> getColor(), square - 7);
                                }
                            } else {
                                //TODO PROMOTIONS
                            }
                        } else if (currPiece -> getXPos() == 7) {
                            if (currPiece -> getYPos() != 0) {
                                if (!doesMoveCauseCheck(square, square - 9)) {
                                    if (pieceLocations[square - 9] != nullptr) {

                                        if (pieceLocations[square - 9] -> getColor() != currPiece -> getColor() && pieceLocations[square - 9] -> getYPos() == currPiece -> getYPos() - 1) {

                                            if (pieceLocations[square - 9] -> getType() == Piece::KING) {
                                                //always allow piece in check to attack piece causing check
                                                bCheckLines.push_back(square);
                                            }

                                            populateMoves.push_back(square - 9);
                                        }

                                    }
                                    addCheckMoves(currPiece -> getColor(), square - 9);
                                }
                            } else {
                                //TODO PROMOTIONS
                            }
                        }
                    }
                    //check for en passant
                    if (!doesMoveCauseCheck(square, square - 9)) {
                        if (currPiece -> getYPos() == 3 && pieceLocations[square - 1] != nullptr) {
                            if (pieceLocations[square - 1] -> getColor() != currPiece -> getColor() && pieceLocations[square - 1] -> getPreviousPos() == 64 && pieceLocations[square - 1] -> getXPos() == currPiece -> getXPos()) {
                                populateMoves.push_back(square - 9);
                            }
                        }
                    }
                    if (!doesMoveCauseCheck(square, square - 7)) {
                        if (currPiece -> getYPos() == 3 && pieceLocations[square + 1] != nullptr) {
                            if (pieceLocations[square + 1] -> getColor() != currPiece -> getColor() && pieceLocations[square + 1] -> getPreviousPos() == 64 && pieceLocations[square + 1] -> getXPos() == currPiece -> getXPos()) {
                                populateMoves.push_back(square - 7);
                            }
                        }
                    }

                    //try moving one
                    if (!doesMoveCauseCheck(square, square - 8)) {
                        if (currPiece -> getYPos() != 0) {
                            if (pieceLocations[square - 8] == nullptr && (square - 8 >= 0 && square - 8 <= 63)) {

                                populateMoves.push_back(square - 8);
                                //try moving two!!
                                if (!doesMoveCauseCheck(square, square - 16)) {
                                    if (pieceLocations[square - 16] == nullptr && !currPiece -> hasPreviouslyMoved()) {
                                        populateMoves.push_back(square - 16);
                                    }
                                }

                            }

                        }

                    } else {
                        //TODO MORE PROMOTION CHECKING
                    }
                } else if (currPiece -> getColor() == Piece::BLACK) {

                    //always establish that an empty square (or square with opposing color piece) is check for a king

                    //
                    if (currPiece -> getXPos() != 0 && currPiece -> getXPos() != 7) {
                        if (currPiece -> getYPos() != 7) {
                            if (!doesMoveCauseCheck(square, square + 7)) {
                                if (pieceLocations[square + 7] != nullptr) {

                                    if (pieceLocations[square + 7] -> getColor() != currPiece -> getColor()) {
                                        populateMoves.push_back(square + 7);

                                        if (pieceLocations[square + 7] -> getType() == Piece::KING) {
                                            //always allow piece in check to attack piece causing check
                                            wCheckLines.push_back(square);
                                        }
                                    }

                                }
                                addCheckMoves(currPiece -> getColor(), square + 7);
                            }
                            if (!doesMoveCauseCheck(square, square + 9)) {
                                if (pieceLocations[square + 9] != nullptr) {

                                    if (pieceLocations[square + 9] -> getColor() != currPiece -> getColor() && pieceLocations[square + 9] -> getYPos() == currPiece -> getYPos() + 1) {
                                        populateMoves.push_back(square + 9);

                                        if (pieceLocations[square + 9] -> getType() == Piece::KING) {
                                            //always allow piece in check to attack piece causing check
                                            wCheckLines.push_back(square);
                                        }

                                    }

                                }

                                addCheckMoves(currPiece -> getColor(), square + 9);
                            }
                        } else {
                            //TODO PROMOTE PROMPTING
                        }
                    } else {
                        if (currPiece -> getXPos() == 0) {
                            if (currPiece -> getYPos() != 7) {
                                if (!doesMoveCauseCheck(square, square + 9)) {
                                    if (pieceLocations[square + 9] != nullptr) {

                                        if (pieceLocations[square + 9] -> getColor() != currPiece -> getColor() && pieceLocations[square + 9] -> getYPos() == currPiece -> getYPos() + 1) {

                                            if (pieceLocations[square + 9] -> getType() == Piece::KING) {
                                                //always allow piece in check to attack piece causing check
                                                wCheckLines.push_back(square);
                                            }

                                            populateMoves.push_back(square + 9);
                                        }

                                    }
                                    addCheckMoves(currPiece -> getColor(), square + 9);
                                }
                            } else {
                                //TODO PROMOTIONS
                            }
                        } else if (currPiece -> getXPos() == 7) {
                            if (currPiece -> getYPos() != 7) {
                                if (!doesMoveCauseCheck(square, square + 7)) {
                                    if (pieceLocations[square + 7] != nullptr) {

                                        if (pieceLocations[square + 7] -> getColor() != currPiece -> getColor() && pieceLocations[square + 7] -> getYPos() == currPiece -> getYPos() - 1) {

                                            if (pieceLocations[square + 7] -> getType() == Piece::KING) {
                                                //always allow piece in check to attack piece causing check
                                                bCheckLines.push_back(square);
                                            }

                                            populateMoves.push_back(square + 7);
                                        }

                                    }
                                    addCheckMoves(currPiece -> getColor(), square + 7);
                                }
                            } else {
                                //TODO PROMOTIONS
                            }
                        }
                    }
                    //check for en passant
                    if (!doesMoveCauseCheck(square, square + 7)) {
                        if (currPiece -> getYPos() == 4 && pieceLocations[square - 1] != nullptr) {
                            if (pieceLocations[square - 1] -> getColor() != currPiece -> getColor() && pieceLocations[square - 1] -> getPreviousPos() == 64 && pieceLocations[square - 1] -> getXPos() == currPiece -> getXPos()) {
                                populateMoves.push_back(square + 7);
                            }
                        }
                    }
                    if (!doesMoveCauseCheck(square, square + 9)) {
                        if (currPiece -> getYPos() == 4 && pieceLocations[square + 1] != nullptr) {
                            if (pieceLocations[square + 1] -> getColor() != currPiece -> getColor() && pieceLocations[square + 1] -> getPreviousPos() == 64 && pieceLocations[square + 1] -> getXPos() == currPiece -> getXPos()) {
                                populateMoves.push_back(square + 9);
                            }
                        }
                    }

                    //try moving one
                    if (!doesMoveCauseCheck(square, square + 8)) {
                        if (currPiece -> getYPos() != 7) {
                            if (pieceLocations[square + 8] == nullptr && (square + 8 >= 0 && square + 8 <= 63)) {

                                populateMoves.push_back(square + 8);
                                //try moving two!!
                                if (!doesMoveCauseCheck(square, square + 16)) {
                                    if (pieceLocations[square + 16] == nullptr && !currPiece -> hasPreviouslyMoved()) {
                                        populateMoves.push_back(square + 16);
                                    }
                                }

                            }

                        }

                    } else {
                        //TODO MORE PROMOTION CHECKING
                    }
                }

                break;
            case (Piece::KNIGHT):

                for (int i = 0; i < 8; i++) {
                    int checkMove = knightMoves[i] + square;

                    //if valid move, not out of bounds!
                    if (abs((checkMove % 8) - currPiece -> getXPos()) <= 2 && (checkMove >= 0 && checkMove <= 63)) {
                        //if move doesn't cause check
                        if (!doesMoveCauseCheck(square, checkMove)) {

                            if (pieceLocations[checkMove] != nullptr) {
                                if (pieceLocations[checkMove] -> getColor() != currPiece -> getColor()) {
                                    populateMoves.push_back(checkMove);
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    if (pieceLocations[checkMove] -> getType() == Piece::KING) {

                                        if (currPiece -> getColor() == Piece::WHITE) {
                                            bCheckLines.push_back(checkMove);
                                        } else {
                                            wCheckLines.push_back(checkMove);
                                        }

                                    }
                                }
                            } else {
                                addCheckMoves(currPiece -> getColor(), checkMove);
                                populateMoves.push_back(checkMove);
                            }
                        }
                    }
                }

                break;
            case (Piece::BISHOP):

                for (int i = 0; i < 4; i++) {

                    int currentDiag = bishopMoves[i];

                    //jump through every square possible in diagonal
                    for (int j = 1; j < 8; j++) {

                        int checkMove = currentDiag * j + square;

                        //check if valid move
                        if (checkMove <= 63 && checkMove >= 0) {
                            if(abs(checkMove % 8 - currPiece->getXPos()) == 1){
                            if ((
                                    (currPiece -> getXPos() == 0 && (i == 0 || i == 3)) || (currPiece -> getXPos() == 7 && (i == 1 || i == 2))) ||
                                ((currPiece -> getYPos() == 0 && (i == 2 || i == 3)) || (currPiece -> getYPos() == 7 && (i == 0 || i == 1)))

                            ) {
                                break;
                            }
                            if (pieceLocations[checkMove] == nullptr) {
                                if (!doesMoveCauseCheck(square, checkMove)) {

                                    if (checkMove % 8 == 0 || checkMove % 8 == 7) {
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                        break;
                                    } else {
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                    }

                                }
                            } else {
                                if (!doesMoveCauseCheck(square, checkMove)) {

                                    if (currPiece -> getColor() != pieceLocations[checkMove] -> getColor()) {

                                        if (pieceLocations[checkMove] -> getType() == Piece::KING) {

                                            //cycle back to the bishop
                                            for (int recur = j; recur > -1; recur--) {
                                                addCheckLines(currPiece -> getColor(), currentDiag * recur + square);
                                            }

                                        }
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                        break;

                                    }
                                    if (currPiece -> getColor() == pieceLocations[checkMove] -> getColor()) {
                                        populateMoves.erase(std::remove(populateMoves.begin(), populateMoves.end(), checkMove), populateMoves.end());
                                        break;
                                    }
                                }
                            }

                        }
                        }
                    }

                }

                break;
            case (Piece::ROOK):
                for (int i = 0; i < 4; i++) {

                    int currentFile = rookMoves[i];

                    //jump through every square possible in diagonal
                    for (int j = 1; j < 9; j++) {

                        int checkMove = currentFile * j + square;

                        //check if valid move
                        if (checkMove <= 63 && checkMove >= 0) {

                            if ((
                                    (currPiece -> getXPos() == 0 && (i == 1)) || (currPiece -> getXPos() == 7 && (i == 0))) ||
                                ((currPiece -> getYPos() == 0 && (i == 3)) || (currPiece -> getYPos() == 7 && (i == 2)))

                            ) {
                                break;
                            }

                            if (pieceLocations[checkMove] == nullptr) {
                                if (!doesMoveCauseCheck(square, checkMove)) {
                                    if ((checkMove % 8 == 0 && currPiece -> getXPos() != 0) || (checkMove % 8 == 7 && currPiece -> getXPos() != 7)) {
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                        break;
                                    } else {
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                    }

                                }
                            } else {

                                if (currPiece -> getColor() != pieceLocations[checkMove] -> getColor()) {
                                    if (!doesMoveCauseCheck(square, checkMove)) {
                                        if (pieceLocations[checkMove] -> getType() == Piece::KING) {

                                            //cycle back to the bishop
                                            for (int recur = j; recur > -1; recur--) {
                                                addCheckLines(currPiece -> getColor(), currentFile * recur + square);
                                            }

                                        }

                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                        break;

                                    }
                                }

                                if (currPiece -> getColor() == pieceLocations[checkMove] -> getColor()) {
                                    populateMoves.erase(std::remove(populateMoves.begin(), populateMoves.end(), checkMove), populateMoves.end());
                                    break;

                                }

                            }

                        }

                    }

                }

                break;
            case (Piece::QUEEN):
                for (int i = 0; i < 8; i++) {

                    int currentFile = queenMoves[i];

                    //jump through every square possible in diagonal
                    for (int j = 1; j < 9; j++) {

                        int checkMove = currentFile * j + square;

                        //check if valid move
                        if (checkMove <= 63 && checkMove >= 0) {

                            if ((
                                    (currPiece -> getXPos() == 0 && (i == 0 || i == 4 || i == 7)) || (currPiece -> getXPos() == 7 && (i == 2 || i == 3 || i == 5))) ||
                                ((currPiece -> getYPos() == 0 && (i == 5 || i == 6 || i == 7)) || (currPiece -> getYPos() == 7 && (i == 0 || i == 1 || i == 2)))

                            ) {
                                break;
                            }
                            if (pieceLocations[checkMove] == nullptr) {
                                if (!doesMoveCauseCheck(square, checkMove)) {
                                    if ((checkMove % 8 == 0 && currPiece -> getXPos() != 0) || (checkMove % 8 == 7 && currPiece -> getXPos() != 7)) {
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                        break;
                                    } else {
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                    }

                                }
                            } else {

                                if (currPiece -> getColor() != pieceLocations[checkMove] -> getColor()) {
                                    if (!doesMoveCauseCheck(square, checkMove)) {
                                        if (pieceLocations[checkMove] -> getType() == Piece::KING) {

                                            //cycle back to the bishop
                                            for (int recur = j; recur > -1; recur--) {
                                                addCheckLines(currPiece -> getColor(), currentFile * recur + square);
                                            }

                                        }
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                        populateMoves.push_back(checkMove);
                                        break;

                                    }
                                }

                                if (currPiece -> getColor() == pieceLocations[checkMove] -> getColor()) {
                                    populateMoves.erase(std::remove(populateMoves.begin(), populateMoves.end(), checkMove), populateMoves.end());
                                    break;
                                }

                            }

                        }

                    }

                }

                break;

            }
            currPiece -> populateLegalMoves(populateMoves);
            populateMoves.clear();

        }

    }

    //king time!
    for (int square = 0; square < 64; square++) {

        //if square contains piece

        if (pieceLocations[square] != nullptr) {

            currPiece = pieceLocations[square];

            if (currPiece -> getType() == Piece::KING) {
                std::vector checkLines = getCheckLines(currPiece -> getColor());
                std::vector checkMoves = getCheckMoves(currPiece -> getColor());

                for (int i = 0; i < 8; i++) {
                    int checkMove = square + kingMoves[i];
                    if (checkMove >= 0 && checkMove <= 63) {
                        //if in check
                        if (find(checkMoves, square) || find(checkLines, square)) {

                            //try to move
                            if (!find(checkMoves, checkMove) && !find(checkLines, checkMove) && !doesMoveCauseCheck(square, checkMove)) {
                                if (pieceLocations[checkMove] != nullptr) {
                                    if (pieceLocations[checkMove] -> getColor() != currPiece -> getColor()) {
                                        populateMoves.push_back(checkMove);
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                    }

                                    //delete all moves that don't protect king
                                    for (int checkDel = 0; checkDel < 64; checkDel++) {

                                        if (pieceLocations[checkDel] != nullptr) {
                                            std::vector < int > tempCheckDelPiece = pieceLocations[checkDel] -> getLegalMoves();
                                            if (pieceLocations[checkDel] -> getColor() == currPiece -> getColor()) {

                                                for (int startDel = 0; startDel < (int) tempCheckDelPiece.size(); startDel++) {
                                                    int deletionMove = tempCheckDelPiece[startDel];

                                                    if (!find(checkLines, deletionMove)) {
                                                        removeMove(tempCheckDelPiece, deletionMove);
                                                        removeMove(checkMoves, deletionMove);
                                                        removeMove(checkLines, deletionMove);
                                                    }

                                                }

                                            }
                                        }

                                    }
                                } else {
                                    populateMoves.push_back(checkMove);
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                }
                            } else {
                                removeMove(populateMoves, checkMove);
                            }
                        }
                        //normal move scenario
                        else {
                            //if move doesn't put king in check
                            if (!find(checkMoves, checkMove) && !find(checkLines, checkMove) && !doesMoveCauseCheck(square, checkMove)) {
                                //check for castle!
                                if(!currPiece->hasPreviouslyMoved()){
                                for (int castleCheck = 2; castleCheck < 4; castleCheck++) {

                                    if (square + castleCheck == 63) {
                                        if (pieceLocations[62] == nullptr && pieceLocations[61] == nullptr && pieceLocations[63] != nullptr) {
                                            if (pieceLocations[63] -> getType() == Piece::ROOK && pieceLocations[63] -> getColor() == currPiece -> getColor() && !pieceLocations[63] -> hasPreviouslyMoved()) {
                                                populateMoves.push_back(62);
                                            }
                                        }
                                    }
                                    if (square + castleCheck == 7) {
                                        if (pieceLocations[6] == nullptr && pieceLocations[5] == nullptr && pieceLocations[4] == nullptr && pieceLocations[3] != nullptr) {
                                            if (pieceLocations[7] -> getType() == Piece::ROOK && pieceLocations[7] -> getColor() == currPiece -> getColor() && !pieceLocations[7] -> hasPreviouslyMoved()) {
                                                populateMoves.push_back(5);
                                            }
                                        }
                                    }
                                    if (square - castleCheck == 0) {
                                        if (pieceLocations[2] == nullptr && pieceLocations[1] == nullptr && pieceLocations[0] != nullptr) {
                                            if (pieceLocations[0] -> getType() == Piece::ROOK && pieceLocations[0] -> getColor() == currPiece -> getColor() && !pieceLocations[0] -> hasPreviouslyMoved()) {
                                                populateMoves.push_back(1);
                                            }
                                        }
                                    }
                                    if (square - castleCheck == 56) {
                                        if (pieceLocations[57] == nullptr && pieceLocations[58] == nullptr && pieceLocations[59] == nullptr && pieceLocations[56] != nullptr) {
                                            if (pieceLocations[56] -> getType() == Piece::ROOK && pieceLocations[56] -> getColor() == currPiece -> getColor() && !pieceLocations[56] -> hasPreviouslyMoved()) {
                                                populateMoves.push_back(58);
                                            }
                                        }
                                    }

                                }
                                }

                                if (pieceLocations[checkMove] != nullptr) {
                                    if (pieceLocations[checkMove] -> getColor() != currPiece -> getColor()) {

                                        populateMoves.push_back(checkMove);
                                        addCheckMoves(currPiece -> getColor(), checkMove);

                                    }
                                } else {

                                    populateMoves.push_back(checkMove);
                                    addCheckMoves(currPiece -> getColor(), checkMove);

                                }
                            } else {
                                removeMove(populateMoves, checkMove);
                            }
                        }
                    }
                }
                currPiece -> populateLegalMoves(populateMoves);
                populateMoves.clear();
            }
        }

    }

}

void Board::computeAllMoves() {

    Piece * currPiece;
    std::vector < int > populateMoves;
    bCheckMoves.clear();
    wCheckMoves.clear();

    bCheckLines.clear();
    wCheckLines.clear();
    int knightMoves[8] = {
        6,
        15,
        17,
        10,
        -6,
        -15,
        -17,
        -10
    };

    int bishopMoves[] = {
        7,
        9,
        -7,
        -9
    };

    int rookMoves[] = {
        1,
        -1,
        8,
        -8
    };

    int queenMoves[] = {
        7,
        8,
        9,
        1,
        -1,
        -7,
        -8,
        -9
    };

    int kingMoves[] = {
        1,
        7,
        8,
        9,
        -1,
        -7,
        -8,
        -9
    };

    //non king move calculation
    for (int square = 0; square < 64; square++) {

        //if square contains piece

        if (pieceLocations[square] != nullptr) {

            currPiece = pieceLocations[square];

            //calculate all moves before king
            switch (currPiece -> getType()) {

            case (Piece::PAWN):

                if (currPiece -> getColor() == Piece::WHITE) {

                    //always establish that an empty square (or square with opposing color piece) is check for a king

                    //
                    if (currPiece -> getXPos() != 0 && currPiece -> getXPos() != 7) {
                        if (currPiece -> getYPos() != 0) {
                            if (pieceLocations[square - 7] != nullptr) {

                                if (pieceLocations[square - 7] -> getColor() != currPiece -> getColor()) {
                                    if (pieceLocations[square - 7] -> getType() == Piece::KING) {
                                        //always allow piece in check to attack piece causing check
                                        bCheckLines.push_back(square);
                                    }
                                    populateMoves.push_back(square - 7);
                                }

                            }
                            addCheckMoves(currPiece -> getColor(), square - 7);

                            if (pieceLocations[square - 9] != nullptr) {

                                if (pieceLocations[square - 9] -> getColor() != currPiece -> getColor() && pieceLocations[square - 9] -> getYPos() == currPiece -> getYPos() - 1) {
                                    populateMoves.push_back(square - 9);

                                    if (pieceLocations[square - 9] -> getType() == Piece::KING) {
                                        //always allow piece in check to attack piece causing check
                                        bCheckLines.push_back(square);
                                    }

                                }

                            }

                            addCheckMoves(currPiece -> getColor(), square - 9);

                        } else {
                            //TODO PROMOTE PROMPTING
                        }
                    } else {
                        if (currPiece -> getXPos() == 0) {
                            if (currPiece -> getYPos() != 0) {
                                if (pieceLocations[square - 7] != nullptr) {

                                    if (pieceLocations[square - 7] -> getColor() != currPiece -> getColor() && pieceLocations[square - 7] -> getYPos() == currPiece -> getYPos() - 1) {

                                        if (pieceLocations[square - 7] -> getType() == Piece::KING) {
                                            //always allow piece in check to attack piece causing check
                                            bCheckLines.push_back(square);
                                        }

                                        populateMoves.push_back(square - 7);
                                    }

                                }
                                addCheckMoves(currPiece -> getColor(), square - 7);

                            } else {
                                //TODO PROMOTIONS
                            }
                        } else if (currPiece -> getXPos() == 7) {
                            if (currPiece -> getYPos() != 0) {
                                if (pieceLocations[square - 9] != nullptr) {

                                    if (pieceLocations[square - 9] -> getColor() != currPiece -> getColor() && pieceLocations[square - 9] -> getYPos() == currPiece -> getYPos() - 1) {

                                        if (pieceLocations[square - 9] -> getType() == Piece::KING) {
                                            //always allow piece in check to attack piece causing check
                                            bCheckLines.push_back(square);
                                        }

                                        populateMoves.push_back(square - 9);
                                    }

                                }
                                addCheckMoves(currPiece -> getColor(), square - 9);

                            } else {
                                //TODO PROMOTIONS
                            }
                        }
                    }
                    //check for en passant
                    if (currPiece -> getYPos() == 3 && pieceLocations[square - 1] != nullptr) {
                        if (pieceLocations[square - 1] -> getColor() != currPiece -> getColor() && pieceLocations[square - 1] -> getPreviousPos() == 64 && pieceLocations[square - 1] -> getXPos() == currPiece -> getXPos()) {
                            populateMoves.push_back(square - 9);
                        }
                    }

                    if (currPiece -> getYPos() == 3 && pieceLocations[square + 1] != nullptr) {
                        if (pieceLocations[square + 1] -> getColor() != currPiece -> getColor() && pieceLocations[square + 1] -> getPreviousPos() == 64 && pieceLocations[square + 1] -> getXPos() == currPiece -> getXPos()) {
                            populateMoves.push_back(square - 7);
                        }
                    }

                    //try moving one
                    if (currPiece -> getYPos() != 0) {
                        if (pieceLocations[square - 8] == nullptr && (square - 8 >= 0 && square - 8 <= 63)) {

                            populateMoves.push_back(square - 8);
                            //try moving two!!
                            if (pieceLocations[square - 16] == nullptr && !currPiece -> hasPreviouslyMoved()) {
                                populateMoves.push_back(square - 16);
                            }

                        }

                    } else {
                        //TODO MORE PROMOTION CHECKING
                    }
                } else if (currPiece -> getColor() == Piece::BLACK) {

                    //always establish that an empty square (or square with opposing color piece) is check for a king

                    //
                    if (currPiece -> getXPos() != 0 && currPiece -> getXPos() != 7) {
                        if (currPiece -> getYPos() != 7) {
                            if (pieceLocations[square + 7] != nullptr) {

                                if (pieceLocations[square + 7] -> getColor() != currPiece -> getColor()) {
                                    populateMoves.push_back(square + 7);

                                    if (pieceLocations[square + 7] -> getType() == Piece::KING) {
                                        //always allow piece in check to attack piece causing check
                                        wCheckLines.push_back(square);
                                    }
                                }

                            }
                            addCheckMoves(currPiece -> getColor(), square + 7);

                            if (pieceLocations[square + 9] != nullptr) {

                                if (pieceLocations[square + 9] -> getColor() != currPiece -> getColor() && pieceLocations[square + 9] -> getYPos() == currPiece -> getYPos() + 1) {
                                    populateMoves.push_back(square + 9);

                                    if (pieceLocations[square + 9] -> getType() == Piece::KING) {
                                        //always allow piece in check to attack piece causing check
                                        wCheckLines.push_back(square);
                                    }

                                }

                            }

                            addCheckMoves(currPiece -> getColor(), square + 9);

                        } else {
                            //TODO PROMOTE PROMPTING
                        }
                    } else {
                        if (currPiece -> getXPos() == 0) {
                            if (currPiece -> getYPos() != 7) {
                                if (pieceLocations[square + 9] != nullptr) {

                                    if (pieceLocations[square + 9] -> getColor() != currPiece -> getColor() && pieceLocations[square + 9] -> getYPos() == currPiece -> getYPos() + 1) {

                                        if (pieceLocations[square + 9] -> getType() == Piece::KING) {
                                            //always allow piece in check to attack piece causing check
                                            wCheckLines.push_back(square);
                                        }

                                        populateMoves.push_back(square + 9);
                                    }

                                }
                                addCheckMoves(currPiece -> getColor(), square + 9);

                            } else {
                                //TODO PROMOTIONS
                            }
                        } else if (currPiece -> getXPos() == 7) {
                            if (currPiece -> getYPos() != 7) {
                                if (pieceLocations[square + 7] != nullptr) {

                                    if (pieceLocations[square + 7] -> getColor() != currPiece -> getColor() && pieceLocations[square + 7] -> getYPos() == currPiece -> getYPos() - 1) {

                                        if (pieceLocations[square + 7] -> getType() == Piece::KING) {
                                            //always allow piece in check to attack piece causing check
                                            bCheckLines.push_back(square);
                                        }

                                        populateMoves.push_back(square + 7);
                                    }

                                }
                                addCheckMoves(currPiece -> getColor(), square + 7);

                            } else {
                                //TODO PROMOTIONS
                            }
                        }
                    }
                    //check for en passant
                    if (currPiece -> getYPos() == 4 && pieceLocations[square - 1] != nullptr) {
                        if (pieceLocations[square - 1] -> getColor() != currPiece -> getColor() && pieceLocations[square - 1] -> getPreviousPos() == 64 && pieceLocations[square - 1] -> getXPos() == currPiece -> getXPos()) {
                            populateMoves.push_back(square + 7);
                        }
                    }

                    if (currPiece -> getYPos() == 4 && pieceLocations[square + 1] != nullptr) {
                        if (pieceLocations[square + 1] -> getColor() != currPiece -> getColor() && pieceLocations[square + 1] -> getPreviousPos() == 64 && pieceLocations[square + 1] -> getXPos() == currPiece -> getXPos()) {
                            populateMoves.push_back(square + 9);
                        }
                    }

                    //try moving one
                    if (currPiece -> getYPos() != 7) {
                        if (pieceLocations[square + 8] == nullptr && (square + 8 >= 0 && square + 8 <= 63)) {

                            populateMoves.push_back(square + 8);
                            //try moving two!!
                            if (pieceLocations[square + 16] == nullptr && !currPiece -> hasPreviouslyMoved()) {
                                populateMoves.push_back(square + 16);
                            }

                        }

                    } else {
                        //TODO MORE PROMOTION CHECKING
                    }
                }
                break;
            case (Piece::KNIGHT):

                for (int i = 0; i < 8; i++) {
                    int checkMove = knightMoves[i] + square;

                    //if valid move, not out of bounds!
                    if (abs((checkMove % 8) - currPiece -> getXPos()) <= 2 && (checkMove >= 0 && checkMove <= 63)) {
                        //if move doesn't cause check

                        if (pieceLocations[checkMove] != nullptr) {
                            if (pieceLocations[checkMove] -> getColor() != currPiece -> getColor()) {
                                populateMoves.push_back(checkMove);
                                addCheckMoves(currPiece -> getColor(), checkMove);
                                if (pieceLocations[checkMove] -> getType() == Piece::KING) {

                                    if (currPiece -> getColor() == Piece::WHITE) {
                                        bCheckLines.push_back(checkMove);
                                    } else {
                                        wCheckLines.push_back(checkMove);
                                    }

                                }
                            }
                        } else {
                            addCheckMoves(currPiece -> getColor(), checkMove);
                            populateMoves.push_back(checkMove);
                        }

                    }
                }

                break;
            case (Piece::BISHOP):

                for (int i = 0; i < 4; i++) {

                    int currentDiag = bishopMoves[i];

                    //jump through every square possible in diagonal
                    for (int j = 1; j < 8; j++) {

                        int checkMove = currentDiag * j + square;

                        //check if valid move
                        if (checkMove <= 63 && checkMove >= 0) {
                            if(abs(checkMove % 8 - currPiece->getXPos()) == 1){

                            if ((
                                    (currPiece -> getXPos() == 0 && (i == 0 || i == 3)) || (currPiece -> getXPos() == 7 && (i == 1 || i == 2))) ||
                                ((currPiece -> getYPos() == 0 && (i == 2 || i == 3)) || (currPiece -> getYPos() == 7 && (i == 0 || i == 1)))
                            ) {
                                break;
                            }
                            if (pieceLocations[checkMove] == nullptr) {

                                if (checkMove % 8 == 0 || checkMove % 8 == 7) {
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                    break;
                                } else {
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                }

                            } else {

                                if (currPiece -> getColor() != pieceLocations[checkMove] -> getColor()) {

                                    if (pieceLocations[checkMove] -> getType() == Piece::KING) {

                                        //cycle back to the bishop
                                        for (int recur = j; recur > -1; recur--) {
                                            addCheckLines(currPiece -> getColor(), currentDiag * recur + square);
                                        }

                                    }
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                    break;

                                }
                                if (currPiece -> getColor() == pieceLocations[checkMove] -> getColor()) {
                                    removeMove(populateMoves, checkMove);
                                    break;
                                }

                            }

                        }
                        }
                    }

                }

                break;
            case (Piece::ROOK):
                for (int i = 0; i < 4; i++) {

                    int currentFile = rookMoves[i];

                    //jump through every square possible in diagonal
                    for (int j = 1; j < 9; j++) {

                        int checkMove = currentFile * j + square;

                        //check if valid move
                        if (checkMove <= 63 && checkMove >= 0) {

                            if ((
                                    (currPiece -> getXPos() == 0 && (i == 1)) || (currPiece -> getXPos() == 7 && (i == 0))) ||
                                ((currPiece -> getYPos() == 0 && (i == 3)) || (currPiece -> getYPos() == 7 && (i == 2)))

                            ) {
                                break;
                            }

                            if (pieceLocations[checkMove] == nullptr) {
                                if ((checkMove % 8 == 0 && currPiece -> getXPos() != 0) || (checkMove % 8 == 7 && currPiece -> getXPos() != 7)) {
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                    break;
                                } else {
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                }

                            } else {

                                if (currPiece -> getColor() != pieceLocations[checkMove] -> getColor()) {
                                    if (pieceLocations[checkMove] -> getType() == Piece::KING) {

                                        //cycle back to the bishop
                                        for (int recur = j; recur > -1; recur--) {
                                            addCheckLines(currPiece -> getColor(), currentFile * recur + square);
                                        }

                                    }

                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                    break;

                                }

                                if (currPiece -> getColor() == pieceLocations[checkMove] -> getColor()) {
                                    removeMove(populateMoves, checkMove);
                                    break;

                                }

                            }

                        }

                    }

                }

                break;
            case (Piece::QUEEN):
                for (int i = 0; i < 8; i++) {

                    int currentFile = queenMoves[i];

                    //jump through every square possible in diagonal
                    for (int j = 1; j < 9; j++) {

                        int checkMove = currentFile * j + square;

                        //check if valid move
                        if (checkMove <= 63 && checkMove >= 0) {

                            if ((
                                    (currPiece -> getXPos() == 0 && (i == 0 || i == 4 || i == 7)) || (currPiece -> getXPos() == 7 && (i == 2 || i == 3 || i == 5))) ||
                                ((currPiece -> getYPos() == 0 && (i == 5 || i == 6 || i == 7)) || (currPiece -> getYPos() == 7 && (i == 0 || i == 1 || i == 2)))

                            ) {
                                break;
                            }
                            if (pieceLocations[checkMove] == nullptr) {
                                if ((checkMove % 8 == 0 && currPiece -> getXPos() != 0) || (checkMove % 8 == 7 && currPiece -> getXPos() != 7)) {
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                    break;
                                } else {
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                }

                            } else {

                                if (currPiece -> getColor() != pieceLocations[checkMove] -> getColor()) {
                                    if (pieceLocations[checkMove] -> getType() == Piece::KING) {

                                        //cycle back to the bishop
                                        for (int recur = j; recur > -1; recur--) {
                                            addCheckLines(currPiece -> getColor(), currentFile * recur + square);
                                        }

                                    }
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                    populateMoves.push_back(checkMove);
                                    break;

                                }

                                if (currPiece -> getColor() == pieceLocations[checkMove] -> getColor()) {
                                    removeMove(populateMoves, checkMove);
                                    break;

                                }

                            }

                        }

                    }

                }

                break;

            }
            currPiece -> populateLegalMoves(populateMoves);
            populateMoves.clear();

        }

    }

    //king time!
    for (int square = 0; square < 64; square++) {

        //if square contains piece

        if (pieceLocations[square] != nullptr) {

            currPiece = pieceLocations[square];

            if (currPiece -> getType() == Piece::KING) {
                std::vector checkLines = getCheckLines(currPiece -> getColor());
                std::vector checkMoves = getCheckMoves(currPiece -> getColor());

                for (int i = 0; i < 8; i++) {
                    int checkMove = square + kingMoves[i];
                    if (checkMove >= 0 && checkMove <= 63) {
                        //if in check
                        if (find(checkMoves, square) || find(checkLines, square)) {

                            //try to move
                            if (!find(checkMoves, checkMove) && !find(checkLines, checkMove)) {
                                if (pieceLocations[checkMove] != nullptr) {
                                    if (pieceLocations[checkMove] -> getColor() != currPiece -> getColor()) {
                                        populateMoves.push_back(checkMove);
                                        addCheckMoves(currPiece -> getColor(), checkMove);
                                    }

                                    //delete all moves that don't protect king
                                    for (int checkDel = 0; checkDel < 64; checkDel++) {

                                        if (pieceLocations[checkDel] != nullptr) {
                                            std::vector < int > tempCheckDelPiece = pieceLocations[checkDel] -> getLegalMoves();
                                            if (pieceLocations[checkDel] -> getColor() == currPiece -> getColor()) {

                                                for (int startDel = 0; startDel < (int) tempCheckDelPiece.size(); startDel++) {
                                                    int deletionMove = tempCheckDelPiece[startDel];

                                                    if (!find(checkLines, deletionMove)) {
                                                        removeMove(tempCheckDelPiece, deletionMove);
                                                        removeMove(checkMoves, deletionMove);
                                                        removeMove(checkLines, deletionMove);
                                                    }

                                                }

                                            }
                                        }

                                    }
                                } else {
                                    populateMoves.push_back(checkMove);
                                    addCheckMoves(currPiece -> getColor(), checkMove);
                                }
                            } else {
                                removeMove(populateMoves, checkMove);
                            }
                        }
                        //normal move scenario
                        else {
                            //if move doesn't put king in check
                            if (!find(checkMoves, checkMove) && !find(checkLines, checkMove)) {
                                //check for castle!
                                if(!currPiece->hasPreviouslyMoved()){
                                for (int castleCheck = 2; castleCheck < 4; castleCheck++) {

                                    if (square + castleCheck == 63) {
                                        if (pieceLocations[62] == nullptr && pieceLocations[61] == nullptr && pieceLocations[63] != nullptr) {
                                            if (pieceLocations[63] -> getType() == Piece::ROOK && pieceLocations[63] -> getColor() == currPiece -> getColor() && !pieceLocations[63] -> hasPreviouslyMoved()) {
                                                populateMoves.push_back(62);
                                            }
                                        }
                                    }
                                    if (square + castleCheck == 7) {
                                        if (pieceLocations[6] == nullptr && pieceLocations[5] == nullptr && pieceLocations[4] == nullptr && pieceLocations[3] != nullptr) {
                                            if (pieceLocations[7] -> getType() == Piece::ROOK && pieceLocations[7] -> getColor() == currPiece -> getColor() && !pieceLocations[7] -> hasPreviouslyMoved()) {
                                                populateMoves.push_back(5);
                                            }
                                        }
                                    }
                                    if (square - castleCheck == 0) {
                                        if (pieceLocations[2] == nullptr && pieceLocations[1] == nullptr && pieceLocations[0] != nullptr) {
                                            if (pieceLocations[0] -> getType() == Piece::ROOK && pieceLocations[0] -> getColor() == currPiece -> getColor() && !pieceLocations[0] -> hasPreviouslyMoved()) {
                                                populateMoves.push_back(1);
                                            }
                                        }
                                    }
                                    if (square - castleCheck == 56) {
                                        if (pieceLocations[57] == nullptr && pieceLocations[58] == nullptr && pieceLocations[59] == nullptr && pieceLocations[56] != nullptr) {
                                            if (pieceLocations[56] -> getType() == Piece::ROOK && pieceLocations[56] -> getColor() == currPiece -> getColor() && !pieceLocations[56] -> hasPreviouslyMoved()) {
                                                populateMoves.push_back(58);
                                            }
                                        }
                                    }

                                }
}
                                if (pieceLocations[checkMove] != nullptr) {
                                    if (pieceLocations[checkMove] -> getColor() != currPiece -> getColor()) {

                                        populateMoves.push_back(checkMove);
                                        addCheckMoves(currPiece -> getColor(), checkMove);

                                    }
                                } else {

                                    populateMoves.push_back(checkMove);
                                    addCheckMoves(currPiece -> getColor(), checkMove);

                                }
                            } else {
                                removeMove(populateMoves, checkMove);
                            }
                        }
                    }
                }
                currPiece -> populateLegalMoves(populateMoves);
                populateMoves.clear();
            }
        }

    }

}

void Board::addCheckMoves(Piece::Color attackingPiece, int pos) {
    if (attackingPiece == Piece::WHITE) {
        bCheckMoves.push_back(pos);
    } else {
        wCheckMoves.push_back(pos);
    }
}

void Board::addCheckLines(Piece::Color attackingPiece, int pos) {
    if (attackingPiece == Piece::WHITE) {
        bCheckLines.push_back(pos);
    } else {
        wCheckLines.push_back(pos);
    }
}

void Board::movePiece(Piece * piece, int square) {

    int oldSquare = piece -> getCompositePosition();

    if (getPiece(square) != nullptr) {
        if (getPiece(square) -> getColor() != getPiece(oldSquare) -> getColor()) {
            attack(square);
            pieceLocations[square] = piece;
            piece -> move(square);
            pieceLocations[oldSquare] = nullptr;
        }

    } else {
        if (piece -> getType() == Piece::KING) {
            //white castle
            if (piece -> getColor() == Piece::WHITE) {
                if (oldSquare == 60) {
                    if (square == 62) {
                        pieceLocations[63] -> move(61);
                        pieceLocations[61] = pieceLocations[63];

                        pieceLocations[63] = nullptr;
                        piece -> move(square);
                        pieceLocations[square] = piece;
                        pieceLocations[60] = nullptr;
                    } else if (square == 58) {
                        pieceLocations[56] -> move(59);
                        pieceLocations[59] = pieceLocations[56];

                        pieceLocations[56] = nullptr;
                        piece -> move(square);
                        pieceLocations[square] = piece;
                        pieceLocations[60] = nullptr;
                    } else {
                        pieceLocations[square] = piece;
                        piece -> move(square);
                        pieceLocations[oldSquare] = nullptr;
                    }
                } else {
                    pieceLocations[square] = piece;
                    piece -> move(square);
                    pieceLocations[oldSquare] = nullptr;
                }
            }
            //black castle
            else {
                if (oldSquare == 4) {
                    if (square == 6) {
                        pieceLocations[7] -> move(5);
                        pieceLocations[5] = pieceLocations[7];

                        pieceLocations[7] = nullptr;
                        piece -> move(square);
                        pieceLocations[square] = piece;
                        pieceLocations[4] = nullptr;
                    } else if (square == 2) {
                        pieceLocations[0] -> move(3);
                        pieceLocations[3] = pieceLocations[0];

                        pieceLocations[0] = nullptr;
                        piece -> move(square);
                        pieceLocations[square] = piece;
                        pieceLocations[4] = nullptr;
                    } else {
                        pieceLocations[square] = piece;
                        piece -> move(square);
                        pieceLocations[oldSquare] = nullptr;
                    }
                } else {
                    pieceLocations[square] = piece;
                    piece -> move(square);
                    pieceLocations[oldSquare] = nullptr;
                }
            }

        } else if (piece -> getType() == Piece::PAWN) {
            if (piece -> getColor() == Piece::WHITE) {

                //first move double check
                if (square == (oldSquare - 16)) {
                    piece -> move(square);
                    piece -> setPreviousPosition(65);
                    pieceLocations[square] = piece;
                    attack(oldSquare);

                }
                //en passant check
                else if (abs(square - (oldSquare - 8)) == 1 && pieceLocations[square] == nullptr) {
                    attack(square + 8);
                    piece -> move(square);
                    pieceLocations[square] = piece;
                    attack(oldSquare);
                }
                //all other moves
                else {
                    pieceLocations[square] = piece;
                    piece -> move(square);
                    attack(oldSquare);
                }
            } else if (piece -> getColor() == Piece::BLACK) {

                //first move double check
                if (square == (oldSquare + 16)) {
                    piece -> move(square);
                    piece -> setPreviousPosition(65);
                    pieceLocations[square] = piece;
                    attack(oldSquare);

                }
                //en passant check
                else if (abs(square - (oldSquare + 8)) == 1 && pieceLocations[square] == nullptr) {
                    attack(square - 8);
                    piece -> move(square);
                    pieceLocations[square] = piece;
                    attack(oldSquare);
                }
                //all other moves
                else {
                    pieceLocations[square] = piece;
                    piece -> move(square);
                    attack(oldSquare);
                }
            }
        } else {
            pieceLocations[square] = piece;
            piece -> move(square);
            attack(oldSquare);
        }

    }
    if (this -> real) {
        qDebug() << boardInCheck(piece -> getColor());
    }
}

void Board::attack(int square) {
    pieceLocations[square] = nullptr;
}

void Board::changeTurn() {

    turn == T_WHITE ? turn = T_BLACK : turn = T_WHITE;

    for (int i = 0; i < 64; i++) {
        if (pieceLocations[i] != nullptr) {

            if (pieceLocations[i] -> getPreviousPos() == 65) {
                pieceLocations[i] -> setPreviousPosition(64);
            } else if (pieceLocations[i] -> getPreviousPos() == 64) {

                if (pieceLocations[i] -> getColor() == Piece::WHITE) {
                    pieceLocations[i] -> setPreviousPosition(i + 16);
                }
                if (pieceLocations[i] -> getColor() == Piece::BLACK) {
                    pieceLocations[i] -> setPreviousPosition(i - 16);
                }
            }

        }
    }

}

bool Board::doesMoveCauseCheck(int oldSquare, int newSquare) {

    Board * b = new Board(false);

    if (pieceLocations[oldSquare] != nullptr) {

        for (int i = 0; i < 64; i++) {
            if (pieceLocations[i] != nullptr)
                b -> setPiece(i, new Piece(pieceLocations[i]));

        }
        b -> movePiece(b -> pieceLocations[oldSquare], newSquare);

        bool inCheck = b -> boardInCheck(b -> getPiece(newSquare) -> getColor());
        delete b;

        return inCheck;
    }
    delete b;
    return false;

}

bool Board::boardInCheck(Piece::Color color) {

    computeAllMoves();

    for (int i = 0; i < 64; i++) {
        Piece * currPiece = pieceLocations[i];

        if (currPiece != nullptr) {

            if (currPiece -> getType() == Piece::KING) {

                if (currPiece -> getColor() == Piece::WHITE) {

                    //if in check
                    if (std::find(wCheckMoves.begin(), wCheckMoves.end(), i) != wCheckMoves.end()) {

                        if (color == currPiece -> getColor()) {
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        continue;
                    }

                } else {

                    if (std::find(bCheckMoves.begin(), bCheckMoves.end(), i) != bCheckMoves.end()) {

                        if (color == currPiece -> getColor()) {
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        continue;
                    }

                }
            } else {
                continue;
            }
        } else {
            continue;
        }
    }

    return false;
}

Board::Turn Board::getTurn() {
    return turn;
}

std::vector < int > Board::getCheckLines(Piece::Color color) {
    if (color == Piece::BLACK) {
        return bCheckLines;
    } else {
        return wCheckLines;
    }
}

std::vector < int > Board::getCheckMoves(Piece::Color color) {
    if (color == Piece::BLACK) {
        return bCheckMoves;
    } else {
        return wCheckMoves;
    }
}

bool Board::find(std::vector < int > vec, int square) {
    return std::find(vec.begin(), vec.end(), square) != vec.end();
}

void Board::removeMove(std::vector<int>& vec, int square){
    vec.erase(std::remove(vec.begin(), vec.end(), square), vec.end());
}
