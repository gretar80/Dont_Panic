#include "player.h"

using namespace std;

player::player()
{
    score = 0;
}

/**
 * Algorithm for keeping the two vectors sorted with corresponding
 * values to corresponding indexes when a new highscore is inserted
 */
void player::updateScore(string name){
    if(name.compare("") == 0)
        name = "NoName";
    int count_int_vec=0;
    for(vector<int>::const_iterator it = highscores.begin(); it != highscores.end(); it++){
        int max = *it;
        if(score > max){
            highscores.insert(it, score);
            highscores.pop_back();
            break;
        }
        count_int_vec++;
    }

    int count_string_vec=0;
    for(vector<string>::const_iterator it = player_names.begin(); it != player_names.end(); it++){
        if(count_string_vec == count_int_vec){
            player_names.insert(it,name);
            player_names.pop_back();
        }
        count_string_vec++;
    }
}

/** Write the contents of the vectors to file (in pairs) **/
void player::appendScoreToFile(){
    ofstream outf(path);        // Opens file, deletes current content
    if(!outf)
        exit(1);
    if(player_names.size() != 10 || highscores.size() != 10)
        resetHighscores();
    else
        for(int i=0; i<highscores.size();i++)
            outf << player_names[i] << " " << highscores[i] << endl;
}

void player::readScoreFromFile(){
    ifstream inf(path);
    if(!inf){
        resetHighscores();
        inf.open(path);
    }

    string n; int s;
    while(inf >> n >> s){
        player_names.push_back(n);
        highscores.push_back(s);
    }
    inf.close();
}

int player::getScore(){return score;}
vector<int> player::getHighscores(){return highscores;}
vector<string> player::getNames(){return player_names;}

void player::incrementScore(int s){
    score+=s;
    sendScoreToWindow(score);
}

void player::resetScore(){score=0;}

void player::sendScoreToWindow(int sc)
{
    emit updateScore(sc);
}

// Check if score makes the highscore list
bool player::checkHighscore(){
    for(int i=0; i<highscores.size(); i++){
        if(score > highscores[i])
            return true;
    }
    return false;
}

/**
 * In case of bad edit/corruption of highscore.dat, this will
 * reset to default values. Should be ten entries, with points
 * in descending order.
 */
void player::resetHighscores(){
    ofstream outf(path);
    if(!outf)
        exit(1);

    outf << "Chong" << " " << 30000 << endl;
    outf << "Wynn" << " " << 19500 << endl;
    outf << "Raylan" << " " << 16500 << endl;
    outf << "Mags" << " " << 12000 << endl;
    outf << "Avery" << " " << 9000 << endl;
    outf << "Dewey" << " " << 7300 << endl;
    outf << "Loretta" << " " << 5500 << endl;
    outf << "Ava" << " " << 2700 << endl;
    outf << "Arlo" << " " << 1500 << endl;
    outf << "Boyd" << " " << 900 << endl;
    outf.close();
}

player::~player()
{
}
