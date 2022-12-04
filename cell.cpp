#include "cell.hpp"

cell::cell() {
    currNum = 0;
};

std::ostream& operator<< (std::ostream & o, const cell & c){
    if (cell.currNum == 0) //uncovered cell
        o << " " ;
    else 
        o << currNum;
}
