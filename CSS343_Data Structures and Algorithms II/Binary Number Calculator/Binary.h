#pragma once
/*Jessica Nguyen
CSS 343, Project 1
This class represents a Binary number instance stored as an array of bool values, where each item in the array represents
a single byte in a Binary sequence. Users will be able to construct a Binary number instance either from their choice as an
input item (operator>>), default item, conversion from an integer value, or create a copy of another Binary instance. 
Binary operators include addition (+), subtraction (-), addition to self (+=), subtraction to self (-=), 
assignment (=), check if equal (==) or non-equal(!=), and outputing to the console the full Binary sequence (<<).
Mutator methods include setBit (set to 1), clearBit (set to 0), and toggleBit (switch from 1 to 0, vice versa).
Accessor method include getBit (what value the byte is at a certain specified location). 
*/


#include <iostream>
using namespace std;

class Binary {

private:
	bool sign;	//true if Binary is negative, false if otherwise
	bool* bits; //stores array representing bits
	int size;	//stores size of array


	/*
	private helper: convertToBinary
	Preconditions:  input integer value must be valid (input >= INT_MIN && input <= INT_MAX) and is not null
	Postconditions: returns a string representation of the Binary sequence of the converted int input
	*/
	string convertToBinary(const int input);

	/*
	private helper: convertToDecimal
	Preconditions: input Binary is a valid, initialized Binary object type
	Postconditions: returns an int decimal value converted from the input Binary object
	*/
	int convertToDecimal(const Binary& input); //private method to help convert from Binary to decimal
	
	/*firstNonZeroHelper
	Preconditions: a Binary instance exists with instantiated size and sign values
	Postconditions: if after changing the bit values of certain entries and the Binary happens to become zero, change the sign to positive
					so the output stream doesn't print a negative zero value
					This method acts as a safe guard against unintentionally printing -0.
	*/
	void firstNonZeroHelper();
public:

	/*
	default constructor
	Postconditions: sign value is defaut to false (non-negative);
					size is default to 1;
					bits array is set to represent 0.
	*/
	Binary();

	/*
	constructor with integer input
	Preconditions: input integer value must be valid (input >= INT_MIN && input <= INT_MAX) and is not null
	Postconditions: the int input will be converted into its Binary form and stored as a new Binary instance;
					the size of the corresponding bits array will equal the length of the Binary sequence;
					if input < 0, sign = true
	*/
	Binary(int);
	bool operator<(const Binary& input) const;
	/*
	copy constructor
	Preconditions: input Binary is a valid, initialized Binary object type
	Postconditions: a deep copy of the input Binary instance will be copied into a newly constructed Binary object, 
					including the array with all associated bit values; sign and size values.
	*/
	Binary(const Binary&);

	/*
	destructor
	Postconditions: all contents of current Binary object are deleted in memory 
	*/
	~Binary();

	//operator overloads
	/*
	operator+
	Preconditions: input Binary is a valid, initialized Binary object type
	Postconditions: a Binary object is returned as the sum of this Binary instance and input Binary instance;
					its sign will reflect appropriately whether the number is positive or negative.
	*/
	Binary operator+(const Binary&);

	/*
	operator-
	Preconditions:input Binary is a valid, initialized Binary object type
	Postconditions: a Binary object is returned as the difference between this Binary instance and input Binary instance;
					its sign will reflect appropriately whether the number is positive or negative.
	*/
	Binary operator-(const Binary&);

	/*
	assignment operator=
	Preconditions: input Binary is a valid,initialized Binary object type
	Postconditions: the calling Binary object is assigned to the current Binary object 
					and both objects share the same memory address
	*/
	const Binary& operator=(const Binary&);
	
	/*
	operator+=
	Preconditions: input Binary is a valid,initialized Binary object type
	Postconditions: this current Binary is set to the sum of this Binary instance and input Binary instance;
					its sign will reflect appropriately whether the number is positive or negative;
					its size will reflect the newly resulted sum.
	*/
	const Binary& operator+=(const Binary&);

	/*
	operator-=
	Preconditions: input Binary is a valid,initialized Binary object type
	Postconditions: this current Binary is set to the difference of this Binary instance and input Binary instance;
					its sign will reflect appropriately whether the number is positive or negative;
					its size will reflect the newly resulted difference.
	*/
	const Binary& operator-=(const Binary&);
	
	/*
	operator==
	Preconditions: input Binary is a valid,initialized Binary object type
	Postconditions: returns true if this Binary instance and input Binary have equal sign, size, and
					same sequence of Binary representation.
					returns false otherwise.
	*/
	bool operator==(const Binary&);
	
	/*
	operator!=
	Preconditions:	input Binary is a valid,initialized Binary object type
	Postconditions: returns false if this Binary instance and input Binary have equal sign, size, and
					same sequence of Binary representation.
					returns true otherwise.
	*/
	bool operator!=(const Binary&);

	/*
	output operator<<
	Preconditions: input Binary is a valid Binary object type
	Postconditions: the console outputs the Binary sequence representing the current Binary instance;
					if the Binary number is negative, a dash ("-") precedes the Binary sequence.
	*/
	friend ostream& operator<<(ostream&, const Binary&);

	//accessor methods
	/*
	getBit
	Preconditions: input int is valid, not out of bounds of the bits array (int >=0 && int < size)
	Postconditions: a value representing the bit value at the specified index location is returned.
					if the bit is 1, getBit returns true;
					if the bit is 0, getBit returns false;
					if the input is out of bounds of the bits array, getBit returns false
	*/
	bool getBit(int);
	
	//mutator methods
	/*
	input operator>>
	Preconditions: input Binary is a valid Binary object type
	Postconditions: input console stores the value of the input integer from user's keyboard as a Binary instance
	*/
	 friend istream& operator>>(istream&, Binary& n);
	
	/*
	setBit
	Preconditions:	input int is valid, not out of bounds of the bits array (int >=0 && int < size)
	Postconditions: sets bit value at specified index to true (1)
					if input int is out of bounds, input n is ignored
	*/
	void setBit(int);

	/*
	clearBit
	Preconditions:	input int is valid, not out of bounds of the bits array (int >=0 && int < size)
	Postconditions:	sets bit value at specified index to false (0)
					if input int is out of bounds, input n is ignored
	*/
	void clearBit(int);

	/*
	toggleBit
	Preconditions:	input int is valid, not out of bounds of the bits array (int >=0 && int < size)
	Postconditions: switches bit value at specified index to true (1) if it was previously false (0) and vice versa
					if input int is out of bounds, input n is ignored
	*/
	void toggleBit(int);

};