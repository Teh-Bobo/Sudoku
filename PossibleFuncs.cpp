#include "PossibleFuncs.h"

int RowPossible(int i, int j, int k, int** solution, bool*** possible)
{
	for(int l=0; l < 9; l+=1){
		if(l==j)
			continue;
		if(solution[i][l]==k){
			possible[i][j][k-1] = false;
			break;
		}
	}
	return 0;
}
int ColumnPossible(int i, int j, int k, int** solution, bool*** possible)
{
	for(int l=0; l < 9; l+=1){
		if(l==i)
			continue;
		if(solution[l][j]==k){
			possible[i][j][k-1] = false;
			break;
		}
	}
	return 0;
}
int BoxPossible(int i, int j, int k, int** solution, bool*** possible)
{
	//NOTE: gcc might optimize this out
	//if it does just use the floor function
	int x = ((i/3)*3);
	int y = ((j/3)*3);

	for(int l=x; l < x+3 && possible[i][j][k]; l+=1){
		for(int m=y; m < y+3 && possible[i][j][k]; m+=1){
			if(l==i && m==j)
				continue;
			if(solution[l][m]==k){
				possible[i][j][k-1] = false;
			}
		}
	}
	return 0;
}
