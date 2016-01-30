#include "gameovernohighscore.h"
#include "ui_gameovernohighscore.h"

GameOverNoHighscore::GameOverNoHighscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverNoHighscore)
{
    ui->setupUi(this);
}

GameOverNoHighscore::~GameOverNoHighscore()
{
    delete ui;
}

void GameOverNoHighscore::on_pushButton_clicked()
{
    this->close();
}
