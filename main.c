#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "questionInput.h"
#include "macros.h"

int mainMenu()
{

	char selection;
	int choice;
	
	do {
		printf("Please choose one of the following options\n");
		printf("S/s - Biggest Matrix Sum.\n");
		printf("C/c - Color Game.\n");
		printf("E/e - Quit\n");
		
		scanf(" %c", &selection);
		if ((selection == 'S') || (selection == 's'))
		{
			choice = BIGGEST_MATRIX;
		}
		else if ((selection == 'C') || (selection == 'c'))
		{
			choice = COLOR_GAME;
		}
		else if ((selection == 'E') || (selection == 'e'))
		{
			choice = EXIT_CHOICE;
		}
		else
		{
			printf("\nInvalid choice, please try again.\n");
			choice = WRONG_CHOICE;
		}
	} 
	while(choice == WRONG_CHOICE);
	return choice;
}

void printBye()
{
	printf("Bye bye!\n");
}

int  main(void)
{
	int choice;
	
	srand((unsigned)time(NULL)); // seed for random number generation
	
	do {
		choice = mainMenu();
		switch(choice)
		{
		case BIGGEST_MATRIX:
			q1_biggest();
			break;
		case COLOR_GAME:
			q2_colorGame();
			break;
		case EXIT_CHOICE:
			printBye();
			break;
		}
	} while (choice != EXIT_CHOICE);
	return EXIT_SUCCESS;
}
