#include "maze.h"
#include <iostream>
#include "dsets.h"
#include "cs225/HSLAPixel.h"
#include <queue>
#include <map>
using namespace std;

/* No parameter constructor.
 * Creates an empty maze.
 */
SquareMaze::SquareMaze(){

    Width = 0;
    Height = 0;
    cells = DisjointSets();

}


/* Makes a new SquareMaze in the shape of an I. For creative portion, MP7 3.3.
 * 
 * Parameters:
 *  	width	The width of the SquareMaze  -- 40
 *  	height	The height of the SquareMaze -- 40
 */
void SquareMaze::makeIMaze(int width, int height){

    Width = width;
    Height = height;
    cells.addelements(Width*Height);

    rightWalls = vector<bool>(Width*Height, true);
    bottomWalls = vector<bool>(Width*Height, true);

  int size = Width * Height;

  srand(time(NULL));

  vector<int> R(size);
	for (int i = 0; i < Width*Height; i++)
	    R.push_back(i);

  vector<int> B = R;
  random_shuffle(R.begin(), R.end());
  random_shuffle(B.begin(), B.end());

  while( !B.empty() || !R.empty() ){

	int direction = rand() % 2;
	if (B.empty())		direction = 0;
	if (R.empty())		direction = 1;

	int wall;
	if (direction == 1){

		wall = B[ B.size()-1 ];
		B.pop_back();

		if (wall >= size-Width ||
			(wall >= 9*Width && wall <= 9*Width+11) || 
			(wall >= 9*Width+29 && wall < 9*Width+40) || 
			(wall >= 30*Width && wall <= 30*Width+11) || 
			(wall >= 30*Width+29 && wall < 30*Width+40)) 
			continue; 

		if ( cells.find(wall) != cells.find(wall+Width) ){
			bottomWalls[wall] = false;
			cells.setunion(wall, wall+Width);
		}
	}

	else{

		wall = R[ R.size()-1 ];
		R.pop_back();

		if ( (wall+1) % Width == 0 ||
		(wall >= 9*Width+30 && wall <= 30*Width+30 && wall%Width == 28) || 
		(wall >= 9*Width+30 && wall <= 30*Width+30 && wall%Width == 11)) 

			continue;

		if ( cells.find(wall) != cells.find(wall+1) ){
			rightWalls[wall] = false;
			cells.setunion(wall, wall+1);
		}	    	
	}

  }

}



/* Makes a new SquareMaze of the given height and width.
 * If this object already represents a maze it will clear all the existing data
 * before doing so. You will start with a square grid (like graph paper) with the
 * specified height and width. You will select random walls to delete without
 * creating a cycle, until there are no more walls that could be deleted without
 * creating a cycle. Do not delete walls on the perimeter of the grid.
 * 
 * Hints: You only need to store 2 bits per square: the "down" and "right" walls.
 * The finished maze is always a tree of corridors.)
 * 
 * Parameters:
 *  	width	The width of the SquareMaze (number of cells)
 *  	height	The height of the SquareMaze (number of cells)
 */
void SquareMaze::makeMaze(int width, int height){

    Width = width;
    Height = height;
    cells.addelements(Width*Height);

    rightWalls = vector<bool>(Width*Height, true);
    bottomWalls = vector<bool>(Width*Height, true);

  int size = Width * Height;

  srand(time(NULL));

  vector<int> R(size);
	for (int i = 0; i < Width*Height; i++)
	    R.push_back(i);

  vector<int> B = R;
  random_shuffle(R.begin(), R.end());
  random_shuffle(B.begin(), B.end());

  while( !B.empty() || !R.empty() ){

	int direction = rand() % 2;
	if (B.empty())		direction = 0;
	if (R.empty())		direction = 1;

	int wall;
	if (direction == 1){

		wall = B[ B.size()-1 ];
		B.pop_back();

		if (wall >= size-Width)
			continue; 

		if ( cells.find(wall) != cells.find(wall+Width) ){
			bottomWalls[wall] = false;
			cells.setunion(wall, wall+Width);
		}
	}

	else{

		wall = R[ R.size()-1 ];
		R.pop_back();

		if ( (wall+1) % Width == 0 )
			continue;

		if ( cells.find(wall) != cells.find(wall+1) ){
			rightWalls[wall] = false;
			cells.setunion(wall, wall+1);
		}	    	
	}

  }

}


