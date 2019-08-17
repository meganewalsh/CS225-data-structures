/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{    /**
     * @todo Implement this function!
     */

  if (first[curDim] < second[curDim])		return true;
  else if (first[curDim] > second[curDim])	return false;

  else return (first < second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
  double curDist = 0;
  double potDist = 0;

  for (unsigned i = 0; i < Dim; i++)
     curDist += (currentBest[i]-target[i])*(currentBest[i]-target[i]);


  for (unsigned i = 0; i < Dim; i++)
     potDist += (potential[i]-target[i])*(potential[i]-target[i]);
//cout << currentBest << " vs " << potential << ":  " << curDist << " " << potDist << endl;
  if (curDist < potDist)		return false;
  else if (curDist > potDist)		return true;

  else return (potential < currentBest);
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
  vector<Point<Dim>> copyPoints = newPoints;
  root = NULL;
  if (copyPoints.size())	build(copyPoints, 0, copyPoints.size()-1, 0);

}

/**
 * This function acts as the recursive builder for the KDTree constructor above.
 * It calls the following helper functions: quickSelect and addToTree.
 */

template <int Dim>
void KDTree<Dim>::build(vector<Point<Dim>>& points, unsigned left, unsigned right, unsigned d){

  if (left > right)				return;
  unsigned median = (right+left)/2;

  points[median] = quickSelect(points, left, right, median, d);
  KDTreeNode* newNode = new KDTreeNode(points[median]);
  addToTree( newNode, root, 0);

  if (median > left)		build(points, left, median-1, (d+1)%Dim);
  if (median < right)		build(points, median+1, right, (d+1)%Dim);
}



/**
 *  This recursive function adds a given node to the current structure of the tree,
 *  and is a helper function for the build function above.
 */

template <int Dim>
void KDTree<Dim>::addToTree(KDTreeNode*& newNode, KDTreeNode*& root, unsigned d){

 if (root != NULL){
    if (smallerDimVal(newNode->point, root->point, d))		addToTree(newNode, root->left, (d+1)%Dim);
    else if (smallerDimVal(root->point, newNode->point, d))	addToTree(newNode, root->right, (d+1)%Dim);
 }
 else    root = newNode;

}


/**  This function returns the median element in the correct partition of
 *   our list of points. It is a helper function for the build function.
 */

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& points, unsigned left, unsigned right, unsigned median, unsigned d){

  if (left == right)	return points[left];

  unsigned pivotIndex = partition(points, left, right, median, d);

  if (median == pivotIndex)			return points[median];
  else if (median < pivotIndex)			return quickSelect(points, left, pivotIndex-1, median, d);
  else						return quickSelect(points, pivotIndex+1, right, median, d);
}


/**
 *  This function groups a list with indices left to right into two parts: those less
 *  than a certain element and those greater than or equal to the element. It is a
 *  helper function for the quickSelect function above.
 */

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& points, unsigned left, unsigned right, unsigned pivotIndex, unsigned d){

  Point<Dim> pivotValue = points[pivotIndex];
  std::swap( points[pivotIndex], points[right] );
  unsigned storeIndex = left;

  for (unsigned i = left; i < right; i++){
    if (points[i] == pivotValue || smallerDimVal(points[i], pivotValue, d)){
	std::swap( points[storeIndex], points[i] );
        storeIndex++;
    }
  }
  std::swap( points[right], points[storeIndex] );

return storeIndex;
}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  root = new KDTreeNode(other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  this->root = rhs.root;
  this->size = rhs.size;

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
 remove(root);
}


/**
 * This function is a recursive helper function for the
 * KDTree destructor above
 */
template <int Dim>
void KDTree<Dim>::remove(KDTreeNode* subroot){

  if (subroot){
      remove(subroot->left);
      remove(subroot->right);
      delete subroot;
  }
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    Point<Dim> point = Point<Dim>();
    bool firstLeaf = false;
    return recurseNN(query, root, 0, point, firstLeaf);
}


/**
 *  This function acts as the recursive helper function for the provided
 *  findNearestNeighbor function (above)
 */
template <int Dim>
Point<Dim> KDTree<Dim>::recurseNN(const Point<Dim>& target, KDTreeNode* subroot, unsigned D, Point<Dim>& bestPoint, bool& firstLeaf) const {

KDTreeNode* chosen = NULL;
KDTreeNode* notChosen = NULL;

  //Reached first leaf node. Mark as best. This block will only be executed ONCE
  //(for the first leaf that is encountered.
  if (subroot->left == NULL && subroot->right == NULL && !firstLeaf){ 
    bestPoint = subroot->point;
    firstLeaf = true;
  }
  else{
    //Based on dimension, check target against node in tree. Will determine
    //in which direction to traverse the tree.
    if (smallerDimVal(target, subroot->point, D) || subroot->right == NULL){
        if (subroot->left != NULL ){
	    chosen = subroot->left;
	    notChosen = subroot->right;
	}
    }
    if (!smallerDimVal(target, subroot->point, D) || subroot->left == NULL){
        if (subroot->right != NULL){
            chosen = subroot->right;
	    notChosen = subroot->left;
	}
    }
    //Will execute unless some kind of funky error occurred. It is important
    //to only recurse once as to return to the same line after recursion completes.
    if (chosen){
	recurseNN(target, chosen, (D+1)%Dim, bestPoint, firstLeaf);
    }
  }
  //Determines whether we have found a better point in the tree, or if we need
  //to recurse the opposite way that we came from
  if (findDistance(target, bestPoint) >= fabs(subroot->point[D] - target[D])){

      if (shouldReplace(target, bestPoint, subroot->point))
	bestPoint = subroot->point;

      if (notChosen) recurseNN(target, notChosen, (D+1)%Dim, bestPoint, firstLeaf);
  }

return bestPoint;
}

/**
 *   This function calculates the distance between the target point and the other
 *   provided point paramter. It returns a double in order to prevent rounding
 *   erors.
 * */

template <int Dim>
double KDTree<Dim>::findDistance(const Point<Dim>& target, const Point<Dim>& point) const{

  double distance = 0;

  for (unsigned i = 0; i < Dim; i++)
     distance += (target[i]-point[i])*(target[i]-point[i]);

return sqrt(distance);
}
