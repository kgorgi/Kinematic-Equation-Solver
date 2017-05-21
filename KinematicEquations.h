//***********************************************************
//* KinematicEquations.h Created By Kian Gorgichuk          *
//* Copyright (c) 2017 Kian Gorgichuk. All rights reserved. *
//***********************************************************

#ifndef KINEMATIC_EQUATIONS
#define KINEMATIC_EQUATIONS

//The order to variables D, A, T, Vi, Vf 
//Note: the solveValue parameter maintains this order 

//Ex: Function ATVfVi contains the variables: acceleration, time, final velocity, initial velocity
//    and will compute the answer as determined by solveValue.

double TAViVf(double A, double T, double Vi, double Vf, int solveValue);
double DTViVf(double D, double T, double Vi, double Vf, int solveValue);
double DAViVf(double D, double A, double Vi, double Vf, int solveValue);
double DTAVf(double D, double A, double T, double Vf, int solveValue);
double DTAVi(double D, double A, double T, double Vi, int solveValue);

//Function removes new line (\n) characters from a string
char* remNewLineChars(char* str);

#endif