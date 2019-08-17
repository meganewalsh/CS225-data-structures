/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
	clear();
	delete head_;
	delete tail_;
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode* current = head_;
  ListNode* temp;

  while (current != NULL){
	temp = current->next;
        delete current;
        current = temp;
        if (temp->next == NULL){
          delete current;
          break;
        }
        temp = temp->next;
  }
  head_ = NULL;
  tail_ = NULL;
}
/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);

  newNode->next = head_;
  head_ = newNode;
  newNode->prev = NULL;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
 if (head_ == NULL){
	head_ = newNode;
	newNode->next = NULL;
	newNode->prev = NULL;
  }
  else{
	tail_->next = newNode;
	newNode->prev = tail_;
	newNode->next = NULL;
  }
  tail_ = newNode;
  length_++;
}
/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
if ( startPoint == endPoint || head_ == NULL) return;

	  ListNode* saveEndPoint = endPoint;
	  ListNode* saveStartPoint = startPoint;

	  ListNode* OdummyNode = new ListNode();
	  ListNode* ZdummyNode = new ListNode();
	  ListNode* tail = head_;


		OdummyNode->next = head_;
		if (head_ != NULL) head_->prev = OdummyNode;
	    head_ = OdummyNode;
	    OdummyNode->prev = NULL;

	    while (tail->next != NULL){
	    	tail = tail->next;
	    }
	    tail->next = ZdummyNode;
	    ZdummyNode->prev = tail;
	    ZdummyNode->next = NULL;
	    tail = ZdummyNode;


  ListNode* startPointPrev = saveStartPoint->prev;
  ListNode* endPointNext = saveEndPoint->next;

  startPointPrev->next = saveEndPoint;

  ListNode* current = saveEndPoint;
    while( current->prev != startPointPrev ){
    	current->next = current->prev;
    	current = current->next;
    }

    current->next = endPointNext;

    current = saveEndPoint;
    saveEndPoint->prev = startPointPrev;
    while( current != endPointNext){
    	current->next->prev = current;
    	current = current->next;
    }


    head_ = OdummyNode->next;
    head_->prev = NULL;
    tail = ZdummyNode->prev;
    tail->next = NULL;

  delete OdummyNode;
  delete ZdummyNode;

startPoint = saveEndPoint;
endPoint = saveStartPoint;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
if ( head_ == NULL || (n <= 0)) return;
if (n > length_) n = length_;
  ListNode* current = head_;
  ListNode* start = head_;
  ListNode* end = NULL;
  int ctr = 0;

  while (ctr < (n-1)){
	current = current->next;
	ctr++;
  }

  end = current;
  reverse (start, end);

  while (end->next != NULL){
	  ctr = 0;
	  start = end->next;
	  current = end->next;

	  while (ctr < (n-1)){
		  if (current->next == NULL)
			  break;
		  current = current->next;
		  ctr++;
	  }
	  end = current;

	  reverse(start, end);
  }


}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

if ( head_ == NULL ) return;

	ListNode* current = head_;
	ListNode* toMove = NULL;

	while ( (current->next) != tail_ && (current->next)!= NULL){
		toMove = current->next;

	    	current->next = toMove->next;
		(toMove->next)->prev = current;
		tail_->next = toMove;
		toMove->prev = tail_;
		toMove->next = NULL;
		tail_ = toMove;

		current = current->next;
	}



}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();
    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2

  if (start-> next == NULL)
	return NULL;

  ListNode* current = start;
    for (int i = 0; i < (splitPoint-1); i++){
        current = current->next;
        if (current == NULL || current->next == NULL)
        	return NULL;
    }

  ListNode* firstSplit = current->next;
  firstSplit->prev = NULL;

  current->next = NULL;

return firstSplit;
}
/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;
    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

	 ListNode* firstCurrent = first;
	 ListNode* secondCurrent = second;
	 ListNode* secondTemp = NULL;
	 ListNode* returnPtr = first;

    while (secondCurrent != NULL)
    {
  	   while (firstCurrent != NULL)
	   {
		   if( secondCurrent->data < firstCurrent->data )
		   {
		  	    if (firstCurrent->prev == NULL)
		  	    {
		  	    	secondTemp = secondCurrent->next;
		     		firstCurrent->prev = secondCurrent;
		   		    secondCurrent->prev = NULL;
		   		    secondCurrent->next = firstCurrent;
		   		    returnPtr = secondCurrent;
		   	    }
		   	    else
		   	    {
		   	    	secondTemp = secondCurrent->next;
		   	    	secondCurrent->prev = firstCurrent->prev;
		   	    	(secondCurrent->prev)->next = secondCurrent;
		   	    	secondCurrent->next = firstCurrent;
		   	    	firstCurrent->prev = secondCurrent;
		   	    }
		   	    firstCurrent = secondCurrent->next;
		   	    secondCurrent = secondTemp;
		   	    break;
		 }
	     else if (firstCurrent->next == NULL)
		 {
		    firstCurrent->next = secondCurrent;
		    secondCurrent->prev = firstCurrent;
		    secondCurrent = NULL;
		    break;
		 }
	     firstCurrent = firstCurrent->next;
	   }
	 }

return returnPtr;
}
/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

//base case
  if (chainLength == 1) return start;

//split returns right half
  ListNode* firstHalf = start;
  ListNode* secondHalf = split(start, chainLength/2);

  secondHalf =  mergesort(secondHalf, chainLength-chainLength/2);
  start = mergesort(firstHalf, chainLength/2);

return merge(start, secondHalf);
}
