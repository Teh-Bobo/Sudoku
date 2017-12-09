#include <string>
#include "MainFuncs.h"
#include "AnswerFuncs.h"
#include "AdvancedFuncs.h"

void FillPossible(int** solution, bool*** possible)
{
	for(int i=0; i < 9; i+=1){
		for(int j=0; j < 9; j+=1){
			//if we already know the number for this square
			//don't redo it
			if(solution[i][j] != 0)
				continue;
			//k is the number we are currently testing for
			for(int k=1; k <= 9; k+=1){
				possible[i][j][k-1] = true;
				//first test to see if k is in this row 
				RowPossible(i,j,k,solution,possible);
				//then if k is in this column; only if needed
				if(!possible[i][j][k-1])
					continue;
				ColumnPossible(i,j,k,solution,possible);
				//and finally check if k is in this 3x3 box; if needed
				if(!possible[i][j][k-1])
					continue;
				BoxPossible(i,j,k,solution,possible);
			}
		}
	}
}
bool MainLoop(int** solution, bool*** possible, int spacesleft, bool verbose, std::ostream& out, int depth)
{
	while(spacesleft > 0){
		FillPossible(solution,possible);
		//Reduce the possibilities buffer
		RowAdvanced(solution,possible,verbose);
		ColumnAdvanced(solution,possible,verbose);
		BoxPairAdvanced(solution,possible,verbose);
		//And find some answers
		if( SquareAnswer(solution,possible,verbose,out) ||
				RowAnswer(solution,possible,verbose,out) ||
				ColumnAnswer(solution,possible,verbose,out) ||
				BoxAnswer(solution,possible,verbose,out)
				)
			spacesleft -=1;
		else
			if(!Guess(solution,possible,spacesleft,verbose,out, depth))
				return false;
			else
				spacesleft-=1;
	}
	return true;
}
void deleteArrays(int** solution, bool*** possible){
	for(int l=0; l < 9; l++){
		for(int m=0; m < 9; m++)
			delete[] possible[l][m];
		delete[] possible[l];
		delete[] solution[l];
	}
	delete[] solution;
	delete[] possible;
}
void copyArrays(int** cs,bool*** cp,int** s,bool*** p){
	for(int i=0; i < 9; i++)
		for(int j=0; j < 9; j++)
			cs[i][j] = s[i][j];
	for(int i=0; i < 9; i++)
		for(int j=0; j < 9; j++)
			for(int k=0; k < 9; k++)
				cp[i][j][k] = p[i][j][k];
}
void printPuzzle(int** solution, bool*** possible, std::ostream& out, std::string indent){
	for(int i=0; i < 9; i++){
		out << std::endl << indent;
		for(int j=0; j < 9; j++)
			out << solution[i][j] << " ";
	}
	out << std::endl;
	for(int i=0; i < 9; i++)
		for(int j=0; j < 9; j++){
			out  << indent << "row: " << i << " col: " << j << ":    ";
			for(int k=0; k < 9; k++)
				out << possible[i][j][k] << " ";
			out << std::endl;
		}
	out << std::endl;
}
bool Guess(int** solution, bool*** possible, int spacesleft, bool verbose, std::ostream& out, int depth)
{
	if(spacesleft == 0)
		return false;
	int** copySolution;
	bool*** copyPossible;
	int copySpacesleft = spacesleft;
	std::string indent = "";
	for(int i=0; i < depth; i++)
		indent += "-";
	
	copySolution = new int*[9];
	copyPossible = new bool**[9];
	for(int i=0; i < 9; i++){
		copySolution[i] = new int[9];
		copyPossible[i] = new bool*[9];
		for(int j=0; j < 9; j++){
			copyPossible[i][j] = new bool[9];
		}
	}
	copyArrays(copySolution,copyPossible,solution,possible);
	//Find a spot and guess a possible number
	for(int i=0; i < 9; i++)
		for(int j=0; j < 9; j++){
			if(copySolution[i][j])
				continue;
			for(int k=0; k < 9; k++){
				if(!copyPossible[i][j][k])
					continue;
				copySolution[i][j] = k+1;
				copySpacesleft--;
				if(verbose){
					out << indent << "Guessing " << k+1 << " at " << i << " " << j << std::endl;
					printPuzzle(copySolution,copyPossible,out,indent);
				}
				if(MainLoop(copySolution,copyPossible,copySpacesleft,verbose,out,depth+1)){
					//We found a solution
					copyArrays(solution,possible,copySolution,copyPossible);
					deleteArrays(copySolution,copyPossible);
					if(verbose){
						out << indent << k+1 << " was right" << std::endl;
						out << indent << depth << " " << copySpacesleft << std::endl;
					}
					return true;
				}
				else{//We didn't find a solution
					if(verbose)
						out << indent << k+1 << " at " << i << " " << j << " was wrong." << std::endl;
					copyArrays(copySolution,copyPossible,solution,possible);
				}
			}
		}
	return false;
}
