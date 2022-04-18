#include "MoveCircleItem.h"

MoveCircleItem::MoveCircleItem(const qreal a, const qreal b, const qreal c, const qreal d, Piece * piece, Game * game, int x, int y){

    this->setRect(a, b, c, d);
    this->piece = piece;
    this->game = game;
    this->x = x;
    this->y = y;
}
MoveCircleItem::~MoveCircleItem(){

}
void MoveCircleItem::mousePressEvent(QGraphicsSceneMouseEvent * event){
    game->movePiece(piece, (x + (8 * y)));

}
