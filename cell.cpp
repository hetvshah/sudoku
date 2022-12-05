#include "cell.hpp"

cell::cell() {
    currNum = 0;
};

std::ostream& operator<< (std::ostream & o, const cell & c){
    if (c.currNum == 0) //uncovered cell
        o << " ";
    else 
        o << c.currNum;
    return o;
}

int cell::getCurrNum() {
    return currNum;
}

int cell::getAnsNum() {
    return ansNum;
}

void cell::setCurrNum(int num) {
    currNum = num; 
}

void cell::setAnsNum(int num) {
    ansNum = num;
}

bool cell::getIsChangeable() {
    return isChangable;
}

void cell::setIsChangeable(bool change) {
    isChangable = change;
}

bool cell::isCorrect() {
    return currNum == ansNum;
}