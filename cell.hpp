#ifndef CELL_HPP
#define CELL_HPP

#include <memory>
#include <iostream>


class cell
{
    protected:
        int currNum;
        int ansNum;
        bool isChangable;
    public:
        cell();
        int getCurrNum();
        int getAnsNum();
        void setCurrNum(int num);
        void setAnsNum(int num);
        bool getIsChangeable();
        void setIsChangeable(bool change);
        bool isCorrect();
    //     int currNum; // 0 - 9, if 0 then covered, o.w. show guess
    //     int ansNum;
    // // virtual void print(std::ostream& o) const = 0;

    // virtual ~cell() = 0;

        friend std::ostream & operator<<(std::ostream & os, const cell & c);
};

#endif
