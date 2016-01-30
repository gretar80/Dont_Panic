#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include "highscorewindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newGame(int);

    void on_easybutton_clicked();

    void on_mediumbutton_clicked();

    void on_hardbutton_clicked();

    void on_actionPlay_easy_triggered();

    void on_actionPlay_medium_triggered();

    void on_actionPlay_hard_triggered();

public slots:
    void updateHighscoreWindow(player*);

private:
    Ui::MainWindow *ui;
    HighScoreWindow hw;

protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
