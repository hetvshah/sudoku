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
    // bool activeGame = false;
    auto board {game(0)};
    bool activeGame = false;

    while (getline(cin, s)) // terminate when EOF is received
    {
        istringstream iss {s};
        string command;
        string difficulty;

        iss >> command;
        
        if (command == "new") {
            activeGame = true;
            iss >> difficulty;

            if (difficulty == "easy") {
                board = game(0);
            } else if (difficulty == "medium") {
                board = game(1);
            } else if (difficulty == "hard") {
                board = game(2);
            } else {
                // throw error
            }

            

            cout << board;
        } else if (activeGame) {
            if (command == "put") {
                int x, y, num;
                iss >> x;
                iss >> y;
                iss >> num;

                if (board.processPut(y, x, num) == 1) {
                    cout << "You won!\n";
                    activeGame = false;
                } 
                cout << board;
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
                cout << board;
            }
        }
    }
}

// TODO:
// add stack of actions
// error check from main