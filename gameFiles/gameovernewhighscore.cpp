#include "gameovernewhighscore.h"
#include "ui_gameovernewhighscore.h"
#include <QMessageBox>

GameOverNewHighscore::GameOverNewHighscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverNewHighscore)
{
    ui->setupUi(this);
}

GameOverNewHighscore::~GameOverNewHighscore()
{
    delete ui;
}

void GameOverNewHighscore::setHighscoreLabel(int score)
{
    QString s = QString::number(score);
    ui->HighscoreLabel->setText(s);
}

void GameOverNewHighscore::setName(QString n)
{
    name = n.toStdString();
}

std::string GameOverNewHighscore::NameFromInput()
{
    return name;
}


void GameOverNewHighscore::on_inputField_editingFinished()
{
    // this function is called when the user has pressed enter or the box loses focus.
    QString n = ui->inputField->text();
    setName(n);
    this->close();
}
