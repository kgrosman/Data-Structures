#include <cmath>
#include <iterator>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */

double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

ImageTraversal::~ImageTraversal() {
}

    
ImageTraversal::Iterator::~Iterator() {
    delete traversal;
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(PNG & p, ImageTraversal * t, Point & s, double to) :  traversal(t), png(p), start(s), tolerance(to) {


}



/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point p = traversal -> pop();
  traversal -> visiting(p);

  
  unsigned ri = p.x + 1;
  unsigned dow = p.y + 1;
  unsigned le = p.x - 1;
  unsigned up = p.y - 1;
  Point r(ri, p.y);
  Point d(p.x, dow);
  Point l(le, p.y);
  Point u(p.x, up);
 
 
  if (r.x < png.width() && r.y < png.height() && calculateDelta(png.getPixel(r.x, r.y), png.getPixel(start.x, start.y)) < tolerance){
         	traversal -> add(r);
  }     
  if (d.x < png.width() && d.y < png.height() && calculateDelta(png.getPixel(d.x, d.y), png.getPixel(start.x, start.y)) < tolerance){
           traversal -> add(d);
  }
  if (l.x < png.width() && l.y < png.height() && calculateDelta(png.getPixel(l.x, l.y), png.getPixel(start.x, start.y)) < tolerance){
           traversal -> add(l);
  }

  if (u.x < png.width() && u.y < png.height() && calculateDelta(png.getPixel(u.x, u.y), png.getPixel(start.x, start.y)) < tolerance){
           traversal -> add(u);
  }

    
  

  
bool done = false;
while(!(traversal -> empty()) && !done) {
    done = true;
    Point topElem = traversal -> peek();
    if (traversal -> fvisited(topElem.x, topElem.y)) {
            traversal -> pop();
            done = false;
        
    }
}


    
     return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return traversal -> peek(); 
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (this -> traversal -> empty() && other.traversal -> empty()) {
      return false;
  }
  if (this -> traversal -> empty() || other.traversal -> empty()) {
      return true;
  }
  if (this -> traversal -> allvisited() != other.traversal -> allvisited()){
      return true;
  }
  return false;
  //return ((this -> traversal -> peek()) != (other.traversal -> peek()));
  
}

