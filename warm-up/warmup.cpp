#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
using std::size_t;
#include <algorithm>
using std::max;
using std::min;
#include <stdlib.h>

vector<vector<bool> > world = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void print_vector(vector<vector<bool>>& v){
	size_t row = v.size();
	size_t col = v[0].size();
	for(size_t r = 0; r < row; r++){
		for (size_t c = 0; c < col; c++){
			if (v[r][c]) cout << "O";
			else cout << ".";
		}
		cout << endl;
	}
	
}

int find_neighbors(vector<vector<bool>>& grid, int row,int col, int rowLength, int colLength){
	// !: this is super unorganized and not ideal. would've made it cleaner by nesting if statements or possibly recursion
	
	int alive = 0;
	// Check bounds 8 sides and make sure the row and col are not going out of bounds
	if (row > 0){
		// look at cell directly above
		if (grid[row-1][col] == 1) alive++;
	}
	if (row < rowLength-1){
		// look at cell directly below
		if (grid[row+1][col] == 1) alive++;
	}
	if (row == 0) {
		// if cell is in top border look at the bottom border for neighbors
		if(grid[rowLength-1][col] == 1) alive++;
	}
	if (row == rowLength - 1){
		// if cell is in bottom border look at the top border for neighbors
		if (grid[0][col] == 1) alive++;
	}
	if (col > 0){
		// look at cell to the direct left
		if (grid[row][col-1] == 1) alive++;
	}
	if (col < colLength-1){
		// look at cell to the direct right
		if (grid[row][col+1] == 1) alive++;
	}
	if (col == 0) {
		// if cell is in left border, look at right border for neighbors
		if (grid[row][colLength-1] == 1) alive++;
	}
	if (col == colLength-1) {
		// if cell is in right border, look at left border for neighbors
		if (grid[row][0] == 1) alive++;
	}
	if (row > 0 && col > 0){
		// look at top left cell
		if (grid[row-1][col-1] == 1) alive++;
	}
	if (row > 0 && col < colLength-1) {
		// look at top right
		if (grid[row-1][col+1] == 1) alive++;
	}
	if (row > 0 && col == 0){
		// check right most col row above
		if (grid[row-1][colLength-1] == 1) alive ++;
	}
	if (row > 0 && col == colLength-1){
		// check left most row above
		if (grid[row-1][0] == 1) alive ++;
	}
	if (row == 0 && col > 0) {
		// check last row and to the left
		if (grid[rowLength-1][col-1] == 1) alive++;
	}
	if (row == 0 && col < colLength - 1) {
		// check last row and to the right
		if (grid[rowLength-1][col+1] == 1) alive++;
	}
	if (row == rowLength-1 && col > 0) {
		// check top row and to the left
		if (grid[0][col-1] == 1) alive++;
	}
	if (row == rowLength-1 && col < colLength - 1) {
		// check top row and to the right
		if (grid[0][col+1] == 1) alive++;
	}
	if (row < rowLength-1 && col < colLength-1){
		// look at bottom right
		if (grid[row+1][col+1] == 1) alive++;
	}
	if (row < rowLength-1 && col > 0){
		// look at bottom left
		if (grid[row+1][col-1] == 1) alive++;
	}
	if (row < rowLength-1 && col == 0){
		// row below right most col
		if (grid[row+1][colLength-1] == 1) alive++;
	}
	if (row < rowLength-1 && col == colLength-1){
		// row below left most col
		if (grid[row+1][0] == 1) alive++;
	}
	return alive;
	
}


int main(int argc, char *argv[])
{
	vector<vector<bool>> future(world); /* make future a copy of world. */
	/* NOTE: the vector 'world' above corresponds to the contents
	 * of ../res/tests/0.  TODO: apply the rules to the vector,
	 * write the result to standard output, and compare with the
	 * contents of ../tests/1. */
	
	int generation = atoi (argv[1]);

	size_t row = world.size();
	size_t col = world[0].size();
	
	while (generation > 0){
		for (size_t r = 0; r < row; ++r){
			for (size_t c = 0; c < col; ++c){
				int neighbors = find_neighbors(world, r,c,row,col);
				if(world[r][c] == 0){
					// check if this dead cell is surrounded by alive cells which would make this cell alive
					if (neighbors == 3) future[r][c] = 1;
				}	
				else if (world[r][c] == 1){
					// if this alive cell has less than 2 or more than 3 alive neighbors unalive it
					if (neighbors < 2 || neighbors > 3) future[r][c] = 0;
				}
			}
		}
		world = future;
		generation --;
	}
	world = future;
	print_vector(future);

	return 0;
}
