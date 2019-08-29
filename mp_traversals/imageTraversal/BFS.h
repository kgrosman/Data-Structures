/**
 * @file BFS.h
 */

#pragma once

#include <unordered_set>
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include <set>
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(PNG & p, Point  s, double t);
  ~BFS();

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  bool fvisited(unsigned x, unsigned y);
  void visiting(Point p);
  std::vector<std::vector<bool>>* allvisited();
private:
   std::queue<Point> points;
   std::vector<std::vector<bool>>* visited;
    PNG& png;
    Point start;
    double tolerance;
  /** @todo [Part 1] */

};
