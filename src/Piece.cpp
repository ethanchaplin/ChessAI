/*
 * Piece.cpp
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#include "Piece.h"

Piece::Piece(Color color, Type type, int pos) {

    this -> color = color;
    this -> type = type;
    this -> pos = pos;
    previousPos = -1;

}



Piece::~Piece() {
    // TODO Auto-generated destructor stub
}

void Piece::move(int square) {
    previousPos = this->pos;
    setCompositePosition(square);

}

void Piece::setCompositePosition(int pos) {
    this -> pos = pos;
}

void Piece::setCompositePosition(int x, int y) {
    this -> pos = (8 * y) + x;
}

Piece::Color Piece::getColor() {
    return color;
}

Piece::Type Piece::getType() {
    return type;
}

void Piece::setXPos(int x) {

    int diff = x - getXPos();
    pos = pos + diff;
}

void Piece::setYPos(int y) {
    int diff = y - getYPos();
    pos = pos + (8 * diff);
}

int Piece::getXPos() {
    return pos - (pos / 8) * 8;
}

int Piece::getYPos() {
    return pos / 8;
}

int Piece::getCompositePosition() {
    return pos;
}
void Piece::populateLegalMoves(std::vector < int > moves) {
    legalMoves = moves;
}

std::vector < int > Piece::getLegalMoves() {
    return legalMoves;
}

bool Piece::hasPreviouslyMoved() {
    return (previousPos != -1);
}

void Piece::setType(Type type){
    this->type = type;
}

int Piece::getPreviousPos(){
    return previousPos;
}

void Piece::setPreviousPosition(int square){
    previousPos = square;
}

bool Piece::canMove(){
    return !legalMoves.empty();
}
