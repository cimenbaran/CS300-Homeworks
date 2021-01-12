// Baran Çimen CS300 HW1

#include <iostream>
#include <vector>
#include <random>
#include <ctime> // for random_range function
#include <string>
#include <fstream>

#ifndef STACK_HEADER
#include "Stack_by_Baran_Cimen.h"
#endif

// DISCLAIMER:
//	This disclaimer is for the person who is going to review my code
//	I have implemented the matrix in my way:
//	Normally row is y and column is x so [row][column] should be [y][x]
//	But I like to use [x][y] so the matrix is inversed
//	Overall, it doesn't change the outcome
//	It's just my implementation and it won't affect the results


using namespace std;

int random_range(const int & min, const int & max) {
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

struct cell{
	cell() {x=0; y=0; l=1;r=1;u=1;d=1;};
	cell(int x,int y)  {x=x; y=y; l=1;r=1;u=1;d=1;};




	bool isVirgin() { // Checks if any walls were knocked downed
		return l+r+u+d == 4;
	}


	int x;
	int y;
	bool l,r,u,d;
};

int SmallerOne(int a, int b) {
	if(a > b) 
		return b;
	return a;
}

int BiggerOne(int a, int b) {
	if(a > b)
		return a;
	return b;
}

vector<vector<cell>> CreateMaze(int M,  int N) {

	vector<vector<cell>> maze(N, vector<cell>(M));

	for(int i=0; i < N; i++) {
		for(int j=0; j< M; j++) {
			maze[i][j].x = i;
			maze[i][j].y = j;
		}
	}

	Stack<cell> mazeStack;


	int x = 0;
	int y = 0;
	mazeStack.push(maze[x][y]);

	while(!mazeStack.isEmpty()) {
		cell current = mazeStack.getTop();
		int direction;
		bool check = true;
		while(check) {

			if(!maze[BiggerOne(x-1,0)][y].isVirgin() && !maze[x][SmallerOne(y+1,M-1)].isVirgin() && !maze[SmallerOne(x+1,N-1)][y].isVirgin() && !maze[x][BiggerOne(y-1,0)].isVirgin()) { // checks if it has any non-virgin cells around (works as intended)
				mazeStack.pop();
				if(!mazeStack.isEmpty()) {
					x = mazeStack.getTop().x;
					y = mazeStack.getTop().y;
				} else {
					check = false;
				}
			}

			direction = random_range(0,3); // 0 = left, 1 = up, 2 = right, 3 = down.
			if(direction == 0){
				if(x > 0 && maze[x-1][y].isVirgin()) {
					maze[x][y].l = 0;
					maze[x-1][y].r = 0;
					mazeStack.push(maze[x][y]);
					x--;
					check = false;
				}
			}
			else if(direction == 1){
				if(y < M-1 && maze[x][y+1].isVirgin()) {
					maze[x][y].u = 0;
					maze[x][y+1].d = 0;
					mazeStack.push(maze[x][y]);
					y++;
					check = false;
				}
			}
			else if(direction == 2){
				if(x < N-1 && maze[x+1][y].isVirgin()) {
					maze[x][y].r = 0;
					maze[x+1][y].l = 0;
					mazeStack.push(maze[x][y]);
					x++;
					check = false;
				}
			}
			else if(direction == 3){
				if(y > 0 && maze[x][y-1].isVirgin()) {
					maze[x][y].d = 0;
					maze[x][y-1].u = 0;

					mazeStack.push(maze[x][y]);
					y--;
					check = false;
				}
			}
		}
		
	}
	
	return maze;
}



void CreatePath(int mazeNum, vector<vector<cell>> & maze, const int & entryX, const int & entryY, const int & exitX, const int & exitY) {
	int columns = maze.size();
	int rows = maze[0].size();

	int x = entryX;
	int y = entryY;

	Stack<cell> pathStack;

	while(x != exitX || y != exitY) {
		if(x > 0 && maze[x][y].l == 0) { // Left
			maze[x][y].l = 1; // To stop tracking backwards and if this path is not correct, do not follow this way again
			maze[x-1][y].r = 1;
			pathStack.push(maze[x][y]);
			x--;
		}
		else if(y < rows-1 && maze[x][y].u == 0) { // Up
			maze[x][y].u = 1; // To stop tracking backwards and if this path is not correct, do not follow this way again
			maze[x][y+1].d = 1;
			pathStack.push(maze[x][y]);
			y++;
		}
		else if(x < columns-1 && maze[x][y].r == 0) { // Right
			maze[x][y].r = 1; // To stop tracking backwards and if this path is not correct, do not follow this way again
			maze[x+1][y].l = 1;
			pathStack.push(maze[x][y]);
			x++;
		}
		else if(y > 0 && maze[x][y].d == 0) { // Down
			maze[x][y].d = 1; // To stop tracking backwards and if this path is not correct, do not follow this way again
			maze[x][y-1].u = 1;
			pathStack.push(maze[x][y]);
			y--;
		}
		else {
			x = pathStack.getTop().x;
			y = pathStack.getTop().y;
			pathStack.pop();
		}
	}
	// Now x = exitx and y = exitY
	Stack<cell> outputStack;
	outputStack.push(maze[x][y]);
	while(!pathStack.isEmpty()) {
		outputStack.push(pathStack.topAndPop());
	}
	// Create filename
	string name = "maze_" + to_string(mazeNum) + "_path_" + to_string(entryX) + "_" + to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY) + ".txt";
	// Create file
	ofstream outfile(name);
	// Write to file
	cell temp;
	while(!outputStack.isEmpty()) {
		temp = outputStack.topAndPop();
		outfile << temp.x << " " << temp.y << endl;
	}
	outfile.close();
}


int main() {
	int K, M, N;
	cout << "Enter the number of mazes: ";
	cin >> K;

	cout << "Enter the number of rows and columns (M and N): ";
	cin >>  M >> N;


	vector<vector<vector<cell>>> mazes;

	for(int i=0; i < K; i++) {
		vector<vector<cell>> maze = CreateMaze(M, N);
		string name = "maze_" + to_string(i+1) + ".txt";
		
		ofstream outfile(name);
		outfile << M << " " << N << endl;
		for(int ii=0; ii< M; ii++) {
			for(int j=0; j<N; j++) {
				cell temp = maze[j][ii];
				outfile << "x=" << temp.x << " y=" << temp.y << " l=" << temp.l << " r=" << temp.r << " u=" << temp.u << " d=" << temp.d << endl;
			}
		}
		outfile.close();
		mazes.push_back(maze);
	}
	cout << "All mazes are generated." << endl << endl;

	int mazeNum, entryX, entryY, exitX, exitY;
	cout << "Enter a maze ID between 1 to " << K << " inclusive to find a path: ";
	cin >> mazeNum;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryX >> entryY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX >> exitY;

	CreatePath(mazeNum, mazes[mazeNum-1], entryX, entryY, exitX, exitY);

	return 0;
}