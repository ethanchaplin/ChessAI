#ifndef PIECEITEM_H
#define PIECEITEM_H

#include <QGraphicsPixmapItem>
#include "Piece.h"
#include "Game.h"
class PieceItem : public QGraphicsPixmapItem
{
public:
    PieceItem(const QPixmap &pixmap, Piece* piece, Game* game);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    ~PieceItem();
private:

    Piece* piece;
    Game* game;
};

#endif // PIECEITEM_H
