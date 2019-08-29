#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    
    SquareMaze m;
    for (int i = -10; i <= 10; i++) {
        for (int j = -10; j <= 10; j++) {
             m.inactive.insert(1275 + i + 50 * j);
        }
    }
    
    m.makeMaze(50, 50);

    std::cout << "MakeMaze complete" << std::endl;

    std::vector<int> sol = m.solveMaze();
    std::cout << "solveMaze complete" << std::endl;

    cs225::PNG* solved = m.drawCreativeMazeWithSolution();
    solved->writeToFile("creative.png");
    delete solved;
    std::cout << "drawMazeWithSolution complete" << std::endl;

    return 0;
}
