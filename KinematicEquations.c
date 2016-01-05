//***********************************************************
//* KinematicEquations.c Created By Kian Gorgichuk			*
//* Copyright (c) 2015 Kian Gorgichuk. All rights reserved. *
//***********************************************************

#include "KinematicEquations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define CHARACTER_LIMIT (5)

//Computational Support Functions:
double quadEquation(double a, double b, double c);
double correctSqrt(double value);
//These functions check if user input is valid:
bool validValue(char* str);
void checkInsideRadical(double value);

double TAViVf(double A, double T, double Vi, double Vf, int solveValue)
{
	double answer;
	switch (solveValue) 
	{
		case 1:
			answer = (Vf - Vi) / A;
			break;
		case 2:
			answer = (Vf - Vi) / T;
			break;
		case 3:
			answer = Vf - (A * T);
			break;
		case 4:
			answer = (A * T) + Vi;
			break;
		default: 
			break;
	}
	return answer;
}
 
double DTViVf(double D, double T, double Vi, double Vf, int solveValue)
{
	double answer;
	switch(solveValue) 
	{
		case 0:
			answer = ( (Vi + Vf) / 2 ) * T ;
			break;
		case 1:
			answer = (2 * D) / (Vi + Vf);
			break;
		case 3: 
			answer = ( (2 * D) / T) - Vf;
			break;
		case 4:
			answer = ( (2 * D) / T) - Vi;
			break;
		default:
			break;
	}	
	return answer;
}

double DAViVf(double D, double A, double Vi, double Vf, int solveValue)
{	
	double answer;
	double insideRadical;
	switch(solveValue)
	{
		case 0:
			answer = ( (Vf * Vf) - (Vi * Vi) ) / ( 2 * A );
			break;
		case 2: 
			answer = ( (Vf * Vf) - (Vi * Vi) ) / ( 2 * D );
			break;
		case 3:
			insideRadical = (Vf * Vf) - (2 * A * D);
			checkInsideRadical(insideRadical);
			answer = correctSqrt(insideRadical);
			break;
		case 4:
			insideRadical = (Vi * Vi) + (2 * A * D);
			checkInsideRadical(insideRadical);
			answer = correctSqrt(insideRadical);
			break;
		default:
			break;
	}
	return answer;
}

double DTAVf(double D, double A, double T, double Vf, int solveValue)
{
	double answer;
	double a, b, c;
	switch(solveValue)
	{	
		case 0:
			answer = (Vf * T) - (0.5 * A * (T * T));
			break;
		case 1:
			if(A == 0) 
			{
				answer = fabs(D / Vf);
			}
			else 
			{
				//Determine and send variables to quadratic equation
				a = (0.5 * A);
				b = ( -1 * Vf);
				c = D;
		
				answer = quadEquation(a,b,c);
			}
			break;
		case 2:
			answer = (D - (Vf * T)) / ( -1 * 0.5 * (T * T));
			break;
		case 4:
			answer = (D + (0.5 * A * (T * T))) / T;
		default:
			break;
		
	}
	return answer;
}

double DTAVi(double D, double A, double T, double Vi, int solveValue)
{
	double answer;
	double a, b, c;
	switch(solveValue) 
	{	
		case 0:
			answer = (Vi * T) + (0.5 * A * (T * T));
			break;
		case 1:
			if(A == 0)
			{
				answer = fabs(D / Vi);
			}
			else
			{
				//Determine and send variables to quadratic equation
				a = (0.5 * A);
				b = Vi;
				c = (-1 * D);

				answer = quadEquation(a,b,c);
			}
			break;
		case 2:
			answer = (D - (Vi * T)) / (0.5 * (T * T));
			break;
		case 3:
			answer = (D - (0.5 * A * (T * T))) / T;
			break;
		default:
			break;	
	}
	return answer;
}


double correctSqrt(double value) {
	value = sqrt(value);
	double answer;
	char s[CHARACTER_LIMIT];
	printf("ERROR: Square Root has Two Valid Answers! \n"); 
	printf("Answer 1 = %f and Answer 2 = %f \n", value, value * -1);
	printf("Please Select The Correct Answer: (1/2): ");
	fgets(s, CHARACTER_LIMIT, stdin);
	strcpy(s, remNewLineChars(s));
	while(!validValue(s))
	{
		printf("Please Select The Correct Answer: (1/2): ");
		fgets(s, CHARACTER_LIMIT, stdin);
		strcpy(s, remNewLineChars(s));
	}
	printf("\n");
	if(strcmp(s, "1") == 0)
	{
		answer = value;
	}
	if(strcmp(s, "2") == 0)
	{
		answer = value * -1;
	}
	return answer;
	
}

double quadEquation(double a, double b, double c)
{
	//Determine Roots
	double root1 = ( (-1 * b) + sqrt( (b * b) - (4 * a * c))) / (2 * a);
	double root2 = ( (-1 * b) - sqrt( (b * b) - (4 * a * c))) / (2 * a);
	
	//If roots are equal
	if(root1 == root2)
		return root1;
	//Both roots are greater than zero
	else if (root1 >= 0 && root2 >= 0)
	{
		char s[CHARACTER_LIMIT];
		printf("ERROR: Quadratic Equation has Two Valid Roots! \n"); 
		printf("Root 1 = %f and Root 2 = %f \n", root1, root2);
		printf("Please Select The Correct Root (1/2): ");
		fgets(s, CHARACTER_LIMIT, stdin);
		strcpy(s, remNewLineChars(s));
		while(!validValue(s))
		{
			printf("Please Select The Correct Root (1/2): ");
			strcpy(s, remNewLineChars(s));
		}
		
		if(strcmp(s, "1") == 0)
		{
			return root1;
		}
		if(strcmp(s, "2") == 0)
		{
			return root2;
		}
	}
	//Return positive root only, because time is always positive
	else if (root1 >= 0 && root2 < 0)
	{
		return root1;
	}
	else 
	{
		return root2;
	}
	
	//If the if statement fails
	return -1;
}

//Determines if selected number is valid (either 1 or 2)
bool validValue(char* str)
{
	if(strcmp(str, "1") == 0)
		return true;
	if(strcmp(str, "2") == 0)
		return true;
	return false;
}

//Remove newline character from input string
char* remNewLineChars(char* str)
{
	char* newStr = (char*)malloc(sizeof(str));
	int len = strlen(str);
	int j = 0;
	int i = 0;
	while(i < len)
	{
		if(str[i] != '\n')
		{
			newStr[j] = str[i];
			j++;
		}
		i++;
	}
	newStr[j] = '\0';
	return newStr;
}

void checkInsideRadical(double value)
{
	if(value < 0)
	{ 	
		printf("ERROR: The Values Entered Produce a Physics Scenario That is Not Possible! \n");
		printf("Press Enter To Exit Program. ");
		getchar();
		exit(EXIT_FAILURE);
	}
}