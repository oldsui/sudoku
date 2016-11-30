
#ifndef SUDOKUSOLVER_MVRGRID_H
#define SUDOKUSOLVER_MVRGRID_H

#include "Grid.h"


class MRVGrid: public Grid{

public:

    MRVGrid(std::string input): Grid(input) {
    };



    std::vector<Cell*>::iterator findNextCandidate() {
        std::vector<Cell*>::iterator res;
        int minSize = 100;
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
        if (frontier.size() == 0) {
            return true;
        }

        numNodesExpanded++;

        // find minimum-remaining-value variable
        std::vector<Cell*>::iterator curNodeItr = findNextCandidate();
        Cell* curNode = *curNodeItr;
        frontier.erase(curNodeItr);



        std::set<int> possibleValues = curNode->allowedValues;

        for (std::set<int>::iterator it = possibleValues.begin(); it != possibleValues.end(); it++) {
            // try to assign the current value to this cell
            int curVal = *it;
            std::vector<Cell*> modifiedCells;

            bool assignOK = assignCell(curNode, curVal, modifiedCells);
            if(!assignOK) {
                continue;
            }

            //printf("(%d, %d) := %d\n", curNode->rowNum, curNode->columnNum, curVal);
            numSolvedCell++;

            if (solve()) {
                return true;
            }

            // reset to the previous state
            curNode->value = 0;
            frontier.push_back(curNode);
            for (int i = 0; i < modifiedCells.size(); i++) {
                modifiedCells[i]->allowedValues.insert(curVal);
            }
        }

        return false;
    }

};

#endif //SUDOKUSOLVER_MVRGRID_H