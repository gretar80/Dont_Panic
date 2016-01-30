#ifndef HIGHSCOREWINDOW_H
#define HIGHSCOREWINDOW_H

#include <QString>
#include <string>
#include <vector>
#include <QDialog>
#include "player.h"

namespace Ui {
class HighScoreWindow;
}

class HighScoreWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoreWindow(QWidget *parent = 0);
    ~HighScoreWindow();
    void buildScoreString(player*);

private:
    Ui::HighScoreWindow *ui;
};

#endif // HIGHSCOREWINDOW_H
