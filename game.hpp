#ifndef GAME_HPP
#define GAME_HPP

#include "cell.hpp"
#include "action.hpp"

#include <iostream>
#include <memory>
#include <stack>

class game
{
    private:
        int difficulty; // 0 = easy, 1 = medium, 2 = hard
        cell grid[9][9];
        std::stack<action> undoStack;
        std::stack<action> redoStack;
        
    public:
        game(int);
        int processPut(int xCoord, int yCoord, int num);
        void processRemove(int xCoord, int yCoord);
        void processHint();
        void processCheck();
        void processUndo();
        void processRedo();
        int processGuess(int xCoord, int yCoord);
        void processFinish();
        void clearRedoStack();
        bool isWon();
        friend std::ostream & operator<<(std::ostream & os, const game & g);
};

#endif