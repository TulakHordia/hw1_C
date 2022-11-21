#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "functions.h"
#include "macros.h"

int doFindMaxSubMatrix(const int* arr, int rows, int cols, int subRows, int subCols, int* rowStart, int* colStart, int* firstNum)
{
	int maxSubmatrix=0;
	for (int k=0; k<rows-subRows+1; k++)
	{
		for (int l=0; l<cols-subCols+1; l++)
		{
			int currentSum=0;
			for (int i=0; i<subRows; i++)
			{
				for (int j=0; j<subCols; j++)
				{
					currentSum += *(arr+cols*(k+i)+l+j);
					if (currentSum > maxSubmatrix)
					{
						maxSubmatrix = currentSum;
						*rowStart = k;
						*colStart = l;
						*firstNum = *(arr+cols*k+l);
					}
				}
			}
		}
	}
	return maxSubmatrix;
}

void initializeArr(int* arr, int rows, int cols)
{
	int i, j;
	for(i=0; i<rows; i++)
	{
		for(j=0; j<cols; j++)
		{
			// rand() % (max_number + 1 - minimum_number) + minimum_number
			*(arr+cols*i+j) = (rand() % (MAX_RAND_VALUE + 1 - MIN_RAND_VALUE) + MIN_RAND_VALUE); 
		}
	}
}

void printMat(int* arr, int rows, int cols)
{
	int i, j;
	for(i=0; i<rows; i++)
	{
		for(j=0; j<cols; j++)
		{
			printf(" %d",*(arr+cols*i+j));
		}
		printf("\n");
	}
}

void printSubMat(int* arr, int cols, int subRows, int subCols, int rowStart, int colStart)
{
	for (int k=0; k<subRows; k++)
	{
		for (int l=0; l<subCols; l++)
		{
			printf("%d ",*(arr+cols*(k+rowStart)+(l+colStart)));
		}
		printf("\n");
	}
}

void biggestMatrixSum()
{
	// Initialize ints
	int rowsNum, colsNum, subRows, subCols, rowStart, colStart, firstNum;
	
	// Print #defined rows, cols, min&max values.

	printf("Max amount of rows: %d\n",ROWS);
	printf("Max amount of cols: %d\n",COLS);
	printf("Min random value currently set: %d.\n",MIN_RAND_VALUE);
	printf("Max random value currently set: %d.\n",MAX_RAND_VALUE);
	
	// Main matrix rows
	printf("Please enter the rows amount: (max is %d) \n",ROWS);
	scanf("%d",&rowsNum);
	while (rowsNum > ROWS || rowsNum < 1)
	{
		printf("Invalid rows amount, enter a range from 1 to %d.\n",ROWS);
		scanf("%d",&rowsNum);
	}
	
	// Main matrix cols
	printf("Please enter the columns amount: (max is %d) \n",COLS);
	scanf("%d",&colsNum);
	while (colsNum > COLS || colsNum < 1)
	{
		printf("Invalid columns amount, enter a range from 1 to %d.\n",COLS);
		scanf("%d",&colsNum);
	}
	
	// Create main matrix + print rows&cols
	int arr[rowsNum][colsNum];
	printf("Entered rows amount: %d\n",rowsNum);
	printf("Entered columns amount: %d\n",colsNum);
	
	// Initialize + print main matrix
	initializeArr((int*)arr, rowsNum, colsNum);
	printMat((int*)arr, rowsNum, colsNum);
	
	// Sub-Matrix rows
	printf("Enter sub-matrix row amount: \n");
	scanf("%d",&subRows);
	while(subRows < 1 || subRows > rowsNum)
	{
		printf("Invalid rows amount, enter a range from 1 to %d.\n",rowsNum);
		scanf("%d",&subRows);
	}
	
	// Sub-Matrix cols
	printf("Enter sub-matrix cols amount: \n");
	scanf("%d",&subCols);
	while(subCols < 1 || subCols > colsNum)
	{
		printf("Invalid cols amount, enter a range from 1 to %d.\n",colsNum);
		scanf("%d",&subCols);
	}
	
	// Sub-Matrix rows&cols print
	printf("- Sub-Matrix Rows entered: %d.\n- Sub-Matrix Cols entered: %d.\n",subRows,subCols);
	
	//Find the maximum sub-matrix available, find the [i,j], print the matrix:
	printf("Max sum is: %d.\n",doFindMaxSubMatrix((int*)arr, rowsNum, colsNum, subRows, subCols, &rowStart, &colStart, &firstNum));
	printf("Located at: [%d,%d] and is starting with: %d.\n",rowStart,colStart,firstNum);
	printf("Max submatrix is as follows:\n");
	printSubMat((int*)arr, colsNum, subRows, subCols, rowStart, colStart);
}

void initializeBoard(int* board, int rows, int cols)
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			*(board+cols*i+j) = 0; 
		}
	}
}

void printBoard(int* board, int rows, int cols)
{
	int i, j;
	for(i=0; i<BOARD_ROWS; i++)
	{
		for(j=0; j<BOARD_COLS; j++)
		{
			printf(" %d",*(board+BOARD_COLS*i+j));
		}
		printf("\n");
	}
}

