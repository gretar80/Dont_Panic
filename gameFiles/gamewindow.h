#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "gamegrid.h"
#include "mainwindow.h"
#include "player.h"
#include <QDialog>
#include <QtCore>   // QTimeLine
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    void init();
    void setPlayer(player*);
    player* getPlayer();
    void setDifficulty(int);
    int getDifficulty();
    int getPossibleMoves();
    ~GameWindow();
signals:
    void signalAvailableMoves(int);
    void signalHighscore(player*);
public slots:
    void bombClicked(int, int);
    void bombUnclicked(int, int);
    void scoreUpdated(int);
    void slotAvailableMoves(int);
private slots:
    void on_quitButton_clicked();
private:
    Ui::GameWindow *ui;             // the gamewindow widget
    QGraphicsScene *scene;          // scene includes all game graphics
    GameGrid *grid;
    QList <Bomb*> selected_list;
    player* p;
    int difficulty;

    // constants
    const int NUMBEROFROWS = 8;     // grid size
    const int NUMBEROFCOLUMNS = 8;  // grid size
    const int SWAPDURATION = 200;   // delay in ms for swapping animation
    const int FALLDURATION = 50;   // delay in ms for falling animation

    GameGrid* createGrid(int,int,int);  // creates the gamegrid
    void delay(int);                    // used when waiting for animation to finish
    void connectSignalsToSlots(Bomb*);  // used to receive mouse-clicked-signals
    void checkSelectedBomb(int,int);        // checks the grid for selected bombs
    void animateFallingBomb(Bomb*,int); // animates a falling bomb 'n' spaces down
    void animateSwapBombs(Bomb*,Bomb*); // animates swapping bombs
    void generateBombAtColumn(int,int); // generate bomb at column i and falls 'n' spaces down
    void removeBomb(Bomb*);
};

#endif // GAMEWINDOW_H
