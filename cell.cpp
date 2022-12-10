#include "cell.hpp"

cell::cell() {
    currNum = 0;
    isChangable = true;
};

std::ostream& operator<< (std::ostream & o, const cell & c){
    if (c.currNum == 0)
        o << ".";
    else {
        o << c.currNum;
    } 
        
    return o;
}

int cell::getCurrNum() {
    return currNum;
}

int cell::getAnsNum() {
    return ansNum;
}

void cell::setCurrNum(int num) {
    this->currNum = num; 
}

void cell::setAnsNum(int num) {
    this->ansNum = num;
}

bool cell::getIsChangeable() {
    return isChangable;
}

void cell::setIsChangeable(bool change) {
    this->isChangable = change;
}

bool cell::isCorrect() {
    return currNum == ansNum;
}