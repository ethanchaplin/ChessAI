/*
 * Board.cpp
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#include "Board.h"

#include <iostream>

#include <algorithm>

Board::Board() {

    for (int i = 0; i < 64; i++) {
        pieceLocations[i] = nullptr;
    }

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

    for (int square = 0; square < 64; square++) {
        if (pieceLocations[square] != nullptr) {

            if (pieceLocations[square] -> getType() != Piece::KING) {
                currPiece = pieceLocations[square];

                switch (currPiece -> getType()) {

                case (Piece::PAWN):
                    if (currPiece -> getColor() == Piece::WHITE) {

                        if (square % 8 != 0) {
                            addCheckMoves(currPiece -> getColor(), square + 7);
                        }

                        if (square % 8 != 7) {
                            addCheckMoves(currPiece -> getColor(), square + 9);
                        }

                        //check if no one blocking pawn
                        if (pieceLocations[square + 8] == nullptr && square + 8 <= 63) {
                            //opening move pawn two squares
                            if (!currPiece -> hasPreviouslyMoved() && pieceLocations[square + 16] == nullptr) {
                                populateMoves.push_back(square + 16);
                            }
                            populateMoves.push_back(square + 8);
                        }

                        //check for attack
                        if (pieceLocations[square + 9] != nullptr && pieceLocations[square + 9] -> getColor() == Piece::BLACK) {
                            populateMoves.push_back(square + 9);

                        }
                        if (pieceLocations[square + 7] != nullptr && pieceLocations[square + 7] -> getColor() != Piece::BLACK) {
                            populateMoves.push_back(square + 7);

                        }

                        //TODO implement en passant

                    }

                    //BLACK PAWN
                    else {
                        if (square % 8 != 0) {
                            addCheckMoves(currPiece -> getColor(), square + 7);
                        }

                        if (square % 8 != 7) {
                            addCheckMoves(currPiece -> getColor(), square + 9);
                        }

                        if (pieceLocations[square - 8] == nullptr && square - 8 >= 0) {
                            //opening move pawn two squares
                            if (!currPiece -> hasPreviouslyMoved() && pieceLocations[square - 16] == nullptr) {
                                populateMoves.push_back(square - 16);
                            }
                            populateMoves.push_back(square - 8);
                        }

                        //check for attack
                        if (pieceLocations[square - 9] != nullptr && pieceLocations[square - 9] -> getColor() == Piece::BLACK) {
                            populateMoves.push_back(square - 9);
                        }
                        if (pieceLocations[square - 7] != nullptr && pieceLocations[square - 7] -> getColor() != Piece::BLACK) {
                            populateMoves.push_back(square - 7);
                        }

                        //TODO implement en passant

                    }
                    currPiece -> populateLegalMoves(populateMoves);
                    populateMoves.clear();
                    break;

                case (Piece::BISHOP):

                    for (int moves = 0; moves < 4; moves++) {
                        for (int diag = 1; diag < 8; diag++) {

                            int checkPos = square + (bishopMoves[moves] * diag);

                            if (checkPos >= 0 && checkPos <= 63) {

                                if (pieceLocations[checkPos] == nullptr) {
                                    populateMoves.push_back(checkPos);
                                    addCheckMoves(currPiece -> getColor(), checkPos);

                                } else {
                                    if (pieceLocations[checkPos] -> getColor() != currPiece -> getColor()) {
                                        populateMoves.push_back(checkPos);

                                        addCheckMoves(currPiece -> getColor(), checkPos);

                                        break;
                                    } else {
                                        break;
                                    }

                                }
                            }

                        }
                    }

                    currPiece -> populateLegalMoves(populateMoves);
                    populateMoves.clear();
                    break;
                case (Piece::KNIGHT):

                    for (int i = 0; i < 8; i++) {
                        int checkPos = knightMoves[i] + square;

                        if (checkPos >= 0 && checkPos <= 63) {

                            if (pieceLocations[checkPos] == nullptr) {
                                populateMoves.push_back(checkPos);
                                addCheckMoves(currPiece -> getColor(), checkPos);
                            } else {
                                if (pieceLocations[checkPos] -> getColor() != currPiece -> getColor()) {
                                    populateMoves.push_back(checkPos);

                                    addCheckMoves(currPiece -> getColor(), checkPos);

                                } else {
                                    continue;
                                }
                            }

                        }

                    }
                    currPiece -> populateLegalMoves(populateMoves);
                    populateMoves.clear();
                    break;
                case (Piece::ROOK):
                    //check vertical moves
                    for (int i = 0; i < 8; i++) {
                        int checkPos = 8 * i + square;

                        if (pieceLocations[checkPos] == nullptr) {
                            populateMoves.push_back(checkPos);
                            addCheckMoves(currPiece -> getColor(), checkPos);

                        } else {
                            if (pieceLocations[checkPos] -> getColor() != currPiece -> getColor()) {
                                populateMoves.push_back(checkPos);
                                addCheckMoves(currPiece -> getColor(), checkPos);

                                break;
                            } else {
                                break;
                            }
                        }

                    }
                    //check horizontal moves
                    for (int i = 0; i < 8; i++) {
                        int checkPos = 8 * i + square;

                        if (pieceLocations[checkPos] == nullptr) {
                            populateMoves.push_back(checkPos);
                            addCheckMoves(currPiece -> getColor(), checkPos);
                        } else {
                            if (pieceLocations[checkPos] -> getColor() != currPiece -> getColor()) {
                                populateMoves.push_back(checkPos);
                                addCheckMoves(currPiece -> getColor(), checkPos);
                                break;
                            } else {
                                break;
                            }

                        }

                    }
                    currPiece -> populateLegalMoves(populateMoves);
                    populateMoves.clear();
                    break;
                case (Piece::QUEEN):

                    for (int i = 0; i < 8; i++) {
                        int checkPos = 8 * i + square;

                        if (pieceLocations[checkPos] == nullptr) {
                            populateMoves.push_back(checkPos);
                            addCheckMoves(currPiece -> getColor(), checkPos);

                        } else {
                            if (pieceLocations[checkPos] -> getColor() != currPiece -> getColor()) {
                                populateMoves.push_back(checkPos);
                                addCheckMoves(currPiece -> getColor(), checkPos);

                                break;
                            } else {
                                break;
                            }
                        }

                    }
                    //check horizontal moves
                    for (int i = 0; i < 8; i++) {
                        int checkPos = 8 * i + square;

                        if (pieceLocations[checkPos] == nullptr) {
                            populateMoves.push_back(checkPos);
                            addCheckMoves(currPiece -> getColor(), checkPos);
                        } else {
                            if (pieceLocations[checkPos] -> getColor() != currPiece -> getColor()) {
                                populateMoves.push_back(checkPos);
                                addCheckMoves(currPiece -> getColor(), checkPos);
                                break;
                            } else {
                                break;
                            }

                        }

                    }

                    for (int moves = 0; moves < 4; moves++) {
                        for (int diag = 1; diag < 8; diag++) {

                            int checkPos = square + (bishopMoves[moves] * diag);

                            if (checkPos >= 0 && checkPos <= 63) {

                                if (pieceLocations[checkPos] == nullptr) {
                                    populateMoves.push_back(checkPos);
                                    addCheckMoves(currPiece -> getColor(), checkPos);

                                } else {
                                    if (pieceLocations[checkPos] -> getColor() != currPiece -> getColor()) {
                                        populateMoves.push_back(checkPos);

                                        addCheckMoves(currPiece -> getColor(), checkPos);

                                        break;
                                    } else {
                                        break;
                                    }

                                }
                            }

                        }
                    }

                    currPiece -> populateLegalMoves(populateMoves);
                    populateMoves.clear();
                    break;

                }
            }
        }
    }

    //compute legal king moves now
    for (int square = 0; square < 64; square++) {

        currPiece = pieceLocations[square];
        if (currPiece != nullptr) {
            if (currPiece -> getType() == Piece::KING) {
                int checkKing[8] = {
                    7,
                    8,
                    9,
                    1,
                    -1,
                    -7,
                    -8,
                    -9
                };

                if (currPiece -> getColor() == Piece::WHITE) {

                    if ((std::find(wCheckMoves.begin(), wCheckMoves.end(), square) != wCheckMoves.end())) {
                        for (int i = 0; i < 64; i++) {
                            Piece * temp = pieceLocations[i];
                            std::vector < int > newMoves;

                            if (temp != nullptr) {
                                if (temp -> getColor() == currPiece -> getColor()) {
                                    for (int j = 0; j < (int) temp -> getLegalMoves().size(); j++) {
                                        if ((std::find(wCheckMoves.begin(), wCheckMoves.end(), j) != wCheckMoves.end())) {
                                            newMoves.push_back(temp -> getLegalMoves()[j]);
                                        }

                                    }

                                    temp -> getLegalMoves().clear();
                                    temp -> populateLegalMoves(newMoves);
                                }

                            }

                        }
                    }

                    for (int i = 0; i < 8; i++) {

                        int checkPos = checkKing[i] + square;

                        if (checkPos >= 0 && checkPos <= 63) {

                            if ((std::find(wCheckMoves.begin(), wCheckMoves.end(), checkPos) == wCheckMoves.end())) {

                                if (pieceLocations[checkPos] == nullptr) {
                                    populateMoves.push_back(checkPos);
                                } else {
                                    if (pieceLocations[checkPos] -> getColor() != currPiece -> getColor()) {
                                        populateMoves.push_back(checkPos);
                                    }
                                }

                                for (int j = 0; j < 8; j++) {
                                    if (checkPos + checkKing[j] >= 0 && checkPos + checkKing[j] <= 63 && checkPos + checkKing[j] != square) {
                                        if (pieceLocations[checkPos + checkKing[j]] != nullptr) {
                                            if (pieceLocations[checkPos + checkKing[j]] -> getType() == Piece::KING) {
                                                populateMoves.pop_back();
                                                break;
                                            }
                                        }
                                    }
                                }
                            }

                        }

                    }
                }

                if (currPiece -> getColor() == Piece::BLACK) {

                    //remove all moves that don't prevent king from being in check
                    if ((std::find(bCheckMoves.begin(), bCheckMoves.end(), square) != bCheckMoves.end())) {
                        for (int i = 0; i < 64; i++) {
                            Piece * temp = pieceLocations[i];
                            std::vector < int > newMoves;

                            if (temp != nullptr) {
                                if (temp -> getColor() == currPiece -> getColor()) {
                                    for (int j = 0; j < (int) temp -> getLegalMoves().size(); j++) {
                                        if ((std::find(bCheckMoves.begin(), bCheckMoves.end(), temp->getLegalMoves()[j]) != bCheckMoves.end())) {
                                            newMoves.push_back(temp -> getLegalMoves()[j]);
                                        }

                                    }
                                    temp -> getLegalMoves().clear();
                                    temp -> populateLegalMoves(newMoves);
                                }
                            }

                        }
                    }

                    for (int i = 0; i < 8; i++) {

                        int checkPos = checkKing[i] + square;

                        if (checkPos >= 0 && checkPos <= 63) {

                            if ((std::find(bCheckMoves.begin(), bCheckMoves.end(), checkPos) == bCheckMoves.end())) {

                                if (pieceLocations[checkPos] == nullptr) {
                                    populateMoves.push_back(checkPos);
                                } else {
                                    if (pieceLocations[checkPos] -> getColor() != pieceLocations[square] -> getColor()) {
                                        populateMoves.push_back(checkPos);
                                    }
                                }

                                for (int j = 0; j < 8; j++) {
                                    if (checkPos + checkKing[j] >= 0 && checkPos + checkKing[j] <= 63 && checkPos + checkKing[j] != square) {
                                        if (pieceLocations[checkPos + checkKing[j]] != nullptr) {
                                            if (pieceLocations[checkPos + checkKing[j]] -> getType() == Piece::KING) {
                                                populateMoves.pop_back();
                                                break;
                                            }
                                        }
                                    }
                                }

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
Board::Turn Board::getTurn() {
    return turn;
}

void Board::changeTurn() {
    if (turn == T_WHITE) {
        turn = T_BLACK;
    } else {
        turn = T_WHITE;
    }
}
void Board::addCheckMoves(Piece::Color attackingPiece, int pos) {
    if (attackingPiece == Piece::WHITE) {
        bCheckMoves.push_back(pos);
    } else {
        wCheckMoves.push_back(pos);
    }
}

