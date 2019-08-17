#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
 //Copy of the start point values for indexing
 int w = png.width();
 //2d vector for keeping track of marked values; initialized to 0, changed to 1 when marked
 vector<int> marked(png.width()*png.height(), 0);

 stack<Point> s;
 s.push(start);

while( s.empty() == 0 ){

    Point current = s.top();
    s.pop();    
    if(marked[current.y*w + current.x] == 0 && calculateDelta(png.getPixel(start.x, start.y), png.getPixel(current.x, current.y)) < tolerance){
      marked[current.y*w + current.x] = 1;
      itr.points.push_back(current);
      copyPoints.push_back(current);

      //Right
      if( current.x+1 < (png.width())){
	s.push(Point(current.x+1, current.y));
      }
      //Bottom
      if( (current.y+1) < (png.height())){
	s.push(Point(current.x, current.y+1));
      }
      //Left
      if( current.x >= 1 ){
    	s.push(Point(current.x-1, current.y));
      }
      //Top
      if( current.y >= 1 ){
    	s.push(Point(current.x, current.y-1));
      }
   }
 }
}


/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  //How this is called:   REQUIRE( *(dfs.begin()) == startPoint );
  return ImageTraversal::Iterator(itr.points, 0);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */

  return ImageTraversal::Iterator(itr.points, itr.points.size());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  itr.points.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point p = itr.points[itr.val];
  itr.points.erase(itr.points.begin()+itr.val);
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return itr.points[itr.val];
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return itr.points.empty();
}