/* This uses your representation of the maze to determine whether it is possible to
 * travel in the given direction from the square at coordinates (x,y).
 * 
 * For example, after makeMaze(2,2), the possible input coordinates will be (0,0),
 * (0,1), (1,0), and (1,1).
 *
 * dir = 0 represents a rightward step (+1 to the x coordinate)
 * dir = 1 represents a downward step (+1 to the y coordinate)
 * dir = 2 represents a leftward step (-1 to the x coordinate)
 * dir = 3 represents an upward step (-1 to the y coordinate)
 * You can not step off of the maze or through a wall.
 * 
 * This function will be very helpful in solving the maze. It will also be used by
 * the grading program to verify that your maze is a tree that occupies the whole
 * grid, and to verify your maze solution. So make sure that this function works!
 * 
 * Parameters:
 *  	
 *  	x	The x coordinate of the current cell
 *  	y	The y coordinate of the current cell
 *  	dir	The desired direction to move from the current cell
 *  
 * Returns:	whether you can travel in the specified direction	
 */
bool SquareMaze::canTravel(int x, int y, int dir) const{

   int ref = Width*y + x;

   if (dir == 0){
	if (rightWalls[ ref ] == false)		return true;
	else					return false;
   }

   else if (dir == 1){
	if (bottomWalls[ ref ] == false)	return true;
	else					return false;
   }
   else if (dir == 2){
	if (ref%Width == 0)			return false;

	int left_ref = ref - 1;
	if (rightWalls[ left_ref ] == false)	return true;
	else					return false;

   }
   else{
	if (ref < Width)			return false;

	int up_ref = ref - Width;
	if (bottomWalls[ up_ref ] == false)	return true;
	else					return false;
   }

}


/* Sets whether or not the specified wall exists.
 * 
 * This function should be fast (constant time). You can assume that in grading we
 * will not make your maze a non-tree and then call one of the other member
 * functions. setWall should not prevent cycles from occurring, but should simply
 * set a wall to be present or not present. Our tests will call setWall to copy a
 * specific maze into your implementation.
 *
 *  Parameters:
 *  	
 *  	x	The x coordinate of the current cell
 *  	y	The y coordinate of the current cell
 *  	dir	Either 0 (right) or 1 (down), which specifies which wall to set
 *  		(same as the encoding explained in canTravel). You only need to
 *  		support setting the bottom and right walls of every square in the
 *  		grid.
 *  	exists	true if setting the wall to exist, false otherwise
 */
void SquareMaze::setWall(int x, int y, int dir, bool exists){

   pair<int, int> coord(x,y);
   int ref = y*Width + x;

   if (dir == 0)
	rightWalls[ ref ] = exists;
   else
	bottomWalls[ ref ] = exists;

}	


/* Solves this SquareMaze.
 * 
 * For each square on the bottom row (maximum y coordinate), there is a distance
 * from the origin (i.e. the top-left cell), which is defined as the length
 * (measured as a number of steps) of the only path through the maze from the origin
 * to that square.
 * 
 * Select the square in the bottom row with the largest distance from the origin as
 * the destination of the maze. solveMaze() returns the winning path from the origin
 * to the destination as a vector of integers, where each integer represents the
 * direction of a step, using the same encoding as in canTravel().
 * 
 * If multiple paths of maximum length exist, use the one with the destination cell
 * that has the smallest x value.
 *
 * Hint: this function should run in time linear in the number of cells in the maze.
 *
 * Returns:	a vector of directions taken to solve the maze
 */
vector< int > SquareMaze::solveMaze(){

   vector<int> final_solution;

   //no cells have been visited yet
   vector<bool> visited(Width*Height, false);

   //p will keep track of predecessor
   map<int, int> p;

   queue<int> Q;
   int start = 0;
   Q.push(start);
   visited[start] = true;

   int up_R, left_R, down_R, right_R, cell;
   pair<int, int> coord; 

   while (!Q.empty()){

	    cell = Q.front();
	    Q.pop();

	    //used for canTravel
	    coord.first = cell % Width;
	    coord.second = cell / Width;

	    //obtain reference number of current cell's neighbors
	    up_R = cell - Width;
	    left_R = cell - 1;
	    down_R = cell + Width;
	    right_R = cell + 1;

	    //UP
       	    if (canTravel(coord.first, coord.second, 3) && !visited[up_R] ) {
		    visited[up_R] = true;
		    Q.push(up_R);
		    p[up_R] = cell;
            }

	    //LEFT
	    if (canTravel(coord.first, coord.second, 2) && !visited[left_R]){
		    visited[left_R] = true;
		    Q.push(left_R);
		    p[left_R] = cell;
	    }

	    //DOWN
	    if (canTravel(coord.first, coord.second, 1) && !visited[down_R]){
		    visited[down_R] = true;
		    Q.push(down_R);
		    p[down_R] = cell;
	    }

	    //RIGHT
	    if (canTravel(coord.first, coord.second, 0) && !visited[right_R]){
		    visited[right_R] = true;
		    Q.push(right_R);
		    p[right_R] = cell;
	    }

   }

   //predecessor map full -- traverse backwards to find furthest exit 
   int longest_distance = 0;
   int length, e;

   for (int a = 0; a < Width; a++){
	length = 0;
	e = (Height-1)*Width + a;

	while (start != e){
		e = p[e];
		length += 1;
	}

	if (length > longest_distance){
		exit = (Height-1)*Width + a;
		longest_distance = length;
	}
   }

   //path is saved in wrong direction -- fixing now
   e = exit;
   int i;

   while (start != e){

	i = e - p[e];

	if (i == -1)
		final_solution.push_back(2);
	else if (i == 1)
		final_solution.push_back(0);
	else if (i < -1)
		final_solution.push_back(3);
	else //(i>1)
		final_solution.push_back(1);

	e = p[e];
   }

   //aaaand now it's backwards
   reverse(final_solution.begin(), final_solution.end());

   return final_solution;
}	



