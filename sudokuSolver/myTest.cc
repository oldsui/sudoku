
#include <string>

#include "BackTrackGrid.h"

int main() {

    std::string testInput = "080900020900060008046002190005010003070208060600040700034700950700080002060004030";

    BackTrackGrid *myGrid = new BackTrackGrid(testInput);

    printf("Input:\n");
    myGrid->print(2);


    if (myGrid->solve()) {
        printf("Solved!\n");
        printf("%d nodes expanded\n", myGrid->numNodesExpanded);
        myGrid->print(2);
    } else {
        printf("Not solved...\n");
    }



    return 0;
}