
#include <string>

#include "BackTrackGrid.h"
#include "MRVGrid.h"

int main() {

    // 32 prefilled cells
    std::string testInput = "080900020900060008046002190005010003070208060600040700034700950700080002060004030";

    //BackTrackGrid *myGrid = new BackTrackGrid(testInput);

    MRVGrid *myGrid = new MRVGrid(testInput);

    printf("Input:\n");
    myGrid->print();

    if (myGrid->solve()) {
        printf("Solved!\n");
        printf("%d nodes expanded\n", myGrid->numNodesExpanded);
        myGrid->print();
    } else {
        printf("Not solved...\n");
    }

    return 0;
}