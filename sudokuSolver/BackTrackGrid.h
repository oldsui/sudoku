
#ifndef SUDOKUSOLVER_BACKTRACKGRID_H
#define SUDOKUSOLVER_BACKTRACKGRID_H

#include "Grid.h"

class BackTrackGrid: public Grid {

public:
    BackTrackGrid(std::string input): Grid(input) {

    };


    // override
    bool solve() {
        return solveFrom(0, 0);
    }

    // DFS back track: left to right, top to bottom
    bool solveFrom(int row, int col) {

        // end condition
        if (row == GRID_DIM) {
            return true;
        }

        // skip pre-filled cells
        if(cells[row][col]->preFilled)
            return solveFrom(col == GRID_DIM - 1 ? row + 1 : row, col == GRID_DIM - 1 ? 0 : col + 1);

        numNodesExpanded++;

        // naively try 1 ~ 9
        for(int val = 1; val <= GRID_DIM; val++)

            if(isValid(row, col, val)) {            // if this cell can be assigned to val

                cells[row][col]->value = val;
                numSolvedCell++;


                // try from the next cell
                if(solveFrom(col == GRID_DIM - 1 ? row + 1 : row, col == GRID_DIM - 1 ? 0 : col + 1))
                    return true;

                // revert to previous state
                cells[row][col]->value = Cell::EMPTY_VALUE;
                numSolvedCell--;
            }

        return false;
    }

};

#endif //SUDOKUSOLVER_BACKTRACKGRID_H
