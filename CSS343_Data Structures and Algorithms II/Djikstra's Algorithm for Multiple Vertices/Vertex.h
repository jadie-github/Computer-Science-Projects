#pragma once
/*Jessica Nguyen
CSS 343, Project 3
This class represents a single Vertex entity. 
Functions users can use include:
Reading in Vertex location from a string;
or printing the Vertex location to the output console.
*/

#include <iostream>
using namespace std;

class Vertex {
private:
	string location; //stores a string as the data portion for the Vertex object
public:
	/*
	operator<<
	Preconditions: input Vertex is a valid, initialized Vertex object type
	Postconditions: the console outputs the character value of the input Vertex
	*/
	friend ostream& operator<<(ostream&, const Vertex&);

	/*
	operator>>
	Preconditions: input Vertex is a valid, initialized Vertex object type
	Postconditions: input console takes in a character value to store in input Vertex
	*/
	friend istream& operator>>(istream&, Vertex&);
};