#ifndef BOMB_H
#define BOMB_H

#include "bombsignaller.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QObject>
#include <QMouseEvent>
#include <QEvent>


class Bomb : public QGraphicsPixmapItem
{
protected:          // protected used if implement subclasses
    QPoint point;   // stores the graphical coordinates for the bomb (x,y)
    int type;
    bool selected;
    int score;
    int i,j;        // Index of bomb in 2D grid
    BombSignaller* signaller;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    Bomb(QPoint, int, int, int);
    QRectF boundingRect() const;    // rectangle object which represent the bomb
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    // getters
    QPoint getPoint();
    int getType();
    bool getSelected();
    int getScore();
    int getIndexI();
    int getIndexJ();
    BombSignaller* getSignaller();

    // setters
    void setType(int);
    void setSelected(bool);
    void setI(int);
    void setJ(int);

    ~Bomb();
};

#endif // BOMB_H
