#ifndef BOMBSIGNALLER_H
#define BOMBSIGNALLER_H

#include <QObject>

class BombSignaller : public QObject
{
    Q_OBJECT
public:
    BombSignaller();
    ~BombSignaller();
    void emitBombSelected(int, int);
    void emitBombUnselected(int, int);
signals:
    void BombSelectedSignal(int, int);
    void BombUnselectedSignal(int, int);
};

#endif // BOMBSIGNALLER_H
