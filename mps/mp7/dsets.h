/* Your code here! */
#ifndef DSETS_H
#define DSETS_H
#include <vector>

class DisjointSets {

  public:
	void addelements(int);
  	int find(int);
  	void setunion(int, int);
  	int size(int);

	std::vector<int> V;

};


#endif
