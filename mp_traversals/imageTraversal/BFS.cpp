#include <iterator>
#include <cmath>
#include <list>
#include <unordered_set>
#include <queue>
#include <stack>
#include <vector>

#include <set>
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(PNG & p, Point  s, double t) : png(p), start(s), tolerance(t) {
    points.push(s);
    visited = new std::vector<std::vector<bool>>(png.width(), std::vector<bool>(png.height()));
}

BFS::~BFS() {
    delete visited;
}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  
  BFS* im = new BFS(png, start, tolerance);
  ImageTraversal::Iterator ans(png, im, start, tolerance);
  return ans;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  BFS* im = new BFS(png, start, tolerance);
  im -> pop();
  ImageTraversal::Iterator ans(png, im, start, tolerance);
  return ans;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
    points.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
 Point ans = points.front();
 points.pop();
 return ans;
}


/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
    return points.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return points.empty();
}
bool BFS::fvisited(unsigned x, unsigned y) {
    return (*visited)[x][y];
}
void BFS::visiting(Point p) {
    (*visited)[p.x][p.y] = true;
}

std::vector<std::vector<bool>>* BFS::allvisited() {
    return visited;
}
