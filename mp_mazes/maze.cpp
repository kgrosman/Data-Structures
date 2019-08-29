#include "maze.h"

#include <cstdlib>      /* rand() */

#include <iostream>     /* debugging - delete */

#include <ctime>        /* time */

SquareMaze::SquareMaze() {
    // create an empty maze
    width = 0;
    height = 0;

    // there are no cells, so these indices are invalid
    startIdx = -1;
    endIdx = -1;

    //set random seed to time
    srand(time(NULL));
}

void SquareMaze::makeMaze(int width, int height) {
    // TODO: eventually set startIdx and endIdx

    // update dimensions
    this->width  = width;
    this->height = height;

    cells.clear();
    cells.resize(width * height);

    // refresh dsets
    dsets.clear();

    // each in its own set to start with
    dsets.addelements(width * height);

    for (int i = 0; i < (width * height); i++) {
        // set walls
        cells.at(i).rWall = true;
        cells.at(i).dWall = true;
    }
    
        if (width > 0 && height > 0) {
        startIdx = 0;
    }

    
    

    
    //we order all of the cells randomly, then for each cell,
    //in order, we randomly pick right or down. If there is a valid (removable)
    //wall in that direction and removing it wouldn't make a cycle, we do so.
    
    std::vector<int> permutedCells;
    for (int i = 0; i < width * height; i++) {
        permutedCells.push_back(i);
    }
    std::random_shuffle(permutedCells.begin(), permutedCells.end());


    for (int k : permutedCells) {
        Cell& cell = cells[k];
        int p = rand() % 2;

        int neighborX = k % width;
        int neighborY = k / width + 1;
        if (neighborX < 0 || neighborX >= width) {
            continue;
        }
        if (neighborY < 0 || neighborY >= width) {
            continue;
        }
        if (!inactive.empty()) {
        if (inactive.find(transform(k % width, k / width)) != inactive.end()) {
            continue;
            
        }
        if (inactive.find(transform(neighborX, neighborY)) != inactive.end()) {
            continue;
        }
        }

        if (dsets.find(k) != dsets.find(transform(neighborX, neighborY))) {
            setWall(k % width, k / width, DOWN, false);
        }

        //int neighborX = k % width + 1;
        //int neighborY = k / width;
        neighborX = k % width + 1;
        neighborY = k / width;
        if (neighborX < 0 || neighborX >= width) {
            continue;
        }
        if (neighborY < 0 || neighborY >= width) {
            continue;
        }
        if (!inactive.empty()) {
        if (inactive.find(transform(k % width, k / width)) != inactive.end()) {
            continue;
        }
        if (inactive.find(transform(neighborX, neighborY)) != inactive.end()) {
            continue;
        }
        }
        if (dsets.find(k) != dsets.find(transform(neighborX, neighborY))) {
            setWall(k % width, k / width, RIGHT, false);
        }
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    // if left or up, go to other node and set that node's down or right
    // appropriately
    // also do bounds checking, etc.
    // modify these vals in the if statements if needed
    //We set (x,y) to be the point whose right or down wall we
    //want to modify and (neighborX, neighborY) is the neigbor of (x,y) such
    //that the wall between neighbor and (x,y) is the one we are modifying.
    int neighborX;
    int neighborY;

    if (dir == UP) {
        neighborX = x;
        neighborY = y;
        y -= 1;
    } else if (dir == LEFT) {
        neighborX = x;
        neighborY = y;
        x -= 1;
    } else if (dir == RIGHT) {
        neighborX = x + 1;
        neighborY = y;
    } else if (dir == DOWN) {
        neighborX = x;
        neighborY = y + 1;
    } else {
        return;
    }
        
    int idxToSet = transform(x, y);
    
    //If either cell on the side of the wall being modified is out of
    //bounds, do nothing. Otherwise we should be modifying a valid wall
    
    if (x < 0 || x >= width) {
        return;
    }
    if (y < 0 || y >= height) {
        return;
    }
    
    if (neighborX < 0 || neighborX >= width) {
        return;
    }
    if (neighborY < 0 || neighborY >= width) {
        return;
    }


    if (dir == RIGHT || dir == LEFT) {
        cells[idxToSet].rWall = exists;
    } else if (dir == UP || dir == DOWN) {
        cells[idxToSet].dWall = exists;
    }
    
    //If a wall is removed and the cells on either side were not in the same
    //set, join the two sets 
    if (exists == false && dsets.find(transform(x,y)) != dsets.find(transform( neighborX, neighborY))) {
        dsets.setunion(transform(x,y), transform(neighborX, neighborY));
    }

}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    int neighborX;
    int neighborY;

    if (dir == UP) {
        neighborX = x;
        neighborY = y;
        y -= 1;
    } else if (dir == LEFT) {
        neighborX = x;
        neighborY = y;
        x -= 1;
    } else if (dir == RIGHT) {
        neighborX = x + 1;
        neighborY = y;
    } else if (dir == DOWN) {
        neighborX = x;
        neighborY = y + 1;
    } else {
        return false;
    }
    

    int idxToSet = transform(x, y);

    //now if wall is invalid, return false

    if (x < 0 || x >= width) {
        return false;
    }
    if (y < 0 || y >= height) {
        return false;
    }
    if (neighborX < 0 || neighborX >= width) {
        return false;
    }
    if (neighborY < 0 || neighborY >= width) {
        return false;
    }

    //Otherwise, return whether there is no wall in between the two cells in
    //question
    
    if (dir == RIGHT || dir == LEFT) {
        return !cells[idxToSet].rWall;
    } else {
        return !cells[idxToSet].dWall;
    }

    return false;
}

