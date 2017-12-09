#include <iostream>
#include <fstream>
#include "MainFuncs.h"

using namespace std;

int solve(ifstream& file){
	int ** original = NULL;
	int ** solution = NULL;
	bool *** possible = NULL;

	int spacesleft = 81;

	original = new int*[9];
	solution = new int*[9];
	possible = new bool**[9];
	for(int i=0; i < 9; i+=1){
		original[i] = new int[9];
		solution[i] = new int[9];
		possible[i] = new bool*[9];
		for(int j=0; j < 9; j+=1){
			original[i][j] = 0;
			solution[i][j] = 0;
			possible[i][j] = new bool[9];
			for(int k=0; k < 10; k+=1)
				possible[i][j][k] = false;
		}
	}

	//Read the puzzle into the puzzle buffers
	for(int i=0; i < 9; i +=1)
		for(int j=0; j < 9; j +=1){
			//register int c = args[1][i * 9 + j];
			char in;
			int c;
			if(!(file >> in)){
				return 7;
			}
			c = in;
			//if(c == '\0'){
			//	cerr << "Puzzle too short" << endl;
			//	return -1;
			//}
			c -= '0';
			original[i][j] = c;
			solution[i][j] = c;
			//check to see if the value is valid
			if(c < 0 && c > 9){
				cerr << "Invalid char in puzzle file" << endl;
				return -1;
			}
			if(c != 0){
				spacesleft--;
			}
		}
	//main loop
	if(!MainLoop(solution,possible,spacesleft,true)){
		cerr << "CURRENT VERSION CANT SOLVE PUZZLE" << endl;
		
		// if(!Guess(&solution,possible,spacesleft,true)){
			// cerr << "PUZZLE CAN'T BE SOLVED WITH CURRENT VERSION" << endl;
			// return 9;
		// }
	}
/*	//debug print
	for(int i=0; i < 9; i++)
		for(int j=0; j < 9; j++){
			cout << "row: " << i << " col: " << j << ":    ";
			for(int k=0; k < 9; k++)
				cout << possible[i][j][k] << " ";
			cout << endl;
		}
	cout << endl;
 */
	//original print
	cout << "Original puzzle:" << endl;
	for(int i=0; i < 9; i++){
		cout << endl;
		for(int j=0; j < 9; j++)
			cout << original[i][j] << " ";
	}
	cout << endl << endl;
	//solution print
	cout << "Solved puzzle:" << endl;

	for(int i=0; i < 9; i++){
		cout << endl;
		for(int j=0; j < 9; j++)
			cout << solution[i][j] << " ";
	}
	cout << endl;
	return 0;
}
int main(int argc, char** args)
{
	if(argc != 2){
		cerr << "put the puzzle in the command line; dummy" << endl;
		return -1;
	}
	ifstream file;
	file.open(args[1],ios::in);
	int ret=0;
	for (;file.good() && ret!=7;){
		ret = solve(file);
	}
	file.close();
}

