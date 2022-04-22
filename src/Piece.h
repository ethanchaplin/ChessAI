/*
 * Piece.h
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#ifndef PIECE_H_
#define PIECE_H_

#include <vector>

class Piece {

    public:
        enum Color {
            BLACK = -1,
            WHITE = 1
        };
    enum Type {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        KING,
        QUEEN
    };

    Piece(Color color, Type type, int pos);
    Piece(Piece * piece){
        this->color = piece->color;
        this->type = piece->type;
        this->pos = piece->pos;
        this->legalMoves=piece->legalMoves;
        this->previousPos = piece->previousPos;
    }
    ~Piece();
    void move(int square);

    Piece* operator=(const Piece *p){

    Piece * piece = new Piece(p->color, p->type, p->pos);

    piece->legalMoves = p->legalMoves;
    piece->previousPos = p->previousPos;

    return piece;

    }


    Type getType();
    Color getColor();
    void setXPos(int x);
    void setYPos(int y);
    void setCompositePosition(int pos);
    void setCompositePosition(int x, int y);
    int getXPos();
    int getYPos();
    int getCompositePosition();
    std::vector < int > getLegalMoves();
    void populateLegalMoves(std::vector < int > moves);
    int getPreviousPos();
    bool hasPreviouslyMoved();
    void setPreviousPosition(int square);
    void setType(Type type);
    bool canMove();

    private:
        Color color;
    Type type;
    int pos;
    std::vector < int > legalMoves;
    int previousPos;
};

#endif /* PIECE_H_ */
