/**
	This header contains all the functions need for the main loop of the
	program.
*/
#include "PossibleFuncs.h"
#include <iostream>

void FillPossible(int**,bool***);
bool MainLoop(int**,bool***,int,bool,std::ostream& = std::cout,int=0);
bool Guess(int**,bool***,int,bool,std::ostream& = std::cout,int=0);
