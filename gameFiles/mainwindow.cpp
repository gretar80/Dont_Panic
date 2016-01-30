#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hw.setFixedSize(240,320);
    hw.move(100,100);
    hw.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// close all windows on exit
void MainWindow::closeEvent(QCloseEvent*)
{
    qApp->quit();
}

void MainWindow::newGame(int diff)
{
    GameWindow gw;

    connect(&gw, SIGNAL(signalHighscore(player*)),this,SLOT(updateHighscoreWindow(player*)));
    gw.setFixedSize(800,670);
    gw.setDifficulty(diff);
    gw.init();
    gw.setModal(true);  // this window becomes 'active', cannot switch to mainWindow
    gw.move(342,100);
    gw.exec();
}

void MainWindow::on_easybutton_clicked()
{
    newGame(5); // 5 bomb types
}

void MainWindow::on_mediumbutton_clicked()
{
    newGame(7); // 7 bomb types
}

void MainWindow::on_hardbutton_clicked()
{
    newGame(9); // 9 bomb types
}

void MainWindow::on_actionPlay_easy_triggered()
{
    newGame(5); // 5 bomb types
}

void MainWindow::on_actionPlay_medium_triggered()
{
    newGame(7); // 7 bomb types
}

void MainWindow::on_actionPlay_hard_triggered()
{
    newGame(9); // 9 bomb types
}

void MainWindow::updateHighscoreWindow(player* p){
    hw.buildScoreString(p);
}
