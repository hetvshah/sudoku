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
        } else if (command == "put") {
            if (activeGame) {
                int x, y, num;
                iss >> x;
                iss >> y;
                iss >> num;
                if (board.processPut(x, y, num) == 1) {
                    cout << "You won!\n";
                    activeGame = false;
                } 
                cout << board;
            }
        } else if (command == "remove") {
            if (activeGame) {
                int x, y;
                iss >> x;
                iss >> y;
                // TODO: handle casing for process remove
                board.processRemove(x, y);
                cout << board;
            }
        } else if (command == "check") {
            if (activeGame) {
                board.processCheck();
            }
        } else if (command == "undo") {

        } else if (command == "redo") {
            
        } else if (command == "hint") {
            if (activeGame) {
                board.processHint();
            }
        } else if (command == "finish") {}
    }
}

// TODO:
// add stack of actions
// error check from main