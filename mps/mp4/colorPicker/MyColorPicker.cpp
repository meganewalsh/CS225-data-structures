#include "../cs225/HSLAPixel.h"
//#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <math.h>
using namespace cs225;

/**
 *  * RainbowColorPicker constructor
 *   */
MyColorPicker::MyColorPicker(double increment)
  : hue(0), increment(increment) { }

MyColorPicker2::MyColorPicker2(double increment)
  : hue(0), increment(increment) { }
/*
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  hue = 0.6*sqrt(x*x+y*y);
  HSLAPixel pixel(hue, 1, 0.5);
  increment++;

  return pixel;
}

HSLAPixel MyColorPicker2::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  hue = sqrt(x*y + x*y)+99;
  HSLAPixel pixel(hue, 1, 0.5);
  increment++;

  return pixel;
}
