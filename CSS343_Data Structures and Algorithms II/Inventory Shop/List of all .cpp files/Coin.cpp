/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a base class for Coins available in the Shop.
Clients will be able to construct a coin,
compare 2 Coins (==,!=,<,>), and print the Coin's atrributes.
*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Coin.h"
using namespace std;

/*constructor
Postconditions: instantiate a Coin object with empty type, 0 year and 0 grade
*/
Coin::Coin() {
	this->type = "";
	this->year = 0;
	this->grade = 0;
}

/*create: factory method that determines type of Coin to be initialized at runtime
Preconditions: type is valid
Postconditions: appropriate Coin that is hashed from the input type with be returned
*/
Coin* Coin:: create(const string description) {
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

	Coin* c = new Coin;

	//construct values for this Coin object
	c->year = atoi(result[0].c_str());	//convert string year to int year
	c->grade = atoi(result[1].c_str());	//convert string grade to int grade 
	c->type = result[2];				//stores string type

	return c;
}

const Coin& Coin::operator=(const Item & input) {
	const Coin& c = static_cast<const Coin&>(input);
	if (this != &input) {
		// check for self assignment
		this->type = c.type;
		this->year = c.year;
		this->grade = c.grade;	
	}
	return *this;
}

/*
operator==
Preconditions: input Coin is a valid, initialized Coin object type
Postconditions: returns true if 2 Coins are the same "rank" in the inventory system
				returns false otherwise
*/
bool Coin::operator==(const Item& input) const {
	
	const Coin& c = static_cast<const Coin&>(input);
	
	return (c.type == this->type) && (c.year == this->year) && (c.grade == this->grade);
}

/*
operator!=
Preconditions: input Coin is a valid, initialized Coin object type
Postconditions: returns false if if 2 Coins are not the same "rank" in the inventory system
				returns true otherwise
*/
bool Coin::operator!=(const Item& input) const {
	return !(operator==(input));
}

/*
operator<
Preconditions: input Coin is a valid, initialized Coin object type
Postconditions: returns true if input Coin is "higher ranked" than this Coin
				returns false otherwise
*/
bool Coin::operator<(const Item& input) const {

	const Coin& c = static_cast<const Coin&>(input);

	if (this->type < c.type) {
		return true;
	}
	
	if (this->type > c.type) {
		return false;
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
Preconditions: input Coin is a valid, initialized Coin object type
Postconditions: returns true if input Coin is "less ranked" than this Coin
				returns false otherwise
*/
bool Coin::operator>(const Item& input) const {
	return !(operator<(input));
}

/*getType: returns type of item
Preconditions: calling Item is initialized
Postconditions: if type is Coin, returns M
				if type is Comic, returns C
				if type if SportsCard, returns S
*/
const string Coin::getType() const {
	return "M";
}

/*print: helps print Item's attributes
Preconditions: initialized Item object
Postconditions: outputs Item's atrributes depending on the type inputted
*/
void Coin::print(ostream& output, const Item& input) const{

	const Coin& c = static_cast<const Coin&>(input);

	output << c.year << ", " << c.grade << ", " << c.type;
}