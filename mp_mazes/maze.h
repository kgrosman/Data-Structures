#ifndef MAZE_H
#define MAZE_H

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "dsets.h"

#include <vector>
#include <set>

using namespace cs225;

class SquareMaze {
private:
    std::vector<int> soln;
    struct Cell {
        //can be used to keep track of whether active, etc. and also for
        //adding color to creative part
        //inactive is transparent, active is anything else
        HSLAPixel color;

        // need to keep track of only rightward and downward walls
        bool rWall;
        bool dWall;

        Cell() {
            color = HSLAPixel(0, 0, 1, 1);
        }
        Cell(bool active) {
            if (active) {
                color = HSLAPixel(0, 0, 1, 1);
            } else {
                color = HSLAPixel(0, 0, 0, 0);
            }
        }
        Cell(HSLAPixel pixel) {
            color = pixel; 
        }
    };
    std::vector<Cell> cells;

    // star of the show
    DisjointSets dsets;

    // store maze dimensions, since using 1D cell vector
    int width;
    int height;

    // 1D indices of the start and end of the maze
    int startIdx;
    int endIdx;

    // 2D coords to internal 1D indices
    int transform(int x, int y) const {
        return (y * width) + x;
    }

    // Internal 1D indices to 2D coords
    std::pair<int, int> transform(int idx) const {
        return std::pair<int, int>((idx % width), (idx / width));
    }

    bool isPath(std::vector<int>& path, int startX, int startY, int endX, int endY, int prevDir);

public:
    enum directions { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };

    SquareMaze();

    void makeMaze(int width, int height);
    void setWall(int x, int y, int dir, bool exists);
    bool canTravel(int x, int y, int dir) const;
    std::vector<int> solveMaze();

    std::set<int> inactive;

    // will assume that people will free the stuff they get back from this
    PNG * drawMaze() const;
    PNG * drawCreativeMaze() const;
    PNG * drawMazeWithSolution();
    PNG * drawCreativeMazeWithSolution();
};

#endif
