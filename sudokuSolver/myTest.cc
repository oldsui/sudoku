
#include <fstream>
#include <string>
#include <chrono>
#include <vector>

#include "BackTrackGrid.h"
#include "MRVGrid.h"

using namespace std;

int main() {

    // select input

    //std::string testInput = "080900020900060008046002190005010003070208060600040700034700950700080002060004030";
    //std::string testInput = "002008500640100908305009040721004050004000200090300784060500807108003062009200100";

    // easy
    //std::string testInput = "064003851200000960005800000020041090036050140010260030000004200058000009642100580";

    // medium 1
    //std::string testInput = "720500006095160000000700904210900003009000400600004091302006000000053620900001045";

    // medium 2
    //std::string testInput = "000800042006050000000142006080004035050673010320500070400761000000020400190005000";

    // hard 1
    //std::string testInput = "040050000010080020060000104100300900007649200002001008305000090020090070000060050";

    // hard 2
    //std::string testInput = "095010006070039000000007053018000000400070001000000580840700000000260040500080720";

    // evil 1
    //std::string testInput = "009800200040001000100720090400000060300010005070000004050037006000100050004005900";

    // evil 2
    //std::string testInput = "800000002930500070000001500000040060006915400090030000008600000040007018600000007";

    // evil 3
    //std::string testInput = "420700000000000001601000508000065007700020009100430000203000806900000000000004072";


    vector<long long> times;
    vector<int> nodes;
    vector<int> backtracks;







    //printf("Input:\n");
    //myGrid->print();

    // select batch input test
    //std::ifstream file("puzzles_easy.txt");
    //std::ifstream file("puzzles_hard.txt");

    std::ifstream file("inputFile.txt");

    std::string testInput;
    while (std::getline(file, testInput)) {

        //printf("Current input is: %s\n", testInput.c_str());

        // select which method to be used:

        // 1. naive backtrack
        BackTrackGrid *myGrid = new BackTrackGrid(testInput);

        // 2. forward checking with minimum-remaining-values heuristic
        //MRVGrid *myGrid = new MRVGrid(testInput);



        auto start = std::chrono::high_resolution_clock::now();

        if (myGrid->solve()) {

            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

            printf("Solved in %lld microseconds!\n", microseconds);


            times.push_back(microseconds);
            nodes.push_back(myGrid->numNodesExpanded);
            backtracks.push_back(myGrid->numBacktrack);

            //printf("%d backtracks\n", myGrid->numBacktrack);
            //printf("%d nodes expanded\n", myGrid->numNodesExpanded);
            //myGrid->print();
        } else {
            printf("Not solved...\n");
        }

    }

    printf("execution time:\n");

    for (int i = 0; i < times.size(); i++) {
        printf("%lld, ", times[i]);
    }

    printf("\nnodes expanded:\n");

    for (int i = 0; i < nodes.size(); i++) {
        printf("%d,", nodes[i]);
    }

    printf("\nbacktracks:\n");

    for (int i = 0; i < backtracks.size(); i++) {
        printf("%d,", backtracks[i]);
    }
    
    return 0;
}