/* Draws the maze without the solution.
 *
 * First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1).
 * where height and width were the arguments to makeMaze. Blacken the entire topmost
 * row and leftmost column of pixels, except the entrance (1,0) through (9,0). For
 * each square in the maze, call its maze coordinates (x,y). If the right wall exists,
 * then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. If
 * the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10)
 * for k from 0 to 10.
 *
 * The resulting PNG will look like the sample image, except there will be no exit
 * from the maze and the red line will be missing.
 *
 * Returns:	a PNG of the unsolved SquareMaze
 */
PNG * SquareMaze::drawMaze() const{

  PNG* myMaze = new PNG(Width*10+1, Height*10+1);

  for (int h = 0; h < Height; h++){
      for (int w = 0; w < Width; w++){

	    if ( h == 0 && w != 0 ){
		for (int k = 0; k <= 10; k++){
		     HSLAPixel & pix = myMaze->getPixel( (w*10)+k, h );
		     pix.l = 0;
		}
	    }
	    else if ( w == 0 ){
		for (int k = 0; k <= 10; k++){
		     HSLAPixel & pix = myMaze->getPixel( w, (h*10)+k );
		     pix.l = 0;
		}
	    }

		int ref = h*Width + w; 
		if (rightWalls[ ref ] == true){
		    for (int k = 0; k <= 10; k++){
			HSLAPixel & pix = myMaze->getPixel( (w+1)*10, h*10+k );
			pix.l = 0;
		    }
		}
		if (bottomWalls[ ref ] == true){
		    for (int k = 0; k <= 10; k++){
 			HSLAPixel & pix = myMaze->getPixel( w*10+k, (h+1)*10 );
			pix.l = 0;
		    }
		}


      }
  }

  return myMaze;
}



/* This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze
 * to show the solution vector and the exit.
 *
 * Start at pixel (5,5). Each direction in the solution vector corresponds to a trail
 * of 11 red pixels in the given direction. If the first step is downward, color
 * pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). Then if the second
 * step is right, color pixels (5,15) through (15,15) red. Then if the third step is
 * up, color pixels (15,15) through (15,5) red. Continue in this manner until you get
 * to the end of the solution vector, so that your output looks analogous the above
 * picture.
 *
 * Make the exit by undoing the bottom wall of the destination square: call the
 * destination maze coordinates (x,y), and whiten the pixels with coordinates
 * (x*10+k, (y+1)*10) for k from 1 to 9.
 *
 * Returns:	a PNG of the solved SquareMaze
 */
PNG * SquareMaze::drawMazeWithSolution() {

    PNG* mySolvedMaze = drawMaze();
    vector<int> solution = solveMaze();
    HSLAPixel RED(0, 1, 0.5, 1);

    int x = 5;
    int y = 5;
    int k;

    for (int i = 0; i < (int)solution.size(); i++) {	

	if (solution[i] == 0){
	     for (k = 0; k <= 10; k++){
		HSLAPixel & pixel = mySolvedMaze->getPixel( x+k, y );
		pixel = RED;
	     }
	     x = x+k-1;
	}
	
	else if (solution[i] == 1){
	     for (k = 0; k <= 10; k++){
		HSLAPixel & pixel = mySolvedMaze->getPixel( x, y+k );
		pixel = RED;
	     }
	     y = y+k-1;
	}

	else if (solution[i] == 2){
	     for (k = 0; k <= 10; k++){
		HSLAPixel & pixel = mySolvedMaze->getPixel( x-k, y );
		pixel = RED;
	     }
	     x = x-k+1;
	}

	else{
	     for (k = 0; k <= 10; k++){
		HSLAPixel & pixel = mySolvedMaze->getPixel( x, y-k );
		pixel = RED;
	     }
	     y = y-k+1;
	}

    }


    for (int k = -4; k < 5; k++){
 	HSLAPixel & pix = mySolvedMaze->getPixel( x+k, y+5 );
	pix.l = 1;
    }

  return mySolvedMaze;
}	

