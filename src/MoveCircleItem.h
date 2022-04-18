#ifndef MOVECIRCLEITEM_H
#define MOVECIRCLEITEM_H

#include <QGraphicsEllipseItem>
#include "Piece.h"
#include "Game.h"
class MoveCircleItem : public QGraphicsEllipseItem
{
public:
    MoveCircleItem(const qreal a, const qreal b, const qreal c, const qreal d, Piece * piece, Game * game, int x, int y);
    ~MoveCircleItem();
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
private:
    Piece * piece;
    Game * game;
    int x;
    int y;
};

#endif // MOVECIRCLEITEM_H
