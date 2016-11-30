
#ifndef SUDOKUSOLVER_CELL_H
#define SUDOKUSOLVER_CELL_H

#include<set>

class Cell {

public:
    static const int EMPTY_VALUE = 0;

    bool preFilled;         // if it's fixed

    int value;                // value of this cell

    int rowNum;             // row number, i.e. y coordinate

    int columnNum;          // column number, i.e. x coordinate

    std::set<int> allowedValues;

    Cell() {
    };

    Cell(const int val, const int r, const int c) {

        for (int i = 1; i < 10; i++) {
            allowedValues.insert(i);
        }

        this->preFilled = val != this->EMPTY_VALUE;
        this->value = val;
        this->rowNum = r;
        this->columnNum = c;
    }


    void print() {
        printf("%d ", this->value);
    };

};

#endif //SUDOKUSOLVER_CELL_H
