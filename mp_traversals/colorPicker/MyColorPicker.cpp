#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker() {
    count = 0;
}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {

    HSLAPixel red(170, 100, 30, 1);
    HSLAPixel blue(245, 100, 32, 1);
  
  count++;
  if (count % 1000 < 500) {
      return blue;
  } else {
      return red;
  }
  
}
