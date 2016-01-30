#ifndef GAMEGRID_H
#define GAMEGRID_H

#include "bomb.h"
#include <QList>

class GameGrid
{
    QList<Bomb*> bomb_list;
    int rows, columns;
    int bombTypes;
public:
    GameGrid(int,int,int);

    int index(int,int);
    bool isNeighbours(Bomb*,Bomb*);
    void swapBombs(Bomb*,Bomb*);
    QList<Bomb*> checkForMatches();
    void replaceBombAtIndex(int,int,Bomb*);
    void deleteBomb(Bomb*);

    // getters
    QList<Bomb*> get_bomb_list();
    int getRows();
    int getColumns();
    Bomb* getBombAt(int,int);
    int getBombTypes();
};

#endif // GAMEGRID_H
