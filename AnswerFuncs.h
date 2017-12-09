/* AnswerFuncs.h
	This file contains the function definitions for all the functions
	that actually find answers to certain squares. They all follow a
	common definition:

	bool [name]Answer(int** solution, bool*** possible, bool verbose = false, ostream& cout = std::cout)
*/
#include <iostream>

bool SquareAnswer(int** solution, bool*** possible, bool verbose = false, std::ostream& cout = std::cout);
bool RowAnswer(int** solution, bool*** possible, bool verbose = false, std::ostream& cout = std::cout);
bool ColumnAnswer(int** solution, bool*** possible, bool verbose = false, std::ostream& cout = std::cout);
bool BoxAnswer(int** solution, bool*** possible, bool verbose = false, std::ostream& cout = std::cout);
