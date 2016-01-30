#include "bombsignaller.h"

BombSignaller::BombSignaller()
{

}

BombSignaller::~BombSignaller()
{

}

void BombSignaller::emitBombSelected(int i, int j){
    emit BombSelectedSignal(i,j);
}

void BombSignaller::emitBombUnselected(int i, int j){
    emit BombUnselectedSignal(i,j);
}
