/*Jessica Nguyen
CSS 343, Project 3
This class represents a single Vertex entity.
Functions users can use include:
Reading in Vertex location from a string;
or printing the Vertex location to the output console.
*/

#include <iostream>
#include <string>
#include "Vertex.h"
using namespace std;

/*
operator<<
Preconditions: input Vertex is initialized
Postconditions: the console outputs the location value of the input Vertex
*/
ostream& operator<<(ostream& output, const Vertex& c) {
	output << c.location;
	return output;
}

/*
operator>>
Preconditions: input Vertex initialized 
Postconditions: input console takes in a location value to store in input Vertex
*/
istream& operator>>(istream& input, Vertex& c) {
	getline(input, c.location, '\n'); //get the whole line 
	
	return input;
}