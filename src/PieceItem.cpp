#include "PieceItem.h"
#include "QGraphicsSceneMouseEvent"

#include <iostream>
PieceItem::PieceItem(const QPixmap &pixmap, Piece* piece, Game * game)
{


    this->setPixmap(pixmap);
    this->piece = piece;
    this->game = game;


}

PieceItem::~PieceItem(){
    delete piece;
}

void PieceItem::mousePressEvent(QGraphicsSceneMouseEvent * event){



    game->showPieceMoves(piece);
    QGraphicsItem::mousePressEvent(event);


}

void PieceItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event){


    QGraphicsItem::mouseMoveEvent(event);
}
void PieceItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event){
    int newX;
    int newY;
    if((int)this->pos().rx() % 50 >= 25){

        newX = (int)this->pos().rx() + 50 - ((int)this->pos().rx() % 50);
    }
    else{
        newX = (int)this->pos().rx() - ((int)this->pos().rx() % 50);
    }

    if((int)this->pos().ry() % 50 >= 25){
        newY = (int)this->pos().ry() + 50 - ((int)this->pos().ry() % 50);
    }
    else{
        newY = (int)this->pos().ry() - ((int)this->pos().ry() % 50);
    }


    this->setPos(QPoint(newX,newY));

    QGraphicsItem::mouseReleaseEvent(event);

}
