#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gameovernohighscore.h"
#include "gameovernewhighscore.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QPixmap>
#include <QEventLoop>
#include <QCoreApplication>
#include <QMessageBox>

GameWindow::GameWindow(QWidget *parent) : QDialog(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    p = new player();
    p->readScoreFromFile();
}

// gets called from the 'mainWindow'
void GameWindow::init()
{
    scene = new QGraphicsScene(this);       //this = parent
    scene->setSceneRect(-100,-100,600,600); // offset bombs 100px down-right

    QPixmap background(":/img/brick_background.png");
    scene->setBackgroundBrush(background);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // type rendering

    grid = createGrid(NUMBEROFCOLUMNS, NUMBEROFROWS, getDifficulty());

    // Draw the bombs in the scene
    for(int i = 0; i < grid->get_bomb_list().size(); i++)
    {
        Bomb* b = grid->get_bomb_list()[i];
        scene->addItem(b);
        connectSignalsToSlots(b);
    }

    // Iterate over the grid to find 3-matches and replace them
    // to create a clean game grid
    QList<Bomb*> matches = grid->checkForMatches();

    while(!matches.empty())
    {
        for(int i = 0; i < matches.size(); i++)
        {
            int indexI=matches[i]->getIndexI();
            int indexJ=matches[i]->getIndexJ();
            // Replace bomb with a random generated one and add to scene
            QPoint qp = matches[i]->getPoint();
            Bomb* b = new Bomb(qp, qrand()%5+1, indexI, indexJ);
            grid->replaceBombAtIndex(indexI, indexJ, b);
            scene->addItem(b);
            // connect bomb with mouseclicked-signal
            connectSignalsToSlots(b);
        }

        matches.clear();
        matches = grid->checkForMatches();
    }
    // connect the score counter to the game logic
    connect(GameWindow::getPlayer(), SIGNAL(updateScore(int)),ui->lcdNumber,SLOT(display(int)));
    // connect the 'available moves' counter to the game logic
    connect(this, SIGNAL(signalAvailableMoves(int)),ui->lcdAvailableMoves ,SLOT(display(int)));

    // initialize the 'available moves' counter
    ui->lcdAvailableMoves->display(this->getPossibleMoves());

    // if possible moves is zero, then "game over"
    if(getPossibleMoves() == 0)
    {
        GameOverNoHighscore gameover;
        gameover.exec();
        this->close();
    }
}

// create a gamegrid
GameGrid* GameWindow::createGrid(int col, int row, int dif)
{
    // create bomb grid
    return new GameGrid(col,row,dif);
}

