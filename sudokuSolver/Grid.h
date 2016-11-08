
#ifndef SUDOKUSOLVER_GRID_H
#define SUDOKUSOLVER_GRID_H

#include "Cell.h"
#include <string>
#include <cassert>

// comparator used to sort cells inside constrainedCells
struct cellCmp {
    bool operator() (const Cell *c1, const Cell *c2) const {
        return c1->constraints.size() > c2->constraints.size();
    }
};

// base class, to be inherited by different methods, which implement solve()
class Grid {

public:
    static const int GRID_DIM = 9;
    static const int SUBGRID_DIM = 3;

    int numNodesExpanded;
    std::set<Cell*, cellCmp> constrainedCells;
    Cell* cells[GRID_DIM][GRID_DIM];

    //virtual bool solve()
    virtual bool solve() {
        return false;
    }

    // Constructor
    Grid(std::string input) {

        assert(input.length() == GRID_DIM * GRID_DIM);
        numNodesExpanded = 0;

        for (int i = 0; i < GRID_DIM; i++) {
            for (int j = 0; j < GRID_DIM; j++) {
                char curChar = input.at(i * GRID_DIM + j);
                cells[i][j] = new Cell(curChar - '0', i, j);
            }
        }
        for(int i = 0; i < GRID_DIM; i++) {
            for (int j = 0; j < GRID_DIM; j++) {
                if (!cells[i][j]->preFilled) {
                    constrainedCells.insert(cells[i][j]);
                }
            }
        }
    }

    // validate current cell at [row, col] with value = val
    bool isValid(int row, int col, int val) {

        // check duplicate on vertical line
        for(int i = 0; i < GRID_DIM; i++) {
            if(row != i && cells[i][col]->value == val) {
                return false;
            }
        }
        // check duplicate on horizontal line
        for (int i = 0; i < GRID_DIM; i++) {
            if (col != i && cells[row][i]->value == val) {
                return false;
            }
        }
        // validate sub grid
        int m = (row / SUBGRID_DIM) * SUBGRID_DIM;
        int n = (col / SUBGRID_DIM) * SUBGRID_DIM;
        for(int i = m; i < m + SUBGRID_DIM; i++) {
            for (int j = n; j < n + SUBGRID_DIM; j++) {
                if (i == row && j == col) {
                    continue;
                }
                if (cells[i][j]->value == val) {
                    return false;
                }
            }
        }
        return true;
    }

    void print(int margin = 1) {

        for (int i = 0; i < GRID_DIM; i++) {
            for (int j = 0; j < margin * 2; j++) {
                printf("_");
            }
            printf("__");
        }
        printf("\n");
        // print each line
        for (int i = 0; i < GRID_DIM; i++) {
            for (int j = 0; j < GRID_DIM; j++) {
                cells[i][j]->print(margin);
            }
            printf("\n");
        }
        printf("\n");
    }

};


#endif //SUDOKUSOLVER_GRID_H
