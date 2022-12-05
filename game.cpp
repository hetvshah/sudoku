#include "game.hpp"
#include "cell.hpp"
#include "random.hpp"

#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

game::game(int difficulty) :
    difficulty {difficulty},
    grid {}
{
    // pick a random sudoku game and initialize each ansNum for cells in grid
    // also initialize cells

    auto numLocations {0};

    if (difficulty == 0) {
        // easy - 45
        numLocations = 45;
    } else if (difficulty == 1) {
        // medium - 30
        numLocations = 30;
    } else if (difficulty == 2) {
        // hard - 25
        numLocations = 25;
    }
    
    auto locations = randomCellLocations(9, 9, numLocations);
    
    // for (int i {0}; i < numLocations; ++i) {
    //     pair<int, int> curr_location = locations[i];
    //     cell curr_cell = grid[curr_location.first][curr_location.second];
    //     curr_cell.setCurrNum(curr_cell.getAnsNum());
    //     curr_cell.setIsChangeable(false);
    // }

    // undoStack.push(game);
}

// return -1 on error, 1 if won, and 0 otherwise
int game::processPut(int xCoord, int yCoord, int num) {
    cell curr_cell = grid[yCoord][xCoord];
    
    if (curr_cell.getIsChangeable()) {
        curr_cell.setCurrNum(num);
        grid[yCoord][xCoord] = curr_cell;
        // action new_action;
        // new_action.prevValue = num;
        // new_action.xCoord = xCoord;
        // new_action.yCoord = yCoord;
        // undoStack.push(new_action);
    } else {
        return -1;
    }
    
    if (isWon()) {
        return 1;
    }

    return 0;
}

int game::processRemove(int xCoord, int yCoord) {
    cell curr_cell = grid[yCoord][xCoord];
    
    if (curr_cell.getIsChangeable()) {
        curr_cell.setCurrNum(0);
        grid[yCoord][xCoord] = curr_cell;
        // stack.push(game);
    } else {
        return -1;
    }

    return 0;
}

void game::processHint() {
    auto hint = randomCellLocations(9, 9, 1)[0];

    int y = hint.first;
    int x = hint.second;

    while (!grid[y][x].getIsChangeable() || grid[y][x].isCorrect()) {
        hint = randomCellLocations(9, 9, 1)[0];
        y = hint.first;
        x = hint.second;
    }
    
    int currNum = grid[hint.first][hint.second].getCurrNum();
    int ansNum = grid[hint.first][hint.second].getAnsNum();

    if (currNum == 0) {
        // cell hasn't been guessed yet
        cout << "Hint: The number at (" << x << ", " << y << ") is " << ansNum;
    } else {
        cout << "Hint: Your current guess at (" << x << ", " << y << ") is incorrect. Try " << ansNum;
    }
}

void game::processCheck() {
    int correctGuesses = 0;
    int incorrectGuesses = 0;
    int numLeft = 0;

    for (int i {0}; i < 9; ++i) {
        for (int j {0}; j < 9; ++j) {
            if (grid[i][j].getIsChangeable() && grid[i][j].getCurrNum() != 0) {
                if (grid[i][j].getCurrNum() == grid[i][j].getAnsNum()) {
                    correctGuesses++;
                } else {
                    incorrectGuesses++;
                }
            } else {
                numLeft++;
            }
        }
    }

    cout << "You have " << correctGuesses << " correct guesses, " << incorrectGuesses << " incorrect guesses, and " << numLeft << " guesses left to make.\n";
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

bool game::isWon() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (grid[i][j].getAnsNum() != grid[i][j].getCurrNum())
                return false;
        }
    }

    return true;
}

ostream & operator<<(ostream & os, const game & g)
{
    // os << setw(3) << " "; // leave a space for the column of y coordinate labels
    // for (int i {0}; i < 9; ++i)
    // {
    //     // setw sets the width of the next thing to be printed
    //     // os << setw(3) << i + 1;
    //     os << setw(3) << " | ";
    // }
    // os << "\n";

    // print row by row
    for (int i {0}; i < 9; ++i)
    {
        // first print the y coordinate
        // os << setw(3) << i + 1;

        for (int j {0}; j < 9; ++j) {
            os << g.grid[j][i];
            if (j == 2 || j == 5) {
                os << setw(3) << " || ";
            } else {
                if (j != 8) {
                    os << setw(3) << " | ";
                }
            }
        }
        os << "\n";
        if (i == 2 || i == 5) {
            os << "-----------------------------------\n";
        }
    }
    return os;
}