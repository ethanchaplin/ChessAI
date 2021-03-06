#include "PieceItem.h"
#include "QGraphicsSceneMouseEvent"
#include <algorithm>
#include <QDebug>
#include "Game.h"
PieceItem::PieceItem(const QPixmap &pixmap, Piece* piece, Game * game)
{


    this->setPixmap(pixmap);
    this->piece = piece;
    this->game = game;


}

PieceItem::~PieceItem(){

    if(piece != nullptr)
        delete piece;
}

void PieceItem::mousePressEvent(QGraphicsSceneMouseEvent * event){


    if(piece != nullptr && game->isActive()){

    game->showPieceMoves(piece);
    QGraphicsItem::mousePressEvent(event);
}

}

void PieceItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event){


    QGraphicsItem::mouseMoveEvent(event);
}
void PieceItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event){

    if(game->isActive()){
    if(piece != nullptr){

    int prevX = (int)piece->getXPos()*50;
    int prevY = (int)piece->getYPos()*50;



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
    if(newX != prevX || newY != prevY){

    int test = (newX/50) + (newY / 50)*8;

    for(int i = 0; i< (int)piece->getLegalMoves().size(); i++){
        if(piece->getLegalMoves()[i] == test){
            prevX = newX;
            prevY = newY;
            game->movePiece(piece, test);



            break;
        }
        else{
            continue;
        }
    }


    this->setPos(QPoint(prevX, prevY));
    }

    else{
        this->setPos(QPoint(prevX, prevY));
    }
    QGraphicsItem::mouseReleaseEvent(event);
}
    }
}

Piece * PieceItem::getPiece(){

    if(piece == nullptr){
        return nullptr;
    }
    else{
    return piece;
    }
    }
