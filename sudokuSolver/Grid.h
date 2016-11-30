
#ifndef SUDOKUSOLVER_GRID_H
#define SUDOKUSOLVER_GRID_H

#include "Cell.h"
#include <string>
#include <cassert>
#include <vector>


// base class, to be inherited by different methods, which implement solve()
class Grid {

public:
    static const int GRID_DIM = 9;
    static const int SUBGRID_DIM = 3;
    static const int TOTAL_CELL = GRID_DIM * GRID_DIM;

    int numNodesExpanded;
    int numSolvedCell;

    Cell* cells[GRID_DIM][GRID_DIM];

    std::vector<Cell*> frontier;


    //virtual function, to be overridden by different versions
    virtual bool solve() {
        printf("Error! Shouldn't reach here!\n");
        return false;
    }

    // Constructor
    Grid(std::string input) {
        assert(input.length() == GRID_DIM * GRID_DIM);      // make sure string length is 81

        numSolvedCell = 0;
        numNodesExpanded = 0;

        // initialize 81 cells
        for (int i = 0; i < GRID_DIM; i++) {
            for (int j = 0; j < GRID_DIM; j++) {
                char curChar = input.at(i * GRID_DIM + j);
                cells[i][j] = new Cell(curChar - '0', i, j);
                if (curChar != '0') {
                    numSolvedCell++;
                }
            }
        }

        // add to-be-assigned cells into frontier
        for(int i = 0; i < GRID_DIM; i++) {
            for (int j = 0; j < GRID_DIM; j++) {
                bool shouldInsert = !cells[i][j]->preFilled;
                if (shouldInsert) {
                    frontier.push_back(cells[i][j]);
                }
            }
        }


        // reduce domains of pre-filled cells' conflicting cells
        std::vector<Cell*> dummyVector;
        for (int i = 0; i < GRID_DIM; i++) {
            for (int j = 0; j < GRID_DIM; j++) {
                if(!assignCell(cells[i][j], cells[i][j]->value, dummyVector)) {
                    printf("Invalid input grid!\n");
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



    // no need to check if val is from cell.allowedValues
    bool assignCell(Cell* curCell, int val, std::vector<Cell*> &modifiedCells) {

        curCell->value = val;
        int row = curCell->rowNum;
        int col = curCell->columnNum;
        // reduce domain of cells in the same column
        for(int i = 0; i < GRID_DIM; i++) {
            if(i == row) {
                continue;
            }
            Cell* curCell = cells[i][col];
            if (curCell->allowedValues.erase(val) > 0) {
                modifiedCells.push_back(curCell);
                if (curCell->allowedValues.size() == 0) {
                    for (int i = 0; i < modifiedCells.size(); i++) {
                        modifiedCells[i]->allowedValues.insert(val);
                    }
                    return false;
                }
            }
        }

        // reduce domain of cells in the same row
        for(int i = 0; i < GRID_DIM; i++) {
            if(i == col) {
                continue;
            }
            Cell* curCell = cells[row][i];
            if (curCell->allowedValues.erase(val) > 0) {
                modifiedCells.push_back(curCell);
                if (curCell->allowedValues.size() == 0) {
                    for (int i = 0; i < modifiedCells.size(); i++) {
                        modifiedCells[i]->allowedValues.insert(val);
                    }
                    return false;
                }
            }
        }

        // reduce domain of cells in the same sub-grid
        int m = (row / SUBGRID_DIM) * SUBGRID_DIM;
        int n = (col / SUBGRID_DIM) * SUBGRID_DIM;
        for(int i = m; i < m + SUBGRID_DIM; i++) {
            for (int j = n; j < n + SUBGRID_DIM; j++) {
                if (i == row || j == col){                      // skip examined cells
                    continue;
                }
                Cell* curCell = cells[i][j];
                if (curCell->allowedValues.erase(val) > 0) {
                    modifiedCells.push_back(curCell);
                    if (curCell->allowedValues.size() == 0) {
                        for (int i = 0; i < modifiedCells.size(); i++) {
                            modifiedCells[i]->allowedValues.insert(val);
                        }
                        return false;
                    }
                }
            }
        }

        return true;
    }



    void print() {
        // print each line
        for (int i = 0; i < GRID_DIM; i++) {
            for (int j = 0; j < GRID_DIM; j++) {
                cells[i][j]->print();
                if ((j + 1) % SUBGRID_DIM == 0) {
                    printf("|");
                }
            }
            if ((i + 1) % SUBGRID_DIM == 0) {
                printf("\n------+------+------");
            }
            printf("\n");
        }
        printf("\n");
    }

};


#endif //SUDOKUSOLVER_GRID_H
