#ifndef CELL_HPP
#define CELL_HPP

#include <memory>
#include <iostream>


class cell
{
public:
    int currNum; // 0 - 9, if 0 then covered, o.w. show guess
    int ansNum;
    virtual void print(std::ostream& o) const = 0;

    virtual ~cell() = 0;

    friend std::ostream & operator<<(std::ostream & os, const cell & c);
};

#endif
