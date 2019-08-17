/**
 * @file ImageTraversal.h
 */
#ifndef IMAGETRAVERSAL_H
#define IMAGETRAVERSAL_H

#include <iterator>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"
#include <queue>

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  deque<Point> copyPoints;
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    Iterator(deque<Point>, unsigned int);

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);

    /** @todo [Part 1] */
    /** add member functions if neccesary*/
  //  vector<double> hues;
    deque<Point> points;
    unsigned int val;

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
  };  

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  

private:
};




#endif
