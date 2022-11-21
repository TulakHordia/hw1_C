#ifndef __FUNCTIONS__
#define __FUNCTIONS__

//Sub Matrix sum functions.
int 	doFindMaxSubMatrix(const int* arr, int rows, int cols, int subRows, int subCols, int* rowStart, int* colStart, int* firstNum);
void 	biggestMatrixSum();
void 	initializeArr(int* arr, int rows, int cols);
void 	printMat(int* arr, int rows, int cols);
void 	printSubMat(int* board, int cols, int subRows, int subCols, int rowStart, int colStart);

//Color functions.
//Actual functions logic.
void	colorTheBoard(int* board, int rows, int cols, int amountOfColors, int* startValues);
int		expandColor(int* board, int rows, int cols, int rowStart, int colStart, int color, int* step);
void	colorGame();
//Prints & Initializers.
const char*	checkColor(int colorNum);
void	printBoard(int* board, int rows, int cols);
void	initializeBoard(int* board, int rows, int cols);
void	randomizeStartingPoints(int* board, int* startValues, int* availableColors, int colors, int cols);
void	printStartingValues(int* startValues, int colors);

#endif