std::vector<int> SquareMaze::solveMaze() {
    
    //holds directions - RIGHT, DOWN, LEFT, UP
    std::vector<int> path;
    
    isPath(path, 0, 0, 0, height - 1, 4); //4 is because we never made a move previously, so prevDir shouldnt be 0,1,2, or 3
    std::vector<int> longestPath = path;

    for (int i = 0; i < width; i++) {
        path.clear();
        isPath(path, 0, 0, i, height - 1, 4); 
        if (path.size() > longestPath.size()) {
            longestPath = path;
            endIdx = transform(i, height - 1); 
        }
    }
    soln = longestPath;
    return longestPath;
}

//Returns whether there is a  path from start to end and, if so, replaces "path"
//with the moves to solve the maze;
bool SquareMaze::isPath(std::vector<int>& path, int startX, int startY, int endX, int endY, int prevDir) {
    if (startX == endX && startY  == endY) {
        return true;
    }

    //If our last move was not to the right (so we dont go back where we were),
    //we can go left, and there is a valid path 
    if ((prevDir != RIGHT) && canTravel(startX, startY, LEFT) && isPath(path, startX - 1, startY, endX, endY, LEFT)) {
        path.insert(path.begin(), LEFT);
        return true;
    }
    if ((prevDir != LEFT) && canTravel(startX, startY, RIGHT) && isPath(path, startX + 1, startY, endX, endY, RIGHT)) {
        path.insert(path.begin(), RIGHT);
        return true;
    }
    if ((prevDir != UP) && canTravel(startX, startY, DOWN) && isPath(path, startX, startY + 1, endX, endY, DOWN)) {
        path.insert(path.begin(), DOWN);
        return true;
    }
    if ((prevDir != DOWN) && canTravel(startX, startY, UP) && isPath(path, startX, startY - 1, endX, endY, UP)) {
        path.insert(path.begin(), UP);
        return true;
    }

    return false;
}
PNG * SquareMaze::drawCreativeMaze() const {


    PNG * result = new PNG((width * 10) + 1, (height * 10) + 1);

    //blacken leftmost column and topmost row aside from entrance
    for (int y = 0; y < (int) result->height(); y++) {
        HSLAPixel & currPixel = result->getPixel(0, y);
        currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 1;
    }
    for (int x = 10; x < (int) result->width(); x++) {
        HSLAPixel & currPixel = result->getPixel(x, 0);
        currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 1;
    }

    //color in walls if applicable
    for (int idx = 0; idx < (int) cells.size(); idx++) {
        //get start coords
        std::pair<int, int> loc = transform(idx);
        int x = loc.first;
        int y = loc.second;

        if (!(inactive.find(idx) != inactive.end() && inactive.find(transform(x+1, y)) != inactive.end())) {
            if (cells.at(idx).rWall == true) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & currPixel = result->getPixel((x + 1) * 10, (y * 10) + k);
                    currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 1;
                }
            }
        } else {
            for (int k = 1; k <= 10; k++) {
                HSLAPixel & currPixel = result->getPixel((x + 1) * 10, (y * 10) + k);
                currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 0;
            }
        }
        

        if (!(inactive.find(idx) != inactive.end() && inactive.find(transform(x, y+1)) != inactive.end())) {
            if (cells.at(idx).dWall == true) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & currPixel = result->getPixel((x * 10) + k, (y + 1) * 10);
                    currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 1;
                }
            }
        } else {
            for (int k = 1; k <= 10; k++) {
                HSLAPixel & currPixel = result->getPixel((x * 10) + k, (y + 1) * 10);
                currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 0;
            }
        }
    }

    for (int k : inactive) {
        std::pair<int, int> loc = transform(k);

        for (int x = loc.first * 10 + 1; x < loc.first * 10 + 10; x++) {
            for (int y = loc.second * 10 + 1; y < loc.second * 10 + 10; y++) {
                HSLAPixel & currPixel = result -> getPixel(x, y);
                currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 0;
            }
        }
    }

    return result;
}

