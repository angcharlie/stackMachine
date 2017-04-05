//Charlie Ang
//May 1, 2016
//CSC 2431 Spring 2016
//Assignment 3
//This program emulates a simple stack machine with the instructions given (add, subtract, multiply, divide)


#include <iostream>

#include "stackMachine.h"

using namespace std;

int main()
{
	stackMachine<double>test;			//try modifying text file with double or some other type of data and see if it still works
	test.readInstructions();	//read instructions from file and emulate 

	/*
	//Testing retrieve function
	cout << test.retrieve(0) << endl;
	cout << test.retrieve(50) << endl;
	cout << test.retrieve(99) << endl;
	cout << test.retrieve(100) << endl; //out of bounds 
	*/

	return 0;
}