#include <iterator>
#include <unordered_set>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(PNG & p, Point  s, double t) :  png(p), start(s), tolerance(t) {
    visited = new std::vector<std::vector<bool>>(png.width(), std::vector<bool>(png.height()));
    points.push(s);
}

DFS::~DFS() {
    delete visited;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS* im = new DFS(png, start, tolerance);
  ImageTraversal::Iterator ans(png, im , start, tolerance);
  return ans;
  // ImageTraversal* ans = new ImageTraversal();

}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  DFS* im = new DFS(png, start, tolerance);
  im -> pop();
  ImageTraversal::Iterator ans(png, im, start, tolerance);
  return ans;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  points.push(point);

  
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
    
  Point ans = points.top();
  points.pop();
  return ans;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return points.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return points.empty();
}
bool DFS::fvisited(unsigned x, unsigned y) {
    return (*visited)[x][y];
}

void DFS::visiting(Point p) {
    (*visited)[p.x][p.y] = true;
}
std::vector<std::vector<bool>>* DFS::allvisited() {
    return visited;
}
