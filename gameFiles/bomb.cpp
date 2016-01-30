#include "bomb.h"
#include <QPixmap>
#include <QPainter>

Bomb::Bomb(QPoint p, int t, int _i, int _j)
{
    signaller = new BombSignaller();
    i=_i;
    j=_j;
    point = p;
    type = t;
    score = 10;

    // variables for mouse functions
    selected = false;

    setFlag(ItemIsSelectable);
    setPos(mapToParent(point.rx(),point.ry()));
}

// must implement for 'QGraphicsPixmapItem' class
QRectF Bomb::boundingRect() const
{
    return QRectF(0,0,50,50);
}

// must implement for 'QGraphicsPixmapItem' class
void Bomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();

    // draw bomb
    if(!selected)
    {
        if(type == 1)
        {
            QPixmap map(0,0);
            map.load(":/img/bomb1.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 2)
        {
            QPixmap map(0,0);
            map.load(":/img/bomb2.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 3)
        {
            QPixmap map(0,0);
            map.load(":/img/bomb3.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 4)
        {
            QPixmap map(0,0);
            map.load(":/img/bomb4.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 5)
        {
            QPixmap map(0,0);
            map.load(":/img/bomb5.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 6)
        {
            QPixmap map(0,0);
            map.load(":/img/bomb6.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 7)
        {
            QPixmap map(0,0);
            map.load(":/img/bomb7.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 8)
        {
            QPixmap map(0,0);
            map.load(":/img/bomb8.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else
        {
            QPixmap map(0,0);
            map.load(":/img/bomb9.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
    }
    else
    {
        if(type == 1)
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb1.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 2)
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb2.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 3)
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb3.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 4)
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb4.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 5)
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb5.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 6)
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb6.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 7)
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb7.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else if(type == 8)
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb8.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
        else
        {
            QPixmap map(0,0);
            map.load(":/img/selected_bomb9.png");
            setPixmap(map);
            painter->drawPixmap(rec, map, rec);
        }
    }
}

// getters
QPoint Bomb::getPoint()
{
    return point;
}

int Bomb::getType()
{
    return type;
}

bool Bomb::getSelected()
{
    return selected;
}

int Bomb::getScore()
{
    return score;
}

int Bomb::getIndexI(){
    return i;
}

int Bomb::getIndexJ(){
    return j;
}

BombSignaller* Bomb::getSignaller(){
    return signaller;
}

// setters
void Bomb::setType(int t)
{
    type=t;
}

void Bomb::setSelected(bool s)
{
    selected = s;
}

void Bomb::setI(int _i){
    i=_i;
}

void Bomb::setJ(int _j){
    j=_j;
}

void Bomb::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!selected){
        selected = true;
        signaller->emitBombSelected(i,j);
    }
    else{
        selected = false;
        signaller->emitBombUnselected(i,j);
    }
}

Bomb::~Bomb()
{
    delete signaller;
}

