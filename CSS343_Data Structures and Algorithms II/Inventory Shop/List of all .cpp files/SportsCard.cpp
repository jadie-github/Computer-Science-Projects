/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a base class for SportsCards available in the Shop.
Clients will be able to construct a SportsCard,
compare 2 SportsCards (==,!=,<,>), and print the SportsCard's atrributes.
*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "SportsCard.h"
using namespace std;

/*constructor
Postconditions: instantiate a SportsCard object
*/
SportsCard::SportsCard() {
	this->year = 0;	
	this->grade ="";				
	this->player = "";			
	this->manufacturer = "";
}

/*create: factory method that determines type of SportsCard to be initialized at runtime
Preconditions: type is valid
Postconditions: appropriate SportsCard that is hashed from the input type with be returned
*/
SportsCard* SportsCard::create(const string description) {
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

	SportsCard* s = new SportsCard;

	//construct values for this SportsCard object
	s->year = atoi(result[0].c_str());	//convert string year to int year
	s->grade = result[1];				//convert string grade to int grade 
	s->player = result[2];				//stores string type
	s->manufacturer = result[3];		//stores string manufacturer

	return s;
}

/*
assignment operator=
Preconditions: input Item is initialized
Postconditions: the calling Item data is assigned to the current Item
*/
const SportsCard& SportsCard::operator=(const Item& input) {
	const SportsCard& s = static_cast<const SportsCard&>(input);
	if (this != &input) {
		// check for self assignment
		this->year = s.year;
		this->grade = s.grade;
		this->player = s.player;
		this->manufacturer = s.manufacturer;
	}
	return *this;
}

/*
operator==
Preconditions: input SportsCard is a valid, initialized SportsCard object type
Postconditions: returns true if 2 SportsCards are the same "rank" in the inventory system
				returns false otherwise
*/
bool SportsCard::operator==(const Item& input) const {

	const SportsCard& c = static_cast<const SportsCard&>(input);

	return (this->year == c.year) && (this->grade == c.grade) && (this->player == c.player) && (this->manufacturer == c.manufacturer);
}

/*
operator!=
Preconditions: input SportsCard is a valid, initialized SportsCard object type
Postconditions: returns false if if 2 SportsCards are not the same "rank" in the inventory system
				returns true otherwise
*/
bool SportsCard::operator!=(const Item& input) const {
	return !(operator==(input));
}

/*
operator<
Preconditions: input SportsCard is a valid, initialized SportsCard object type
Postconditions: returns true if input SportsCard is "higher ranked" than this SportsCard
				returns false otherwise
*/
bool SportsCard::operator<(const Item& input) const {

	const SportsCard& s = static_cast<const SportsCard&>(input);

	if (this->player < s.player) {
		return true;
	}

	if (this->player > s.player) {
		return false;
	}

	if (this->year < s.year) {
		return true;
	}

	if (this->year > s.year) {
		return false;
	}

	if (this->manufacturer < s.manufacturer) {
		return true;
	}

	if (this->manufacturer > s.manufacturer) {
		return false;
	}

	if (this->grade < s.grade) {
		return true;
	}

	if (this->grade > s.grade) {
		return false;
	}

	//if reach here, they are both equal
	return false;
}

/*
operator>
Preconditions: input SportsCard is a valid, initialized SportsCard object type
Postconditions: returns true if input SportsCard is "less ranked" than this SportsCard
				returns false otherwise
*/
bool SportsCard::operator>(const Item& input) const {
	return !(operator<(input));
}

/*getType: returns type of item
Preconditions: calling Item is initialized
Postconditions: if type is Coin, returns M
				if type is Comic, returns C
				if type if SportsCard, returns S
*/
const string SportsCard::getType() const {
	return "S";
}

/*print: helps print Item's attributes
Preconditions: initialized Item object
Postconditions: outputs Item's atrributes depending on the type inputted
*/
void SportsCard::print(ostream& output, const Item& input) const {

	const SportsCard& s = static_cast<const SportsCard&>(input);

	output << s.year << ", " << s.grade << ", " << s.player << ", " << s.manufacturer;
}