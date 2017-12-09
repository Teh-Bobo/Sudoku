#include "AnswerFuncs.h"

bool SquareAnswer(int** solution, bool*** possible, bool verbose, std::ostream& cout )
{
	int count = 0;
	int temp = 0;
	for(int i=0; i < 9; i++)
		for(int j=0; j < 9; j++)
			if(!solution[i][j]){
				count = 0;
				for(int k=0; k < 9; k++)
					if(possible[i][j][k]){
						count += 1;
						temp = k+1;
					}
				if(count == 1){
					solution[i][j] = temp;
					possible[i][j][temp-1] = false;
					if(verbose) cout << "square put: " << temp << " in " << i << " " << j << std::endl;
					return true;
				}
			}
	return false;
}
bool RowAnswer(int** solution, bool*** possible, bool verbose, std::ostream& cout)
{
	int count = 0;
	int pos = 0;
	for(int i=0; i < 9; i++)
		for(int k=0; k < 9; k++){
			count = 0;
			for(int j=0; j < 9; j++){
				if(solution[i][j] == k+1){
					count = 0;
					break;
				}
				if(solution[i][j])
					continue;
				if(possible[i][j][k]){
					count++;
					pos = j;
				}
			}
			if(count == 1){
				solution[i][pos] = k + 1;
				if(verbose) cout << "row put: " << k + 1 << " in " << i << " " << pos << std::endl;
				return true;
			}
		}
	return false;
}
bool ColumnAnswer(int** solution, bool*** possible, bool verbose, std::ostream& cout)
{
	int count = 0;
	int pos = 0;
	for(int j=0; j < 9; j++)
		for(int k=0; k < 9; k++){
			count = 0;
			for(int i=0; i < 9; i++){
				if(solution[i][j] == k+1){
					count = 0;
					break;
				}
				if(solution[i][j])
					continue;
				if(possible[i][j][k]){
					count++;
					pos = i;
				}
			}
			if(count == 1){
				solution[pos][j] = k + 1;
				if(verbose) cout << "column put: " << k + 1 << " in " << pos << " " << j << std::endl;
				return true;
			}
		}
	return false;
}
bool BoxAnswer(int** solution, bool*** possible, bool verbose, std::ostream& cout)
{
	int count = 0;
	int x = 0;
	int y = 0;
	for(int i=0; i < 9; i+=3)
		for(int j=0; j < 9; j+=3)
			for(int k=0; k < 9; k++){
				x = 0;
				y = 0;
				count = 0;
				for(int l=i; l < i+3; l++)
					for(int m=j; m < j+3; m++){
						if(solution[l][m] == k+1){
							count = 0;
							goto boxend;
						}
						if(solution[l][m])
							continue;
						if(possible[l][m][k]){
							count++;
							x = l;
							y = m;
						}
					}
boxend:
				if(count == 1){
					solution[x][y] = k + 1;
					if(verbose) cout << "box put: " << k + 1 << " in " << x << " " << y << std::endl;
					return true;
				}
			}
	return false;
}