void randomizeStartingPoints(int* board, int* startValues, int* availableColors, int colors, int cols)
{
	for (int i=0; i<colors; i++)
	{
		// rand() % (max_number + 1 - minimum_number) + minimum_number
		int x = rand() % (MAX_RAND_BOARD+1-MIN_RAND_BOARD)+MIN_RAND_BOARD, y = rand() % (MAX_RAND_BOARD+1-MIN_RAND_BOARD)+MIN_RAND_BOARD;
		printf("1.) x:%d, y:%d.\n",x,y);
		if (*(board+cols*x+y) == FREE_CELL && *(board+cols*x+y) < cols)
		{
			printf("2.) x:%d, y:%d.\n",x,y);
			*(board+cols*x+y) = availableColors[i];
			*(startValues+2*i+0) = x;
			*(startValues+2*i+1) = y;
		}
		else
		{
			randomizeStartingPoints((int*) board, (int*) startValues, (int*) availableColors,colors,cols);
		}
	}
}

void printStartingValues(int* startValues, int colors)
{
	for (int i=0; i<colors; i++)
	{
		
		printf("Color is: %s, and is located at: [%d,%d]",checkColor(i),*(startValues+2*i+0),*(startValues+2*i+1));
		printf("\n");
	}
	printf("\n");
}

const char* checkColor(int colorNum)
{
	if (colorNum == 0)
	{
		return "Black";
	}
	else if (colorNum == 1)
	{
		return "Dark Gray";
	}
	else if (colorNum == 2)
	{
		return "Light Gray";
	}
	else {
		return 0;
	}
}

void colorGame()
{
	//Create ROWSxCOLS array.
	int board[BOARD_ROWS][BOARD_COLS];
	printf("Current rows amount: %d\n",BOARD_ROWS);
	printf("Current columns amount: %d\n",BOARD_COLS);
	
	//Determine amount of colors.
	int colors=3;
	printf("Colors amount:%d.\n",colors);
	
	//Print, initialize with 0's.
	initializeBoard((int*) board, BOARD_ROWS, BOARD_COLS);
	
	//Initializes starting points & prints the result.
	int startValues[colors][2];
	int availableColors[] = {BLACK, DARK_GRAY, LIGHT_GRAY};
	randomizeStartingPoints((int*)board, (int*)startValues, (int*)availableColors, colors, BOARD_COLS);
	printBoard((int*)board, BOARD_ROWS, BOARD_COLS);
	printStartingValues((int*)startValues, colors);
	
	//Lets start coloring the board!
	colorTheBoard((int*)board, BOARD_ROWS, BOARD_COLS, colors, (int*)startValues);
}

void colorTheBoard(int* board, int rows, int cols, int amountOfColors, int* startValues)
{
	int step=0,rowStart, colStart;
	for (int i=0; i<amountOfColors; i++)
	{
		rowStart=*(startValues+2*i+0);
		colStart=*(startValues+2*i+1);
		int color = i;
		printf("Color is: %s, rowStart is: %d, colStart is: %d.\n",checkColor(i),rowStart,colStart);
		int amountFilled = expandColor((int*)board, rows, cols, rowStart, colStart, color+1, &step);
		printf("\nFilled %d cells with %s color.\n",amountFilled,checkColor(i));
		step++;
	}
	printBoard((int*)board, rows, cols);
}

int expandColor(int* board, int rows, int cols, int rowStart, int colStart, int color, int* step)
{
	int amountFilled=0;
	//int bottom=0, right=0, left=0;
	//Corner indicators
	//int topLeftCorner = *(board+cols*(*rowStart-step-1)+(*colStart-1));
	//int topRightCorner = *(board+cols*(*rowStart-1)+(*colStart+step+1));
	//int bottomLeftCorner = *(board+cols*(*rowStart+step+1)+(*colStart-1));
	//int bottomRightCorner = *(board+cols*(*rowStart+step+1)+(*colStart+step+1));
	//Square color painting
	//int bottomSq = *(board+cols*(*rowStart+step)+(*colStart-step+i));
	//int rightSq = *(board+cols*(*rowStart-step+i)+(*colStart+step));
	//int leftSq = *(board+cols*(*rowStart-step+i)+(*colStart-step));
	
	//Directions.

	//int moveRightBottom = *colStart-*step+bottom;
	//int moveDownRight = *rowStart-*step+right;
	//int moveDownLeft = *rowStart-*step+left;
	//Starting points for painting.

	//int topRightStart = *colStart+*step;
	//int bottomLeftStart = *rowStart+*step;


	for (int top=1; top<=(*step*2)+1; top++)
	{
		int topLeftStart = rowStart-*step-top;
		printf("topLeftStart 1.):%d.\n",topLeftStart);
		if (topLeftStart >= 0 &&  topLeftStart == FREE_CELL && topLeftStart < cols)
		{
			printf("Before change::%d.\n",*(board+cols*(rowStart-*step)+(colStart-*step+top)));
			*(board+cols*(rowStart-*step)+(colStart-*step+top)) = color;
			amountFilled++;
			printf("After change::%d.\n",*(board+cols*(rowStart-*step)+(colStart-*step+top)));
		}
		else
		{
			topLeftStart = rowStart-*step-top;
			printf("topLeftStart 2.):%d.\n",topLeftStart);
		}
	}

	return amountFilled;
}

