//Charlie Ang
//May 1, 2016
//CSC 2431 Spring 2016
//Assignment 3
//Header file for stackMachine class that emulates a simple stack 
//machine with the instructions given (add, subtract, multiply, divide)

#ifndef H_STACKMACHINE
#define H_STACKMACHINE

#include <iostream>
#include <cassert>
#include <stack>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//********************stackMachine header********************
template <class Type>
class stackMachine
{
public:
	
	//Default constructor 
	//Postcondition: Stack is empty and memory array contans all zeroes
	stackMachine();

	//Pushes a value from memory at location N onto the top of the stack
	//Postcondition: Value from memory at location N is pushed on top of stack
	void push(int N);

	//Pops from the top of the stack into memory location N
	//Postcondition: Value from top of stack is placed into memory location N
	void pop(int N);

	//Add
	//Postcondition: Pops the top two elements off stack, adds, then puts result on top of stack
	void add();

	//Subtract 
	//Postcondition: Pops the top two elements off stack, subtracts, then puts result on top of stack
	void subtract();

	//Multiply
	//Postcondition: Pops the top two elements off stack, multiplies, then puts result on top of stack
	void mulitply();

	//Divide 
	//Postcondition: Pops the top two elements off stack, divides, then puts result on top of stack
	void divide();

	//Read instructions from a file line-by-line
	//Postcondition: Read instructions from a file line-by-line, and call the appropriate methods
	void readInstructions();

	//Method to retrieve an element from memory at the specified position
	//POstcondition: Returns element from memory at specified position
	Type retrieve(int pos);


private:
	static const int MAX = 100;		//100 elements for stack's machine memory
	Type myarr[MAX];				//statically allocated array of 100 elements 
	stack<Type> myStack;			//stack to keep track of operands for stack instructions
};


//****************************************stackMachine implementation***************************************************

//Default constructor 
template <class Type>
stackMachine<Type>::stackMachine()
{
	for (int i = 0; i < MAX; i++)	//array contains all zeroes 
	{
		myarr[i] = 0;
	}

	while (!myStack.empty())	//if stack is not empty, then pop all elements off stack 
	{
		myStack.pop();
	}
}

//Push
template <class Type>
void stackMachine<Type>::push(int N)
{
	if (N >= 0 && N < MAX)	//N within bounds of array
	{
		myStack.push(myarr[N]);
	}
	else
	{
		cout << "Value from memory location N is out of bounds." << endl;
	}
}

//Pop
template <class Type>
void stackMachine<Type>::pop(int N)
{
	if ((N >= 0 && N < MAX) && !myStack.empty())	//N within bounds of array and stack is not empty 
	{
		myarr[N] = myStack.top();
		myStack.pop();
	}
	else
	{
		cout << "Memory location N is out of bounds or the stack is empty." << endl;
	}
}

//Add
template <class Type>
void stackMachine<Type>::add()
{
	Type op1, op2;

	if (myStack.empty())
	{
		cout << "Not enough operands." << endl;
	}
	else												//stack is not empty										
	{
		op2 = myStack.top();							//righthand operand
		myStack.pop();									//pop the top value off stack 

		if (myStack.empty())
		{
			cout << "Not enough operands." << endl;
		}
		else											//there are more elements in stack
		{
			op1 = myStack.top();						//lefthand operand 
			myStack.pop();								//pop the top value off stack 

			myStack.push(op1 + op2);					//push the result onto top of stack 
		}
	}
}

//Subtract
template <class Type>
void stackMachine<Type>::subtract()
{
	Type op1, op2;

	if (myStack.empty())
	{
		cout << "Not enough operands." << endl;
	}
	else												//stack is not empty										 
	{
		op2 = myStack.top();							//righthand operand
		myStack.pop();									//pop the top value off stack 

		if (myStack.empty())
		{
			cout << "Not enough operands." << endl;
		}
		else											//there are more elements in stack									
		{
			op1 = myStack.top();						//lefthand operand 
			myStack.pop();								//pop the top value off stack 

			myStack.push(op1 - op2);					//push the result onto top of stack 
		}
	}
}

//Multiply
template <class Type>
void stackMachine<Type>::mulitply()
{
	Type op1, op2;

	if (myStack.empty())
	{
		cout << "Not enough operands." << endl;
	}
	else								//stack is not empty
	{
		op2 = myStack.top();			//righthand operand
		myStack.pop();					//pop the top value off stack 
		if (myStack.empty())
		{
			cout << "Not enough operands." << endl;
		}
		else							//there are more elements in stack 
		{	
			op1 = myStack.top();		//lefthand operand 
			myStack.pop();				//pop the top value off stack 

			myStack.push(op1 * op2);	//push the result onto top of stack 
		}
	}
}

