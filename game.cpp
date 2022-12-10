#include "game.hpp"
#include "cell.hpp"
#include "random.hpp"

#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <random>
#include <string>

using namespace std;

//Helper function to read from a certain line of the sudoku file
std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

string switchNumbers(string original, string digit1, string digit2) {
    string switched;
    for (int i = 0; i < original.length(); ++i) {
        if (original[i] == digit1[0]) 
            switched = switched + digit2[0];
        else if (original[i] == digit2[0])
            switched = switched + digit1[0];
        else
            switched = switched + original[i];
    }
    
    return switched;
}

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
    
    //Import game from sudokus.txt
    fstream file("sudokus.txt");

    random_device rd;
    mt19937 rng(rd()); 
    uniform_int_distribution<int> uni(1,10000); 

    auto random_integer = uni(rng);
    GotoLine(file, random_integer);
    string line;
    file >> line;

    //loop to do 5 bijective switches of integers from the original given line
    for (int i = 0; i < 5; ++i) {
        random_device rd2;
        mt19937 rng2(rd2()); 
        uniform_int_distribution<int> uni2(1,9); 
        auto random_integer2 = uni2(rng2);

        random_device rd3;
        mt19937 rng3(rd3()); 
        uniform_int_distribution<int> uni3(1,9); 
        auto random_integer3 = uni3(rng3);

        line = switchNumbers(line, to_string(random_integer2),to_string(random_integer3));
    }

    int index = 0;

    //cout << line << "\n";
    for (int i {0}; i < 9; ++i) {
        for (int j {0}; j < 9; ++j) {
            int num = line[index] - '0';
            ++index;
            cell curr_cell = grid[j][i];
            //cout<< num;
            curr_cell.setAnsNum(num);
            grid[j][i] = curr_cell;
        }
    }
    
    

    for (int i {0}; i < numLocations; ++i) {
        pair<int, int> curr_location = locations[i];
        cell curr_cell = grid[curr_location.first][curr_location.second];
        curr_cell.setCurrNum(curr_cell.getAnsNum());
        curr_cell.setIsChangeable(false);
        grid[curr_location.first][curr_location.second] = curr_cell;
    }

    // undoStack.push(game);
}

// return 1 if won, and 0 otherwise
int game::processPut(int xCoord, int yCoord, int num) {
    cell curr_cell = grid[yCoord][xCoord];
    
    if (curr_cell.getIsChangeable()) {
        action new_action {curr_cell.getCurrNum(), xCoord, yCoord};
        undoStack.push(new_action);

        curr_cell.setCurrNum(num);
        grid[yCoord][xCoord] = curr_cell;

        clearRedoStack();
    }
    
    if (isWon()) {
        return 1;
    }

    return 0;
}

void game::processRemove(int xCoord, int yCoord) {
    cell curr_cell = grid[yCoord][xCoord];
    
    if (curr_cell.getIsChangeable()) {
        action new_action {curr_cell.getCurrNum(), xCoord, yCoord};
        undoStack.push(new_action);

        curr_cell.setCurrNum(0);
        grid[yCoord][xCoord] = curr_cell;

        clearRedoStack();
    }
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

void game::processUndo() {
    if (!undoStack.empty()) {
        action prev_action = undoStack.top();
        undoStack.pop();
        int xCoord = prev_action.xCoord;
        int yCoord = prev_action.yCoord;

        cell curr_cell = grid[yCoord][xCoord];

        action new_action {curr_cell.getCurrNum(), xCoord, yCoord};
        redoStack.push(new_action);

        curr_cell.setCurrNum(prev_action.prevValue);
        grid[yCoord][xCoord] = curr_cell;
    }
}

void game::processRedo() {
    if (!redoStack.empty()) {
        action prev_action = redoStack.top();
        redoStack.pop();
        int xCoord = prev_action.xCoord;
        int yCoord = prev_action.yCoord;

        cell curr_cell = grid[yCoord][xCoord];

        action new_action {curr_cell.getCurrNum(), xCoord, yCoord};
        undoStack.push(new_action);

        curr_cell.setCurrNum(prev_action.prevValue);
        grid[yCoord][xCoord] = curr_cell;
    }
}

void game::clearRedoStack() {
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void game::processFinish() {
    for (int i {0}; i < 9; ++i) {
        for (int j {0}; j < 9; ++j) {
            
            cell curr_cell = grid[i][j];
            curr_cell.setCurrNum(curr_cell.getAnsNum());
            grid[i][j] = curr_cell;
    
        }
    }
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