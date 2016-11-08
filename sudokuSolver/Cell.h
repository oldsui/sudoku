
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


    std::set<int> constraints;


    Cell(){};

    Cell(const int val, const int r, const int c) {
        this->preFilled = val != this->EMPTY_VALUE;
        this->value = val;
        this->rowNum = r;
        this->columnNum = c;
    }

    void print(int margin = 1) {
        printf("|");
        for (int i = 0; i < margin; i++) {
            printf("_");
        }
        printf("%d", this->value);
        for (int i = 0; i < margin; i++) {
            printf("_");
        }

        if (this->columnNum == 8) {
            printf("|");
        }
    };

};




#endif //SUDOKUSOLVER_CELL_H
