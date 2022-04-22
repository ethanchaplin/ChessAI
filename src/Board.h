/*
 * Board.h
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Piece.h"

class Board {
    public:

    enum Turn {
        T_WHITE,
        T_BLACK
    };
    Board(bool real);
    Board(const Board &board){

        turn = board.turn;
        for(int i = 0; i < 64; i++){
            if(board.pieceLocations[i] != nullptr){
                pieceLocations[i] = board.pieceLocations[i];}
            else{
                pieceLocations[i] = nullptr;
            }
        }
        bCheckLines = board.bCheckLines;
        wCheckLines = board.wCheckLines;
        wCheckMoves = board.wCheckMoves;
        bCheckMoves = board.bCheckMoves;

        real = board.real;

        bInCheck = board.bInCheck;
        wInCheck = board.wInCheck;

    }
    Piece * getPiece(int pos);
    Piece ** getPieces();
    std::vector <Piece* > getPieces(Piece::Color color);

    void setPiece(int pos, Piece * piece);
    virtual~Board();
    void computeAllPiecesLegalMove();
    void computeAllMoves();
    void movePiece(Piece * piece, int square);
    void attack(int square);
    Turn getTurn();
    void changeTurn();
    void addCheckMoves(Piece::Color attackingPiece, int pos);
    void addCheckLines(Piece::Color attackingPiece, int pos);
    bool doesMoveCauseCheck(int oldSquare, int newSquare);
    bool boardInCheck(Piece::Color color);
    bool find(std::vector<int> vec, int square);
    void removeMove(std::vector<int>& vec, int move);
    std::vector <int > getCheckMoves(Piece::Color color);
    std::vector <int > getCheckLines(Piece::Color color);
    float evaluate(Piece::Color);
    std::vector < Piece* > getBlackPieces();
    std::vector < Piece * > getWhitePieces();
    bool checkmate(Piece::Color color);
    void updateColorPieceVectors();
    int numPieces(Piece::Color color, Piece::Type type);

    int numPiecesOpposite(Piece::Color color, Piece::Type type);


    int numMoves(Piece::Color);
    int numMovesOpposite(Piece::Color);
    private:
    Piece * pieceLocations[64];
    Turn turn = T_WHITE;
    std::vector < int > wCheckMoves;
    std::vector < int > bCheckMoves;

    std::vector < int > wCheckLines;
    std::vector < int > bCheckLines;

    std::vector < Piece* > blackPieces;
    std::vector < Piece * > whitePieces;

    bool real;
    bool wInCheck;
    bool bInCheck;

};

#endif /* BOARD_H_ */
