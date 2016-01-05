//***********************************************************
//* KinematicSolver.c Created By Kian Gorgichuk			    *
//* Copyright (c) 2015 Kian Gorgichuk. All rights reserved. *
//***********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "KinematicEquations.h"

#define CHARACTER_LIMIT (101)

void exceptionHandling(char * message); 
bool validAnswer(char* str);
char* remNewLineChars(char* str);

int main()
{
	//Set Command Prompt Size
	system("mode 100,40"); 
	
	//Loop back program in order to due multiple calculations
	bool exitProgram = false;
	do 
	{
		
		char userValues[5][CHARACTER_LIMIT];
		
		//Ask Values From User
		system("CLS");
		printf("**********************************************\n");
		printf("* Welcome to the Kinematic Equation Solver!  *\n");
		printf("*         Created By Kian Gorgichuk          *\n");
		printf("*               Version 2.0.0                *\n");
		printf("**********************************************\n\n");
		
		printf("Please enter the values below. Up to %d digits is allowed.\n", CHARACTER_LIMIT - 1);
		printf("Use \"SOLVE\" for the value you would like to solve for. \n");
		printf("One value must be left blank, as only three values are required. \n\n");
		
		//Scientific Notation
		printf("Note: Scientific Notation is supported in the format: \"123e5\". \n\n");
		
		/* Enter Values for Computation 
		 * Please note that the sequences of variables will remain
		 * consistent throughout the program: D, T, A, Vi, Vf 
		 */
		
		printf("Please enter the displacement in the units meters: ");
		fgets(userValues[0], CHARACTER_LIMIT, stdin);

		printf("Please enter the time in the units seconds: ");
		fgets(userValues[1], CHARACTER_LIMIT, stdin);
		
		printf("Please enter the acceleration in the units meters per second squared: ");
		fgets(userValues[2], CHARACTER_LIMIT, stdin);

		printf("Please enter the initial velocity in the units meters per second: ");
		fgets(userValues[3], CHARACTER_LIMIT, stdin);
		
		printf("Please enter the final velocity in the units meters per second: ");
		fgets(userValues[4], CHARACTER_LIMIT, stdin);
		printf("\n");
		
		
		//Initialize Values for Computation
		int blankValue = -1;
		int solveValue = -1;
		bool solveSelected = false; 
		bool blankSelected = false;
		
		double D;
		double A;
		double T;
		double Vi;
		double Vf;
		double answer;
		
		int i;
		for(i = 0; i < 5; i++) 
		{
			char* value = remNewLineChars(userValues[i]);
			if(strcmp(value,"SOLVE") == 0) //Value to Solve
			{
				if(solveSelected == false) 
				{
					solveValue = i;
					solveSelected = true;	
				} 
				else 
					exceptionHandling("Multiple Variables Selected to Solve!");
			}
			else if(value[0] == '\0') //Blank Value
			{
				if(blankSelected == false) 
				{
					blankValue = i;
					blankSelected = true;
				}
				else
					exceptionHandling("Too Many Variables Left Blank!");
			}
			else //Valid Value
			{
				switch(i) 
				{
					case 0: 
						D = strtod(value, NULL);
						break;
					case 1:
						T = strtod(value, NULL);
						if(T <= 0)
							exceptionHandling("Time Cannot Be Zero or Negative!");
						break;
					case 2:
						A = strtod(value, NULL);
						break;
					case 3: 
						Vi = strtod(value, NULL);
						break;
					case 4: 
						Vf = strtod(value, NULL);
						break;
					default:
						break;
				}
			}
			value = NULL;
		}
			
		// Pass the variables into the function that does not contain the blank variable
		// Ex: Function ATViVf contains the variables: acceleration, time, final velocity, initial velocity

		switch(blankValue) 
		{
			case 0: 
				answer = TAViVf(A, T, Vi, Vf, solveValue);
				break;
			case 1:
				answer = DAViVf(D, A, Vi, Vf, solveValue);
				break;
			case 2:
				answer = DTViVf(D, T, Vi, Vf, solveValue);
				break;
			case 3: 
				answer = DTAVf(D, A, T, Vf, solveValue);
				break;
			case 4:
				answer = DTAVi(D, A, T, Vi, solveValue);
				break;
			default: 
				exceptionHandling("Four Variables Contain Values!");
				break;
		}
		
		//Scientific Notation?
		bool useScientif;
		printf("Would you like to print the answer in Scientific Notation? (Y/N): ");
		
		char s[CHARACTER_LIMIT / 2];
		fgets(s, CHARACTER_LIMIT / 2, stdin);
		strcpy(s, remNewLineChars(s));
		
		while(!validAnswer(s))
		{
			printf("Would you like to print the answer in Scientific Notation? (Y/N): ");
			fgets(s, CHARACTER_LIMIT / 2, stdin);
			strcpy(s, remNewLineChars(s));
		}
		if( (s[0] == 'Y') || (s[0] == 'y') )
			useScientif = true;
		else 
			useScientif = false;
		
		printf("\n");
		
		//Print Answer
		switch(solveValue)
		{
			case 0:
				if (useScientif)
					printf("The displacement is: %e meters\n", answer);
				else 
					printf("The displacement is: %f meters\n", answer);
				break;
			case 1:
				if (useScientif)
					printf("The time is: %e seconds\n", answer);
				else 
					printf("The time is: %f seconds\n", answer);
				break;
			case 2:
				if (useScientif)
					printf("The acceleration is: %e meters per second squared\n", answer);
				else 
					printf("The acceleration is: %f meters per second squared\n", answer);
				break;
			case 3:
				if (useScientif)
					printf("The initial velocity is: %e meters per second\n", answer);
				else 
					printf("The initial velocity is: %f meters per second\n", answer);
				break;
			case 4:
				if (useScientif)
					printf("The final velocity is: %e meters per second\n", answer);
				else 
					printf("The final velocity is: %f  meters per second\n", answer);
				break;
			default:
				exceptionHandling("Did Not Select A Value to Solve!");
				break;
		}
		
		//Ask to Run Program Again	
		printf("\nWould you like to do another calculation? (Y/N): ");
		
		char exitS[CHARACTER_LIMIT / 2];
		fgets(exitS, CHARACTER_LIMIT / 2, stdin);
		strcpy(exitS, remNewLineChars(exitS));
		
		while(!validAnswer(exitS))
		{
			printf("Would you like to do another calculation? (Y/N): ");
			fgets(exitS, CHARACTER_LIMIT / 2, stdin);
			strcpy(exitS, remNewLineChars(exitS));
		}
		if( (exitS[0] == 'Y') || (exitS[0] == 'y') )
		{
			blankValue = -1;
			solveValue = -1;
			solveSelected = false; 
			blankSelected = false;
		}
		else 
			exitProgram = true;
		printf("\n");
	
	} while (!exitProgram);
	
	return EXIT_SUCCESS;
}

//Function that displays exception message and exits program 
void exceptionHandling(char* message) 
{	
	printf("ERROR: %s \n", message);
	printf("Press Enter To Exit Program. ");
	getchar();
	exit(EXIT_FAILURE);
}
 
//Function that determines if user entered valid input in a y/n question. 
bool validAnswer(char* str)
{
	if(strcmp(str, "Y") == 0)
		return true;
	if(strcmp(str, "y") == 0)
		return true;
	if(strcmp(str, "N") == 0)
		return true;
	if(strcmp(str, "n") == 0)
		return true;
	return false;
}