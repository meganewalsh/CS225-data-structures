/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <stack>
using namespace cs225;
using namespace std;

  class SquareMaze {

    public:
	SquareMaze();
	void makeMaze(int, int);
	void makeIMaze(int, int);
	bool canTravel(int, int, int) const;
	void setWall(int, int, int, bool);
	vector<int> solveMaze();
	PNG* drawMaze() const;
	PNG* drawMazeWithSolution();	

	bool solve(int, vector<bool>, vector<int> &);
    private:

	int Width;
	int Height;
	int exit;

	DisjointSets cells;

	vector<bool> rightWalls;
	vector<bool> bottomWalls;
  };


#endif
