#include "mainwindow.h"
#include <QApplication>
#include <QSize>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    // generate new random seed for each run
    qsrand(time(NULL));

    QApplication a(argc, argv);    
    MainWindow w;
    // make non-resizable
    w.setFixedSize(400,400);
    // center the main window
    w.move((QApplication::desktop()->screen()->width()-w.width())/2, (QApplication::desktop()->screen()->height()-w.height())/2);

    // highscore window
    w.show();
    return a.exec();
}