// delay function, borrowed from user 'kshark27' on stackoverflow.com
void GameWindow::delay(int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

// this function will move bomb 'x' spaces down
// Note! This method only moves the graphics and DOES NOT CHANGE THE INDEX in the list
void GameWindow::animateFallingBomb(Bomb* b, int spaces)
{
    // timer
    QTimeLine *timer = new QTimeLine(FALLDURATION);
    timer->setFrameRange(0, FALLDURATION);

    // animation
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(b);
    animation->setTimeLine(timer);

    // calculation for each step of the animation
    float stepY = (spaces*50) / 200.0; // size of each step
    float tempPosY = b->y() * 1.0;   // return a float
    float fixedX = b->x();

    // implement the animation
    for (int i = 1; i <= 200; ++i)
    {
        tempPosY += stepY;
        animation->setPosAt(i / 200.0, QPointF(fixedX,tempPosY));
    }

    timer->start();
    delay(FALLDURATION+10); // delay is called so pointers b1 and b2 will not be deleted before animation is finished

    // clean up after animation is finished
    delete animation;
    delete timer;
}


// Only visualized swap
void GameWindow::animateSwapBombs(Bomb* b1, Bomb* b2)
{
    // timer for b1
    QTimeLine *timer1 = new QTimeLine(SWAPDURATION);
    timer1->setFrameRange(0, SWAPDURATION);

    // timer for b2
    QTimeLine *timer2 = new QTimeLine(SWAPDURATION);
    timer2->setFrameRange(0, 100);

    // animation for b1
    QGraphicsItemAnimation *animation1 = new QGraphicsItemAnimation;
    animation1->setItem(b1);
    animation1->setTimeLine(timer1);

    // animation for b2
    QGraphicsItemAnimation *animation2 = new QGraphicsItemAnimation;
    animation2->setItem(b2);
    animation2->setTimeLine(timer2);

    // calculation for each step of the animation for b1
    float b1_stepX = (b2->x() - b1->x()) / 200.0;
    float b1_stepY = (b2->y() - b1->y()) / 200.0;
    float b1_tempX = b1->x() * 1.0;
    float b1_tempY = b1->y() * 1.0;

    // calculation for each step of the animation for b2
    float b2_stepX = (b1->x() - b2->x()) / 200.0;
    float b2_stepY = (b1->y() - b2->y()) / 200.0;
    float b2_tempX = b2->x() * 1.0;
    float b2_tempY = b2->y() * 1.0;

    // implement the animation
    for (int i = 1; i <= 200; ++i)
    {
        b1_tempX += b1_stepX;
        b1_tempY += b1_stepY;

        b2_tempX += b2_stepX;
        b2_tempY += b2_stepY;

        animation1->setPosAt(i / 200.0, QPointF(b1_tempX,b1_tempY));
        animation2->setPosAt(i / 200.0, QPointF(b2_tempX,b2_tempY));
    }

    timer1->start();
    timer2->start();
    delay(SWAPDURATION+10); // delay is called so pointers b1 and b2 will not be deleted before animation is finished

    // clean up after animation is finished
    delete animation1;
    delete animation2;
    delete timer1;
    delete timer2;
}

// when object is clicked, it sends a signal, that must be connected to a slot
void GameWindow::connectSignalsToSlots(Bomb* b)
{
    connect(b->getSignaller(), &BombSignaller::BombSelectedSignal,
            this, &GameWindow::bombClicked);

    connect(b->getSignaller(), &BombSignaller::BombUnselectedSignal,
            this, &GameWindow::bombUnclicked);
}


// generates a bomb at (i,j), animates the drop and removes the old bomb
void GameWindow::generateBombAtColumn(int i, int j)
{
    QPoint *p = new QPoint();
    // bomb starts one row above top of grid (-50px)
    p->setX(i*50);
    p->setY(-50);

    //generate a new bomb and set all parameters
    Bomb* b = new Bomb(*p,qrand()%(getDifficulty())+1,i,j);

    grid->replaceBombAtIndex(i,j,b);
    connectSignalsToSlots(b);
    scene->addItem(b);
    animateFallingBomb(b,j+1);

    delete p;
}

// this slot receives a 'clicked'-signal from bomb (i,j)
void GameWindow::bombClicked(int i, int j)
{
    checkSelectedBomb(i, j);
}

// this slot receives a 'unclicked'-signal from bomb (i,j)
void GameWindow::bombUnclicked(int i, int j)
{
    for(int k=0; k<selected_list.size(); k++)
        if(selected_list[k]->getIndexI() == i && selected_list[k]->getIndexJ() == j)
            selected_list.removeAt(k);
}

// Main game logic starts here
void GameWindow::checkSelectedBomb(int i, int j)
{
    // Find corresponding index in bomblist, from coordinates (i,j)
    // and add to the 'selected_list' of bombs
    int bomblist_index = grid->index(i,j);
    selected_list.push_back(grid->get_bomb_list()[bomblist_index]);

    // Only one bomb is currently selected, wait for next selection
    if(selected_list.size() == 1)
        return;
    else
    {
        // add bombs to 'selected_list'
        Bomb* b1 = selected_list[0]; Bomb* b2 = selected_list[1];

        // If not neighbours, clear the first selected bomb (QList will 'compress' automatically)
        if(!grid->isNeighbours(b1,b2))
        {
            b1->setSelected(false);
            selected_list.removeFirst();
        }
        // Swap bombs if they are neighbors
        else
        {
            // Unselect afterwards
            b1->setSelected(false);
            b2->setSelected(false);
            while(!selected_list.isEmpty())
                selected_list.pop_back();   // Clear list

            grid->swapBombs(b1, b2);
            animateSwapBombs(b1,b2);
            // if no new matches are found after swap, then swap the bombs back
            if(grid->checkForMatches().empty())
            {
                grid->swapBombs(b2, b1);
                animateSwapBombs(b2,b1);
            }
            // found a match! - here is where the real algorithm starts
            else
            {
                // list of matching bombs
                QList<Bomb*> removedList = grid->checkForMatches();
                while(!removedList.empty())
                {
                    p->incrementScore(removedList.size()*100);
                    // remove matching bombs (i.e. replace with ghostbombs)
                    for(int i = 0; i < removedList.size(); i++)
                        grid->deleteBomb(removedList[i]);
                    int spacesToMoveBombDown = 0;
                    // go through columns, move bombs down and generate new ones
                    for(int column = 0; column < NUMBEROFCOLUMNS; column++)
                    {
                        // search from bottom-up and move bombs down
                        for(int row = NUMBEROFROWS-1; row >= 0; row--)
                        {
                            // check if ghostbomb
                            if(grid->getBombAt(column,row)->getType() == 0)
                                spacesToMoveBombDown++;
                            else
                            {
                                if(spacesToMoveBombDown > 0)
                                {
                                    animateFallingBomb(grid->getBombAt(column,row),spacesToMoveBombDown);
                                    grid->swapBombs(grid->getBombAt(column,row),grid->getBombAt(column,row+spacesToMoveBombDown));
                                }
                            }
                        }
                        // all bombs have been moved down
                        // generate new bombs if we found any ghostbombs in this column
                        if(spacesToMoveBombDown > 0)
                            for(int h = spacesToMoveBombDown; h > 0; h--)
                                generateBombAtColumn(column,h-1);
                        // reset for next column
                        spacesToMoveBombDown = 0;
                    }
                    // check the grid has more 3+matches before we start swapping again
                    removedList.clear();
                    removedList = grid->checkForMatches();
                }
            }
        }
    }
    int pm = getPossibleMoves();
    emit signalAvailableMoves(pm);
    // if possible moves is zero, then "game over"
    if(pm == 0)
    {
        // check if player gets a new highscore
        if(p->checkHighscore())
        {
            GameOverNewHighscore gameover;
            gameover.setHighscoreLabel(p->getScore());
            gameover.exec();

            // get nickname from the user field
            p->updateScore(gameover.NameFromInput());
            emit signalHighscore(p);
            this->close();
        }
        else{
            GameOverNoHighscore gameover;
            gameover.exec();
            this->close();
        }
    }
}// End checkSelectedBomb

void GameWindow::setPlayer(player* _p){
    p=_p;
    qDebug() << "Player " << p->getScore();
}

player *GameWindow::getPlayer()
{
    return p;
}

void GameWindow::setDifficulty(int d)
{
    difficulty = d;
}

int GameWindow::getDifficulty()
{
    return difficulty;
}

int GameWindow::getPossibleMoves()
{
    int counter = 0;

    // start top left and swap to the right (and back), every other column
    // and check if it will result in a match
    for(int column = 0; column < NUMBEROFCOLUMNS-1; column++)
    {
        for(int row = 0; row < NUMBEROFROWS; row++)
        {
            // make the swap
            grid->swapBombs(grid->getBombAt(column,row),grid->getBombAt(column+1,row));

            // check for matches
            if(!grid->checkForMatches().empty())
                counter++;

            // swap back
            grid->swapBombs(grid->getBombAt(column,row),grid->getBombAt(column+1,row));
        }
    }

    // start top left and swap downwards (and back), every other row
    // and check if it will result in a match
    for(int column = 0; column < NUMBEROFCOLUMNS; column++)
    {
        for(int row = 0; row < NUMBEROFROWS-1; row++)
        {
            // make the swap
            grid->swapBombs(grid->getBombAt(column,row),grid->getBombAt(column,row+1));

            // check for matches
            if(!grid->checkForMatches().empty())
                counter++;

            // swap back
            grid->swapBombs(grid->getBombAt(column,row),grid->getBombAt(column,row+1));
        }
    }

    return counter;
}

GameWindow::~GameWindow()
{
    delete ui;
    p->appendScoreToFile();
    delete p;
    delete scene;
    delete grid;
}

void GameWindow::on_quitButton_clicked()
{
    if(p->checkHighscore())
    {
        // Highscore!
        GameOverNewHighscore gameover;
        gameover.setHighscoreLabel(p->getScore());
        gameover.exec();

        //get name from the input field
        p->updateScore(gameover.NameFromInput());
        emit signalHighscore(p);
        this->close();
    }
    else
    {
        this->close();
    }
}

void GameWindow::scoreUpdated(int s)
{
    ui->lcdNumber->display(s);
}

void GameWindow::slotAvailableMoves(int am)
{
    ui->lcdAvailableMoves->display(am);
}

