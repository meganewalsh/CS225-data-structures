/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here

  Node* rightNode = t->right;
  t->right = rightNode->left;
  rightNode->left = t;

  t->height = getHeight(t);
  rightNode->height = getHeight(rightNode);
  t = rightNode;
 
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
 
  Node* leftNode = t->left;
  t->left = leftNode->right;
  leftNode->right = t;

  t->height = getHeight(t);
  leftNode->height = getHeight(leftNode);
  t = leftNode;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
//cout << "Rebalancing " << subtree->key << " with balance " << getBalance(subtree) << " and height " << getHeight(subtree) << endl;
  if (getBalance(subtree) > 1){// && subtree->left != NULL){
    if (subtree->left != NULL && getBalance(subtree->left) < 0){
        rotateLeftRight(subtree);
    }
    else{
        rotateRight(subtree);
    }
  }

  else if (getBalance(subtree) < -1){// && subtree->right != NULL) {
    if (subtree->right != NULL && getBalance(subtree->right) > 0){
            rotateRightLeft(subtree);
    }
    else{
        rotateLeft(subtree);
    }
  }

}


template <class K, class V>
int AVLTree<K, V>::getBalance(Node*& subtree)
{
   if (subtree->left != NULL && subtree->right != NULL)
   {
//cout << "For Node " << subtree->key << ", (" << subtree->left->key << ", " << subtree->right->key << ")\n";
   	return (getHeight(subtree->left) - getHeight(subtree->right));
   }
   else if (subtree->left == NULL)
   {
//cout << "For Node " << subtree->key << ", (, " << subtree->right->key << ")\n";
	return -1*getHeight(subtree);
   }
   else{
//cout << "For Node " << subtree->key << ", (" << subtree->left->key << ",)\n";
        return getHeight(subtree);
   }
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    if (root == NULL){
	root = new Node(key, value);
	root->height = 0;
    }
    else
    	insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
  if( key < subtree->key )
  {
    if( subtree->left == NULL )
	subtree->left = new Node(key, value);
    else
	insert(subtree->left, key, value);
  }

  else if( key > subtree->key )
  {
     if( subtree->right == NULL)
     {
	subtree->right = new Node(key, value);
    } 
    else
	insert(subtree->right, key, value);
  }
  else return;

  rebalance(subtree);
  subtree->height = getHeight(subtree); 

}


template <class K, class V>
int AVLTree<K, V>::getHeight(Node*& thisN) {

  int left = 0, right = 0;
  if (thisN->left == NULL && thisN->right == NULL){ return 0;}
  if (thisN->left != NULL)
	left = getHeight(thisN->left);
  if (thisN->right != NULL)
	right = getHeight(thisN->right);

  if (left > right) return 1+left;
  else return 1+right;

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        // your code here
	remove (subtree->left, key);
	rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove (subtree->right, key);
	rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
	    subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
	    Node * left = subtree->left;
            Node * leftParent = subtree;
            while(left->right != NULL){
               leftParent = left;
               left = left->right;
            }
            // Replace value of the removed node
            subtree->key = left->key;
            subtree->value = left->value;

            // Delete the duplicate
            if(leftParent != subtree)
               leftParent->right = NULL;
            else leftParent->left = NULL;
	    //rebalance(subtree);
            delete left;
	    left = NULL;

        } else {
            /* one-child remove */
            // your code here
	    Node* temp = subtree;
	    if (subtree->left != NULL) //left child exists
	    {
		subtree = subtree->left;
	    }
	    else //right child exists
	    {
		subtree = subtree->right;
	    }
	    delete temp;
	    temp = NULL;
        }
        // your code here
    }
}
