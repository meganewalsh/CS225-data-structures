/* Your code here! */
#include "dsets.h"
#include <vector>
#include <iostream>

using namespace std;

/* Creates n unconnected root nodes at the end of the vector.
 *
 * -- num    The number of nodes to create.
 */
void DisjointSets::addelements(int num){

    for (int i = 0; i < num; i++)
	V.push_back(-1);

}

/* This function should compress paths and works as described in lecture.
 * Returns the index of the root of the up-tree in which the parameter element resides.
 */
int DisjointSets::find(int elem){

    if (V[elem] < 0)
	return elem;
    else
	return find(V[elem]);

}

/* This function should be implemented as union-by-size.
 *
 * That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point
 * at the larger. This function works as described in lecture, except that you should not assume that the
 * arguments to setunion are roots of existing uptrees.
 * Your setunion function SHOULD find the roots of its arguments before combining the trees. If the two
 * sets are the same size, make the tree containing the second argument point to the tree containing the
 * first. (Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)
 *
 * -- a     Index of the first element to union
 * -- b	    Index of the second element to union
 */
void DisjointSets::setunion(int a, int b){

    int rootA = find(a);
    int rootB = find(b);
    int newSize = V[rootA] + V[rootB];

    if (V[rootA] > V[rootB]){
	V[rootA] = rootB;
	V[rootB] = newSize;
    }
    else{
	V[rootB] = rootA;
	V[rootA] = newSize;
    }

}


int DisjointSets::size(int elem){

    int curr = elem;
    int s = 0;
    while (V[curr] >= 0){
	curr = V[curr];
	s++;
    }

    return s;
}
