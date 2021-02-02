/*Jessica Nguyen
CSS 343, Project 2
This class represents a Comparable object which stores a character value.
Users will be able to compare the Comparable's values through operators equal (==), non-equal (!=),
less than (<), greater than (>); outputing to the console the Comparable's character value, and takes in a character
value to store as a Comparable.
*/


#include <iostream>
#include "Comparable.h"
using namespace std;

/*
operator==
Preconditions: input Comparable is a valid, initialized Comparable object type
Postconditions: returns true if input character's ASCII value matches that of this instance's char value
				returns false otherwise
*/
bool Comparable:: operator==(const Comparable& input) const{
	return this->character == input.character;
}

/*
operator!=
Preconditions: input Comparable is a valid, initialized Comparable object type
Postconditions: returns false if input character's ASCII value matches that of this instance's char value
				returns true otherwise
*/
bool Comparable:: operator!=(const Comparable& input) const {
	return !(this->character == input.character);
}

/*
operator<
Preconditions: input Comparable is a valid, initialized Comparable object type
Postconditions: returns true if input character's ASCII value is less than this instance's char value
				returns false otherwise
*/
bool Comparable:: operator<(const Comparable& input) const {
	return this->character < input.character;
}

/*
operator>
Preconditions: input Comparable is a valid, initialized Comparable object type
Postconditions: returns true if input character's ASCII value is more than this instance's char value
				returns false otherwise
*/
bool Comparable:: operator>(const Comparable& input) const {
	return this->character > input.character;
}

/*
operator<<
Preconditions: input Comparable is a valid, initialized Comparable object type
Postconditions: the console outputs the character value of the input Comparable
*/
ostream& operator<<(ostream& output, const Comparable& c) {
	output << c.character;
	return output;
}

/*
operator>>
Preconditions: input Comparable is a valid, initialized Comparable object type
Postconditions: input console takes in a character value to store in input Comparable
*/
istream& operator>>(istream& input, Comparable& c) {
	input >> c.character;
	return input;
}