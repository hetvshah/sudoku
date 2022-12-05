// #include <fstream>
// #include <limits>
#include "game.hpp"

#include <iostream>
#include <sstream>
#include <memory>
#include <string.h>

using namespace std;

// std::fstream& GotoLine(std::fstream& file, unsigned int num){
//     file.seekg(std::ios::beg);
//     for(int i=0; i < num - 1; ++i){
//         file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//     }
//     return file;
// }

// int main(){
//     using namespace std;
//     fstream file("bla.txt");

//     GotoLine(file, 8);

//     string line8;
//     file >> line8;

//     cout << line8;
//     cin.get();
//     return 0;
// }

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
                    cout << "Winner winner chicken dinner!\n";
                    activeGame = false;
                } 
            }
        } else if (command == "remove") {
            if (activeGame) {
                int x, y;
                iss >> x;
                iss >> y;
                //TODO: handle casing for process remove
                board.processRemove(x, y);

            }
        } else if (command == "check") {
            
        } else if (command == "undo") {

        } else if (command == "redo") {
            
        } else if (command == "hint") {
            
        } else if (command == "finish") {}
    }
}