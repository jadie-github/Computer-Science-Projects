#pragma once
/*Jessica Nguyen
CSS 343, Project 2
This class represents a Comparable object which stores a character value.
Users will be able to compare the Comparable's values through operators equal (==), non-equal (!=),
less than (<), greater than (>); outputing to the console the Comparable's character value, and takes in a character
value to store as a Comparable.
*/

#include <iostream>
using namespace std;

class Comparable {
private:
	char character; //stores a character as a key for the Comparable object
public:
	/*
	operator==
    Preconditions: input Comparable is a valid, initialized Comparable object type
    Postconditions: returns true if input character's ASCII value matches that of this instance's char value
					returns false otherwise
    */
	bool operator==(const Comparable&) const;

	/*
	operator!=
	Preconditions: input Comparable is a valid, initialized Comparable object type
    Postconditions: returns false if input character's ASCII value matches that of this instance's char value
					returns true otherwise
	*/
	bool operator!=(const Comparable&) const;

	/*
	operator<
	Preconditions: input Comparable is a valid, initialized Comparable object type
    Postconditions: returns true if input character's ASCII value is less than this instance's char value
					returns false otherwise
	*/
	bool operator<(const Comparable&) const;

	/*
	operator>
	Preconditions: input Comparable is a valid, initialized Comparable object type
    Postconditions: returns true if input character's ASCII value is more than this instance's char value
					returns false otherwise
	*/
	bool operator>(const Comparable&) const;

	/*
	operator<<
	Preconditions: input Comparable is a valid, initialized Comparable object type
	Postconditions: the console outputs the character value of the input Comparable
	*/
	friend ostream& operator<<(ostream&, const Comparable&);

	/*
	operator>>
	Preconditions: input Comparable is a valid, initialized Comparable object type
	Postconditions: input console takes in a character value to store in input Comparable
	*/
	friend istream& operator>>(istream&, Comparable&);
};