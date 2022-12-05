#ifndef GAME_HPP
#define GAME_HPP

#include "cell.hpp"

#include <iostream>
#include <memory>

class game
{
    private:
        int difficulty; // 0 = easy, 1 = medium, 2 = hard
        cell grid[9][9];
    public:
        game(int);
        int processPut(int xCoord, int yCoord, int num);
        int processRemove(int xCoord, int yCoord);
        void processHint();
        int processUndo();
        int processRedo();
        int processGuess(int xCoord, int yCoord);
        void uncoverAll();
        bool isWon();
        friend std::ostream & operator<<(std::ostream & os, const game & g);
};

#endif