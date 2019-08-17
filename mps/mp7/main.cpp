#include <iostream>
#include "dsets.h"
#include "maze.h"
#include <cmath>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here

   SquareMaze myMaze;
   myMaze.makeIMaze(40,40);

   for (int i = 0; i < 11; i++){
	for (int j = 10; j <= 29; j++){
		myMaze.setWall(i,j,0,0);
		myMaze.setWall(i,j,1,0);
	}
   }
   for (int i = 29; i < 40; i++){
	for (int j = 10; j <= 29; j++){
		myMaze.setWall(i,j,0,0);
		myMaze.setWall(i,j,1,0);
	}
   }

   PNG* maze = myMaze.drawMazeWithSolution();
   for (int i = 0; i < 12*10; i++){
	for (int j = 12*10; j < 31*10; j++){
		HSLAPixel & p = maze->getPixel(i,j);
		p.l = 1;
	}
   }
   for (int i = 30*10; i < 40*10; i++){
	for (int j = 12*10; j < 31*10; j++){
		HSLAPixel & p = maze->getPixel(i,j);
		p.l = 1;
	}
   }

   maze->writeToFile("creative.png");
   delete maze;
   
  return 0;
}
