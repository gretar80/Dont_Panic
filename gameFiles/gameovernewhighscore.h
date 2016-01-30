#ifndef GAMEOVERNEWHIGHSCORE_H
#define GAMEOVERNEWHIGHSCORE_H

#include <QDialog>

namespace Ui {
class GameOverNewHighscore;
}

class GameOverNewHighscore : public QDialog
{
    Q_OBJECT

public:
    std::string name;
    explicit GameOverNewHighscore(QWidget *parent = 0);
    ~GameOverNewHighscore();
    void setHighscoreLabel(int);
    void setName(QString n);
    std::string NameFromInput();

private slots:
    void on_inputField_editingFinished();

private:
    Ui::GameOverNewHighscore *ui;
};

#endif // GAMEOVERNEWHIGHSCORE_H
