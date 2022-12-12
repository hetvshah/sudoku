// #include <fstream>
// #include <limits>
#include "game.hpp"

#include <iostream>
#include <sstream>
#include <memory>
#include <string.h>

using namespace std;

int main () {
    string s;
    auto board {game(0)};
    bool activeGame = false;

    cout << "\nWelcome to Sudoku! Possible commands: \n";
    cout << "- new {difficulty}: generate a puzzle with difficulty options of easy (default), medium, or hard\n";
    cout << "- put {x} {y} {value}: put value at position (x, y)\n";
    cout << "- remove {x} {y}: remove value at position (x, y) if it's changeable\n";
    cout << "- check: check progress of guesses so far\n";
    cout << "- undo: undo the last move\n";
    cout << "- redo: redo the last undo-ed move\n";
    cout << "- hint: get a hint on the next move or an incorrect move you've made\n";
    cout << "- finish: end the game and get the solution to the puzzle\n\n";

    while (getline(cin, s)) {
        istringstream iss {s};
        string command;
        string difficulty;

        iss >> command;
        
        if (command == "new") {
            iss >> difficulty;

            if (difficulty == "easy") {
                board = game(0);
            } else if (difficulty == "medium") {
                board = game(1);
            } else if (difficulty == "hard") {
                board = game(2);
            } else {
                continue;
            }

            activeGame = true;
            cout << board;
        } else if (activeGame) {
            if (command == "put") {
                int x, y, num;
                iss >> x;
                iss >> y;
                iss >> num;

                if (board.processPut(y, x, num) == 1) {
                    cout << board;
                    cout << "You won!\n";
                    activeGame = false;
                } else {
                    cout << board;
                }
            } else if (command == "remove") {
                int x, y;
                iss >> x;
                iss >> y;
                board.processRemove(y, x);
                cout << board;
            } else if (command == "check") {
                board.processCheck();
            } else if (command == "undo") {
                board.processUndo();
                cout << board;
            } else if (command == "redo") {
                board.processRedo();
                cout << board;
            } else if (command == "hint") {
                board.processHint();
            } else if (command == "finish") {
                board.processFinish();
                activeGame = false;
                cout << board;
            }
        }
    }
}