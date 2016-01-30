#include "highscorewindow.h"
#include "ui_highscorewindow.h"
#include <QTextBrowser>
#include <fstream>

HighScoreWindow::HighScoreWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighScoreWindow)
{
    ui->setupUi(this);

    std::ifstream inf("../gameFiles/highscores.dat");
    if(!inf){
        ui->textBrowser->setText("Creating file...");
        return;
    }
    QString scoreString;
    std::string n; int s;
    while(inf >> n >> s){
        scoreString.append(QString::fromStdString(n));
        scoreString.append(" ");
        scoreString.append(QString::fromStdString(std::to_string(s)));
        scoreString.append("\n");
    }
    inf.close();
    ui->textBrowser->setText(scoreString);
}

void HighScoreWindow::buildScoreString(player* p){
    QString scoreString;
    std::vector<int> scores = p->getHighscores();
    std::vector<std::string> names = p->getNames();
    for(int i=0; i< scores.size(); i++){
       scoreString.append(QString::fromStdString(names[i]));
       scoreString.append(" ");
       scoreString.append(QString::fromStdString(std::to_string(scores[i])));
       scoreString.append("\n");
    }
    ui->textBrowser->setText(scoreString);
}

HighScoreWindow::~HighScoreWindow()
{
    delete ui;
}
