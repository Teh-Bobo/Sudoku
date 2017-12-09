/* PossibleFuns.h
	This file contains all the function
	definitions for working with the 
	possibilites array.
	
	They're all formatted in this format:

	int [name]Possible(int x, int y, int k, int** solution, bool*** possible)

	where x is the horizontal index of the square we're working with
	where y is the vertical index
	k is the current number we're working with for the given square
	int** solution is the solution array that SHOULD NOT BE CHANGED in these functions
	bool*** possible is the possiblites array that will be changed by these functions
	they should return 0 on sucess and a different arbitrary number on failure

	These functions all work by assuming a number can go in the given square 
	then proving it can't.
*/

int RowPossible(int i, int j, int k, int** solution, bool*** possible);
int ColumnPossible(int i, int j, int k, int** solution, bool*** possible);
int BoxPossible(int i, int j, int k, int** solution, bool*** possible);
