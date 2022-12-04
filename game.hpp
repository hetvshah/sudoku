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
    int processHit(int xCoord, int yCoord);
    int processHint();
    int processUndo();
    int processRedo();
    void uncoverAll();
    friend std::ostream & operator<<(std::ostream & os, const game & g);
};

#endif