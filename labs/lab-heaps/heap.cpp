
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cmath>

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    	return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
	return currentIdx*2 +1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child

    //Only check left because right implies left anyways
    if (leftChild(currentIdx) < _elems.size())	return true;
    else					return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    size_t ret = 0;

    //If only one child exists, it will be the left child so return left
    if (rightChild(currentIdx) > _elems.size()-1)		ret = leftChild(currentIdx);
    //Will not be called on no children, so both children must exist..
    else
      higherPriority(_elems[rightChild(currentIdx)], _elems[leftChild(currentIdx)]) ?
	  ret = rightChild(currentIdx)
 	  :
	  ret = leftChild(currentIdx);

  return ret;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.

    size_t child;
    size_t c = currentIdx;

    while (hasAChild(c)){
	child = maxPriorityChild(c);

	if (higherPriority(_elems[c], _elems[child])) 	return;
	std::swap(_elems[c], _elems[child]);
	c = child;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    
	//Fill 0 spot with anything so we start from 1
	_elems.push_back(0);
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
 
    _elems.push_back(0);
    for (int i = 0; i < (int)elems.size(); i++)
	_elems.push_back(elems[i]);

    for (int j = parent((int)_elems.size()-1); j >= 1; j--)
	heapifyDown(j);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    int size = _elems.size();
    T elem = T();

	elem = _elems[1];
	_elems[1] = _elems[size-1];
	_elems.pop_back();
	heapifyDown(1);

    return elem;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems.at(1);
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if (_elems.size() == 1) 	return true;
    else			return false;
    //return (_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
