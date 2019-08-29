/**
 * @file DFS.h
 */

#pragma once
#include <unordered_set>
#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <set>
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:

  DFS(PNG & p, Point s, double t);
  ~DFS();
  
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
   std::stack<Point> points;
   std::vector<std::vector<bool>>* visited;
    PNG& png;
    Point start;
    double tolerance;
  //	/** @todo [Part 1] */
    
};
