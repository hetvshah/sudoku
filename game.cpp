#include "game.hpp"
#include "cell.hpp"
#include "random.hpp"
#include "safe.hpp"
#include "mine.hpp"

#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

game::game(int difficulty) :
    difficulty {difficulty},
    grid {} // needs to be a 2D array
{
    // unique_ptr<pair<int, int> []> mine_locations = randomMineLocations(width, height, 0, 0, amount);
    // numSafeSpaces = height*width - amount;
    // // set up each column
    // for (int i {0}; i < width; ++i)
    // {
    //     grid[i] = make_unique<shared_ptr<cell> []>(height);
    // }
}

int game::processGuess(int xCoord, int yCoord){
    return 0;
}

int game::processHint() {
    return 0;
}

int game::processUndo() {
    return 0;
}

int game::processRedo() {
    return 0;
}

// Uncovers all the cells since the game is over
void game::uncoverAll() {
    // for (int i {0}; i < width; ++i) {
    //     for (int j {0}; j < height; ++j) {
    //         grid[i][j]->changedCovered(false);
    //     }
    // }
}

ostream & operator<<(ostream & os, const game & g)
{
    // first print the top row of x coordinates
    os << setw(3) << " "; // leave a space for the column of y coordinate labels
    for (int i {0}; i < g.width; ++i)
    {
        // setw sets the width of the next thing to be printed
        os << setw(3) << i + 1;
    }
    os << "\n";

    // print row by row
    for (int i {0}; i < g.height; ++i)
    {
        // first print the y coordinate
        os << setw(3) << i + 1;

        // for (int j {0}; j < g.width; ++j) {
        //     os << setw(3);
        //     g.grid[j][i]->print(os);
        // }
        os << "\n";
    }
    return os;
}