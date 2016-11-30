
#include <string>
#include<chrono>

#include "BackTrackGrid.h"
#include "MRVGrid.h"

int main() {

    // 32 prefilled cells
    std::string testInput = "080900020900060008046002190005010003070208060600040700034700950700080002060004030";
    //std::string testInput = "002008500640100908305009040721004050004000200090300784060500807108003062009200100";


    BackTrackGrid *myGrid = new BackTrackGrid(testInput);

    //MRVGrid *myGrid = new MRVGrid(testInput);

    printf("Input:\n");
    myGrid->print();

    auto start = std::chrono::high_resolution_clock::now();

    if (myGrid->solve()) {

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

        printf("Solved in %lld microseconds!\n", microseconds);
        printf("%d nodes expanded\n", myGrid->numNodesExpanded);
        myGrid->print();
    } else {
        printf("Not solved...\n");
    }




    return 0;
}