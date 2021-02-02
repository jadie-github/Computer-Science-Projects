/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a base class for Comics available in the Shop.
Clients will be able to construct a Comic,
compare 2 Comics (==,!=,<,>), and print the Comic's atrributes.
*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Comic.h"
using namespace std;

/*constructor
Postconditions: instantiate a Comic object
*/
Comic::Comic() {
	this->year = 0;	
	this->grade = "";					
	this->title = "";			
	this->publisher = "";
}

/*create: factory method that determines type of Comic to be initialized at runtime
Preconditions: type is valid
Postconditions: appropriate Comic that is hashed from the input type with be returned
*/
Comic* Comic::create(const string description) { // 1938, Mint, Superman, DC
	vector<string> result;

	stringstream s_stream(description); //create string stream from the string

	while (s_stream.good()) {
		string substr;
		getline(s_stream, substr, ','); //get first string delimited by comma
		s_stream.get(); 			    //discard space 
		result.push_back(substr);
	}

	if (atoi(result[0].c_str()) < 0) {
		cout << "Invalid year " << atoi(result[0].c_str()) << endl;
		return nullptr;
	}

	Comic* c = new Comic;

	//construct values for this Comic object
	c->year = atoi(result[0].c_str());	//convert string year to int year
	c->grade =result[1];				//convert string grade to int grade 
	c->title = result[2];				//stores string type
	c->publisher = result[3];

	return c;
}

/*
assignment operator=
Preconditions: input Item is initialized
Postconditions: the calling Item data is assigned to the current Item
*/
const Comic& Comic::operator=(const Item& input) {
	const Comic& c = static_cast<const Comic&>(input);
	if (this != &input) {
		// check for self assignment
		this->year = c.year;
		this->grade = c.grade;
		this->title = c.title;
		this->publisher = c.publisher;
	}
	return *this;	
}

/*
operator==
Preconditions: input Comic is a valid, initialized Comic object type
Postconditions: returns true if 2 Comics are the same "rank" in the inventory system
				returns false otherwise
*/
bool Comic::operator==(const Item& input) const {

	const Comic& c = static_cast<const Comic&>(input);

	return (this->year == c.year) && (this->grade == c.grade) && (this->title == c.title) && (this->publisher == c.publisher);
}

/*
operator!=
Preconditions: input Comic is a valid, initialized Comic object type
Postconditions: returns false if if 2 Comics are not the same "rank" in the inventory system
				returns true otherwise
*/
bool Comic::operator!=(const Item& input) const {
	return !(operator==(input));
}

/*
operator<
Preconditions: input Comic is a valid, initialized Comic object type
Postconditions: returns true if input Comic is "higher ranked" than this Comic
				returns false otherwise
*/
bool Comic::operator<(const Item& input) const {

	const Comic& c = static_cast<const Comic&>(input);

	if (this->publisher < c.publisher) {
		return true;
	}

	if (this->publisher > c.publisher) {
		return false;
	}

	if (this->title < c.title) {
		return true;
	}

	if (this->title > c.title) {
		return true;
	}

	if (this->year < c.year) {
		return true;
	}

	if (this->year > c.year) {
		return false;
	}

	if (this->grade < c.grade) {
		return true;
	}

	if (this->grade > c.grade) {
		return false;
	}

	//if reach here, they are both equal
	return false;
}

/*
operator>
Preconditions: input Comic is a valid, initialized Comic object type
Postconditions: returns true if input Comic is "less ranked" than this Comic
				returns false otherwise
*/
bool Comic::operator>(const Item& input) const {
	return !(operator<(input));
}

/*getType: returns type of item
Preconditions: calling Item is initialized
Postconditions: if type is Coin, returns M
				if type is Comic, returns C
				if type if SportsCard, returns S
*/
const string Comic::getType() const {
	return "C";
}

/*print: helps print Item's attributes
Preconditions: initialized Item object
Postconditions: outputs Item's atrributes depending on the type inputted
*/
void Comic::print(ostream& output, const Item& input) const {

	const Comic& c = static_cast<const Comic&>(input);

	output << c.year << ", " << c.grade << ", " << c.title << ", " << c.publisher;
}