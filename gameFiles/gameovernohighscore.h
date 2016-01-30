#ifndef GAMEOVERNOHIGHSCORE_H
#define GAMEOVERNOHIGHSCORE_H

#include <QDialog>

namespace Ui {
class GameOverNoHighscore;
}

class GameOverNoHighscore : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverNoHighscore(QWidget *parent = 0);
    ~GameOverNoHighscore();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GameOverNoHighscore *ui;
};

#endif // GAMEOVERNOHIGHSCORE_H
