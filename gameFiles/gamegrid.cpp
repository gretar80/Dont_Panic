#include "gamegrid.h"

GameGrid::GameGrid(int r, int c, int bt) : rows{r}, columns{c}, bombTypes{bt}
{
    // Create the bombs and add to QList
    int xcoord;
    int ycoord = 0;

    for(int j = 0; j < rows; j++)
    {
        xcoord = 0;

        for(int i = 0; i < columns; i++)
        {
            QPoint *p = new QPoint();
            p->setX(xcoord);
            p->setY(ycoord);

            Bomb* bomb = new Bomb(*p,qrand()%bt+1, i, j);
            bomb_list.push_back(bomb);
            xcoord += 50;

            delete p;
        }
         ycoord += 50;
    }

}

QList<Bomb *> GameGrid::get_bomb_list()
{
    return bomb_list;
}

int GameGrid::getColumns()
{
    return columns;
}

int GameGrid::getRows()
{
    return rows;
}

Bomb* GameGrid::getBombAt(int i, int j)
{
    return bomb_list[index(i,j)];
}

int GameGrid::getBombTypes()
{
    return bombTypes;
}


// returns the index[] in the bomb_list
// usage: bomb_list[index(x,y)]
int GameGrid::index(int colNr, int rowNr)
{
    return (rowNr) * columns + (colNr);
}

// Check if two bombs are neighbours in the grid
bool GameGrid::isNeighbours(Bomb* b1, Bomb* b2)
{
    int b1_i = b1->getIndexI(), b1_j = b1->getIndexJ(),
            b2_i=b2->getIndexI(), b2_j=b2->getIndexJ();

    if(b1_i==b2_i && b1_j==b2_j)
        return false;
    else if(b1_i == b2_i && ( b1_j == b2_j+1 || b1_j == b2_j-1 ) )
    {
        return true;
    }
    else if(b1_j == b2_j && ( b1_i == b2_i+1 || b1_i == b2_i-1 ) )
    {
        return true;
    }
    else return false;
}

/*
 * Swaps two bombs in the bomb_list, changing their 'logical
 * position' (no animation is done here). If no matches are
 * found after swap, the bombs will be swapped back to original
 * positions
 */
void GameGrid::swapBombs(Bomb* b1, Bomb* b2)
{
    // i and j indices for b1 and b2
    int b1_i = b1->getIndexI(), b1_j = b1->getIndexJ(),
        b2_i = b2->getIndexI(), b2_j = b2->getIndexJ();

    // swap indices in the 'bomb_list'
    int index_b1 = index(b1_i, b1_j);
    int index_b2 = index(b2_i, b2_j);
    bomb_list.swap(index_b1, index_b2);

    b1->setI(b2_i); b1->setJ(b2_j);
    b2->setI(b1_i); b2->setJ(b1_j);
}

// searches all grid for matches and returns a list of bombs that match
QList<Bomb *> GameGrid::checkForMatches()
{
    QList<Bomb *> matchingBombs;

    bool match;
    bool second;

    // first check horziontally
    for(int i = 0; i < rows-2; i++)
    {
        // reset for each column
        match = false;
        second = false;

        // start top left and work downwards
        for(int j = 0; j < columns; j++)
        {
            Bomb* b1 = bomb_list[index(i,j)];
            Bomb* b2 = bomb_list[index(i+1,j)];
            Bomb* b3 = bomb_list[index(i+2,j)];

            if(b1->getType() == b2->getType() && b1->getType() != 0)
                second = true;

            if(second && b1->getType() == b3->getType() && b1->getType() != 0)
                match = true;
            else
                second = false;

            // if three bombs match, add them to mathinglist if not already included
            if(match)
            {
                // check if included before
                if(matchingBombs.indexOf(b1) == -1)
                    matchingBombs.push_back(b1);
                if(matchingBombs.indexOf(b2) == -1)
                    matchingBombs.push_back(b2);
                if(matchingBombs.indexOf(b3) == -1)
                    matchingBombs.push_back(b3);

                // reset for next iteration
                match = false;
                second = false;
            }
        }
    }

    // now check vertically
    for(int i = 0; i < rows; i++)
    {
        // reset for each row
        match = false;
        second = false;

        // start top left and work to the right
        for(int j = 0; j < columns-2; j++)
        {
            Bomb* b1 = bomb_list[index(i,j)];
            Bomb* b2 = bomb_list[index(i,j+1)];
            Bomb* b3 = bomb_list[index(i,j+2)];

            if(b1->getType() == b2->getType() && b1->getType() != 0)
                second = true;

            if(second && b1->getType() == b3->getType() && b1->getType() != 0)
                match = true;
            else
                second = false;

            // if three bombs match, add them to mathinglist if not already included
            if(match)
            {
                // check if included before
                if(matchingBombs.indexOf(b1) == -1)
                    matchingBombs.push_back(b1);
                if(matchingBombs.indexOf(b2) == -1)
                    matchingBombs.push_back(b2);
                if(matchingBombs.indexOf(b3) == -1)
                    matchingBombs.push_back(b3);

                // reset for next iteration
                match = false;
                second = false;
            }
        }
    }
    return matchingBombs;
}

// replaces bomb and deletes the old one
void GameGrid::replaceBombAtIndex(int i, int j, Bomb* b)
{
    Bomb* temp = bomb_list[index(i,j)];
    bomb_list.replace(index(i,j),b);
    delete temp;
}

// replaces the bomb-pointer with a ghostbomb
void GameGrid::deleteBomb(Bomb* b)
{
    Bomb* ghostBomb = new Bomb(b->getPoint(),0,b->getIndexI(),b->getIndexJ());
    // replace (and delete) a bomb with a ghostbomb
    replaceBombAtIndex(b->getIndexI(),b->getIndexJ(),ghostBomb);
}



