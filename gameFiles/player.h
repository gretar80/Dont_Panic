#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <string>
#include <fstream>
#include <vector>

class player : public QObject
{
    Q_OBJECT

    int score;
    std::vector<int> highscores;
    std::vector<std::string> player_names;
    const std::string path="../gameFiles/highscores.dat";
    
    void resetHighscores();

public:
    player();
    ~player();
    int getScore();
    void incrementScore(int);
    void appendScoreToFile();
    void readScoreFromFile();
    void resetScore();
    void sendScoreToWindow(int);
    void updateScore(std::string);
    bool checkHighscore();
    std::vector<int> getHighscores();
    std::vector<std::string> getNames();
signals:
    void updateScore(int);
};

#endif // PLAYER_H