PNG * SquareMaze::drawMaze() const {

    PNG * result = new PNG((width * 10) + 1, (height * 10) + 1);

    //blacken leftmost column and topmost row aside from entrance
    for (int y = 0; y < (int) result->height(); y++) {
        HSLAPixel & currPixel = result->getPixel(0, y);
        currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 1;
    }
    for (int x = 10; x < (int) result->width(); x++) {
        HSLAPixel & currPixel = result->getPixel(x, 0);
        currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 1;
    }

    //color in walls if applicable
    for (int idx = 0; idx < (int) cells.size(); idx++) {
        //get start coords
        std::pair<int, int> loc = transform(idx);
        int x = loc.first;
        int y = loc.second;

        if (cells.at(idx).rWall == true) {
            for (int k = 0; k <= 10; k++) {
                HSLAPixel & currPixel = result->getPixel((x + 1) * 10, (y * 10) + k);
                currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 1;
            }
        }

        if (cells.at(idx).dWall == true) {
            for (int k = 0; k <= 10; k++) {
                HSLAPixel & currPixel = result->getPixel((x * 10) + k, (y + 1) * 10);
                currPixel.h = 0; currPixel.s = 0; currPixel.l = 0; currPixel.a = 1;
            }
        }
    }

    
    return result;
}
PNG * SquareMaze::drawCreativeMazeWithSolution() {

    //start with incomplete maze as base
    PNG * result = drawCreativeMaze();
    


    //start at (5, 5)
    std::pair<int, int> curr_pt(5, 5);


    for (auto it = soln.begin(); it != soln.end(); it++) {

        //must make trail of 11 red pixels in current direction
        
        int dir = *it;
        
        //add one more pixel if last thing
        int AMT = 9;
        if ((it + 1) == soln.end()) {
            AMT += 1;
        }

        if (dir == UP) {
            for (int i = 0; i <= AMT; i++) {
                HSLAPixel & currPixel = result->getPixel(curr_pt.first, curr_pt.second);
                currPixel.h = 0; currPixel.s = 1; currPixel.l = 0.5; currPixel.a = 1;

                curr_pt.second--;
            }
        } else if (dir == LEFT) {
            for (int i = 0; i <= AMT; i++) {
                HSLAPixel & currPixel = result->getPixel(curr_pt.first, curr_pt.second);
                currPixel.h = 0; currPixel.s = 1; currPixel.l = 0.5; currPixel.a = 1;

                curr_pt.first--;
            }
        } else if (dir == RIGHT) {
            for (int i = 0; i <= AMT; i++) {
                HSLAPixel & currPixel = result->getPixel(curr_pt.first, curr_pt.second);
                currPixel.h = 0; currPixel.s = 1; currPixel.l = 0.5; currPixel.a = 1;

                curr_pt.first++;
            }
        } else if (dir == DOWN) {
            for (int i = 0; i <= AMT; i++) {
                HSLAPixel & currPixel = result->getPixel(curr_pt.first, curr_pt.second);
                currPixel.h = 0; currPixel.s = 1; currPixel.l = 0.5; currPixel.a = 1;

                curr_pt.second++;
            }
        } else {
            //error?
        }
    }

    //open destination wall
    std::pair<int, int> dest = transform(endIdx);

    std::cout << "endIdx = " << endIdx << std::endl;

    for (int k = 1; k < 10; k++) {
        std::cout << "x = " << (dest.first * 10) + k << ", y = " << (dest.second + 1) * 10 << std::endl;

        HSLAPixel & currPixel = result->getPixel((dest.first * 10) + k, (dest.second + 1) * 10);
        currPixel.h = 0; currPixel.s = 0; currPixel.l = 1; currPixel.a = 1;
    }


    return result;
}
PNG * SquareMaze::drawMazeWithSolution() {

    //start with incomplete maze as base
    PNG * result = drawMaze();
    


    //start at (5, 5)
    std::pair<int, int> curr_pt(5, 5);


    for (auto it = soln.begin(); it != soln.end(); it++) {

        //must make trail of 11 red pixels in current direction
        
        int dir = *it;
        
        //add one more pixel if last thing
        int AMT = 9;
        if ((it + 1) == soln.end()) {
            AMT += 1;
        }

        if (dir == UP) {
            for (int i = 0; i <= AMT; i++) {
                HSLAPixel & currPixel = result->getPixel(curr_pt.first, curr_pt.second);
                currPixel.h = 0; currPixel.s = 1; currPixel.l = 0.5; currPixel.a = 1;

                curr_pt.second--;
            }
        } else if (dir == LEFT) {
            for (int i = 0; i <= AMT; i++) {
                HSLAPixel & currPixel = result->getPixel(curr_pt.first, curr_pt.second);
                currPixel.h = 0; currPixel.s = 1; currPixel.l = 0.5; currPixel.a = 1;

                curr_pt.first--;
            }
        } else if (dir == RIGHT) {
            for (int i = 0; i <= AMT; i++) {
                HSLAPixel & currPixel = result->getPixel(curr_pt.first, curr_pt.second);
                currPixel.h = 0; currPixel.s = 1; currPixel.l = 0.5; currPixel.a = 1;

                curr_pt.first++;
            }
        } else if (dir == DOWN) {
            for (int i = 0; i <= AMT; i++) {
                HSLAPixel & currPixel = result->getPixel(curr_pt.first, curr_pt.second);
                currPixel.h = 0; currPixel.s = 1; currPixel.l = 0.5; currPixel.a = 1;

                curr_pt.second++;
            }
        } else {
            //error
        }
    }

    //open destination wall
    std::pair<int, int> dest = transform(endIdx);

    std::cout << "endIdx = " << endIdx << std::endl;

    for (int k = 1; k < 10; k++) {
        std::cout << "x = " << (dest.first * 10) + k << ", y = " << (dest.second + 1) * 10 << std::endl;

        HSLAPixel & currPixel = result->getPixel((dest.first * 10) + k, (dest.second + 1) * 10);
        currPixel.h = 0; currPixel.s = 0; currPixel.l = 1; currPixel.a = 1;
    }


    return result;
}