//Divide
template <class Type>
void stackMachine<Type>::divide()
{
	Type op1, op2;

	if (myStack.empty())
	{
		cout << "Not enough operands." << endl;
	}
	else												//stack is not empty
	{
		op2 = myStack.top();							//righthand operand
		myStack.pop();									//pop the top value off stack 

		if (myStack.empty())
		{
			cout << "Not enough operands." << endl;
		}
		else											//there are more elements in stack 
		{
			op1 = myStack.top();						//lefthand operand 
			myStack.pop();								//pop the top value off stack 

			if (op2 != 0)								//cannot divide by 0
			{
				myStack.push(op1 / op2);				//push the result onto top of stack 
			}
			else
			{
				cout << "Division by 0." << endl;
			}	
		}
	}
}

//Read instructions
template <class Type>
void stackMachine<Type>::readInstructions()
{
	//Declare stream variable
	ifstream inFile;

	//Ask user for the name of the data file they wish to use
	string inData;
	cout << "Enter the input file: ";
	cin >> inData;
	cout << endl;

	inFile.open(inData);	//opens input file inData  

	if (inFile.fail())		//if file can't be opened 
	{
		cout << "Error Opening File" << endl;
		exit(1);
	}

	//*********************************after opening file*********************************

	string fileText;
	getline(inFile, fileText);	//grabs next line and store in fileText 
	if (fileText == ".data")
	{
		string dataInMemory;
		getline(inFile, dataInMemory);	//string with data in memory is stored in dataInMemory 
		int index = 0;	//index in memory array
		int space = 0;	//finding index of first space 
		while (space != -1 && dataInMemory.size() != 0)	//while there is another space and the string isn't empty  
		{
			myarr[index] = (Type)stod(dataInMemory);	//Type casting
			space = dataInMemory.find(" ");	//find index of space...returns -1 if no space is found 
			dataInMemory = dataInMemory.substr(space + 1);	//chop off the already retrived data value 
			index++;	//increment index for placing into memory array 
		}

		/*ONLY WORKS IF DATA IS ALL ONE DIGIT NUMBERS 
		string dataInMemory;
		int lengthDataInMemory = 0;
		getline(inFile, dataInMemory);	//string with data in memory is stored in dataInMemory 
		lengthDataInMemory = ((dataInMemory.length()) / 2) + 1;	//6 for number of elements in data 
		//cout << lengthDataInMemory << endl;
		int pos = 0;
		for (int i = 0; i < lengthDataInMemory; i++)
		{
			Type temp = stod(dataInMemory.substr(pos, 1));	//converts memory string to double to place in array 
			myarr[i] = temp;
			//cout << dataInMemory.substr(pos, 1) << endl;
			pos += 2;
		}
		*/

	}
	else //text does not have a .data field...meaning it is an invalid text file
	{
		cout << "Invalid text file. Please input an appropriate text file with appropriate field." << endl;
	}

	//***************************************after processing data field******************************************************

	string dataInText;
	getline(inFile, fileText);
	if (fileText == ".text")
	{
		while (getline(inFile, dataInText))
		{
			//find function returns std::string::npos if string is not found....so != means a match is found
			if ((dataInText.find("push") != std::string::npos) || (dataInText.find("pop") != std::string::npos))	//if push or pop, then separate values 
			{
				int found = dataInText.find(' ');
				//cout << found << endl;	//FOR TESTING PURPOSES 
				string instruction = dataInText.substr(0, found);	//retrieve substring 
				int N = stod(dataInText.substr(found));
				//cout << instruction <<  " " << N << endl; //FOR TESTING PURPOSES 

				if (instruction == "push")
				{
					push(N);	//push value in memory location called value
				}

				if (instruction == "pop")
				{
					pop(N);
				}
			}
			else //instructions can only be add, subtract, multiply, divide 
			{
				//cout << "different instructions" << endl;	//FOR TESTING PURPOSES 
				if (dataInText == "add")
				{
					add();
					//cout << "added" << endl; //FOR TESTING PURPOSES
				}
				if (dataInText == "subtract") //FOR TESTING PURPOSES
				{
					subtract();
					//cout << "subtracted" << endl;
				}
				if (dataInText == "multiply") //FOR TESTING PURPOSES
				{
					mulitply();
					//cout << "multiplied" << endl;
				}
				if (dataInText == "divide") 
				{
					divide();
					//cout << "divided" << endl; //FOR TESTING PURPOSES
				}
			}
		}
	}
	else //text file doesn't have .text field 
	{
		cout << "Invalid text file. Please input an appropriate text file with appropriate field." << endl;
	}
	
	//PRINTING OUT THE ENTIRE CONTENTS OF THE STACK MACHINE'S MEMORY 
	int index = 0;
	//cout << fixed << showpoint;
	for (int i = 0; i < 10; i++)	//10 rows 
	{
		for (int j = 0; j < 10; j++)	//10 elements per row 
		{
			cout << right << setw(6) <<setprecision(2) << fixed << myarr[index] << " ";	//formatted output to work with int and doubles
			index++;
		}
		cout << endl;
	}
	inFile.close();	//close input file 	
}

template <class Type>
Type stackMachine<Type>::retrieve(int pos)
{
	if (pos >= 0 && pos < MAX)	//N within bounds of array
	{
		return myarr[pos];
	}

	//prints message if pos is out of bounds 
	cout << "Value from memory location pos is out of bounds." << endl;
	return NULL;
}

#endif