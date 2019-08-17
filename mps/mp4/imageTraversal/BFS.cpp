#include <iterator>
#include <cmath>
#include <list>
#include <queue>

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
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
 int w = png.width();
 //2d vector for keeping track of marked values; initialized to 0, changed to 1 when marked
 vector<int> marked(png.height()*png.width(), 0);

 queue<Point> q;
 q.push(start);

 //Continue until all pixels have been visited
 while( q.empty() == false ){

  Point current = q.front();

  if(marked[current.y*w+current.x] == 0 && calculateDelta(png.getPixel(start.x, start.y), png.getPixel(current.x,current.y)) < tolerance){

    //Right
    if( (current.x+1) < png.width()){
	q.push(Point(current.x+1, current.y));
    }
    //Bottom
    if( (current.y+1) < png.height() ){
	q.push(Point(current.x, current.y+1));
    }
    //Left
    if( current.x >= 1){
    	q.push(Point(current.x-1, current.y));
    }
    //Top
    if( (current.y) >= 1 ){
    	q.push(Point(current.x, current.y-1));
    }

  itr.points.push_back(q.front());
  copyPoints.push_back(q.front());
  marked[current.y*w+current.x] = 1;
  
  }
  q.pop();
 }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(itr.points, 0);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(itr.points, itr.points.size());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  itr.points.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point p = itr.points[itr.val];
  itr.points.erase(itr.points.begin()+itr.val);
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return itr.points[itr.val];
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return itr.points.empty();
}
