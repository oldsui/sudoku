
#ifndef SUDOKUSOLVER_MVRGRID_H
#define SUDOKUSOLVER_MVRGRID_H

#include "Grid.h"


class MRVGrid: public Grid{

public:

    MRVGrid(std::string input): Grid(input) {
    };



    std::vector<Cell*>::iterator findNextCandidate() {
        std::vector<Cell*>::iterator res;
        int minSize = 10;
        std::vector<Cell*>::iterator it = frontier.begin();
        for (; it != frontier.end(); it++) {
            Cell *tmpCell = *it;
            int tmpSize = tmpCell->allowedValues.size();
            if (tmpSize < minSize) {
                res = it;
                minSize = tmpSize;
            }
        }
        return res;
    }


    // MRV
    bool solve() {
        // end condition
        if (frontier.size() == 0)
            return true;

        // find minimum-remaining-value variable
        std::vector<Cell*>::iterator curCell_itr = findNextCandidate();
        Cell* curCell = *curCell_itr;
        frontier.erase(curCell_itr);

        numSolvedCell++;
        this->numNodesExpanded++;

        std::set<int> possibleValues = curCell->allowedValues;

        for (std::set<int>::iterator it = possibleValues.begin(); it != possibleValues.end(); it++) {
            // try to assign the current value to this cell
            int curVal = *it;
            std::vector<Cell*> modifiedCells;

            if(!assignCell(curCell, curVal, modifiedCells))
                continue;

            numSolvedCell++;

            if (solve())
                return true;


            for (int i = 0; i < modifiedCells.size(); i++)
                modifiedCells[i]->allowedValues.insert(curVal);
        }
        curCell->value = 0;
        frontier.push_back(curCell);
        numBacktrack++;
        return false;
    }

};

#endif //SUDOKUSOLVER_MVRGRID_H