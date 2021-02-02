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
#include "Binary.h"
using namespace std;

/*
default constructor
Postconditions: sign value is defaut to false (non-negative);
				size is default to 1;
				bits integer is set to 0.
*/
Binary::Binary() {
	sign = false;
	size = 1;
	bits = new bool[size];
	bits[0] = false;
}

/*
private helper: convertToBinary
Preconditions:  input integer value must be valid (input >= INT_MIN && input <= INT_MAX) and is not null
Postconditions: returns a string representation of the Binary sequence of the converted int input 
*/
string Binary::convertToBinary(int n) {
	string result = "";

	if (n < INT_MIN && n > INT_MAX) { //returns empty string if input out of bounds
		return result;
	}

	while (n > 0) {
		int digit = n % 2;
		n /= 2;
		result += char('0' + digit);
	}

	return result;
}

/*
constructor with integer input
Preconditions: input integer value must be valid (input >= INT_MIN && input <= INT_MAX) and is not null
Postconditions: the int input will be converted into its Binary form and stored as a new Binary instance;
				the size of the corresponding bits array will equal the length of the Binary sequence;
				if input < 0, sign = true
*/
Binary::Binary(int n) {
	sign = false; //default sign to non-negative

	if (n == 0) { 
		size = 1;
		bits = new bool[size];
		bits[0] = false;
		return;
	}

	//at this point, n != 0
	
	if (n < 0) { //if n is negative
		sign = true; 
		n *= -1;
	}
	
	string result = convertToBinary(n);
	//result stores the backwards Binary value for easier insertation to the bits array

	size = result.size();
	bits = new bool[size]; 
	for (int i = 0; i < size; i++) { 
		if (result.at(i) == '0') {
			bits[i] = false;
		}
		else {
			bits[i] = true;
		}
	}

}

/*
copy constructor
Preconditions: input Binary is a valid, initialized Binary object type
Postconditions: a deep copy of the input Binary instance will be copied into a newly constructed Binary object,
				including the array with all associated bit values; sign and size values.
*/
Binary::Binary(const Binary& n) {
	sign = n.sign;
	size = n.size;
	bits = new bool[size];
	bits[0] = false; //by default
	
	for (int i = 0; i < size; i++) {
		bits[i] = n.bits[i];
	}
}

/*
destructor
Postconditions: all contents of current Binary object are deleted in memory
*/
Binary::~Binary() {
	sign = false;
	size = 0;
	delete [] bits;
	bits = nullptr;
}

/*
private helper: convertToDecimal
Preconditions: input Binary is a valid, initialized Binary object type
Postconditions: returns an int decimal value converted from the input Binary object
*/
int Binary::convertToDecimal(const Binary& n) {
	
	int ans = 0;

	// Initializing base value to 1, aka 2^0 
	int base = 1;

	for (int i = 0; i < n.size; i++){
		if (n.bits[i] == true) {
			ans += base;
		}
		base*= 2; //increment the value to be added by a multiple of 2 every iteration
	}
	if (n.sign) { ans *= -1; } //multiply to -1 if number is negative

	return ans;
}

//operator overloads
/*
operator+
Preconditions: input Binary is a valid, initialized Binary object type
Postconditions: a Binary object is returned as the sum of this Binary instance and input Binary instance;
				its sign will reflect appropriately whether the number is positive or negative.
*/
 Binary Binary::operator+(const Binary& n) {
	
	int first = convertToDecimal(*this);
	int second = convertToDecimal(n);

	int result = first + second;
	
	return Binary(result);
}

 /*
 operator-
 Preconditions:input Binary is a valid, initialized Binary object type
 Postconditions: a Binary object is returned as the difference between this Binary instance and input Binary instance;
				 its sign will reflect appropriately whether the number is positive or negative.
 */
 Binary Binary::operator-(const Binary& n){
	int first = convertToDecimal(*this);
	int second = convertToDecimal(n);

	int result = first - second;

	return Binary(result);
}

 /*
 assignment operator=
 Preconditions: input Binary is a valid,initialized Binary object type
 Postconditions: the calling Binary object is assigned to the current Binary object
				 and both objects share the same memory address
 */
const Binary& Binary::operator=(const Binary& n) {
	if (this != &n) {
		// check for self assignment
		delete[] bits; //delete current memory
		sign = n.sign;
		size = n.size; //resize
		bits = new bool[size];

		//copy over the input array
		for (int i = 0; i < size; i++) {
			bits[i] = n.bits[i];
		}
	}
	return *this;
}

/*
operator+=
Preconditions: input Binary is a valid,initialized Binary object type
				its sign will reflect appropriately whether the number is positive or negative;
				its size will reflect the newly resulted sum.
*/
const Binary& Binary::operator+=(const Binary& n) {
	*this = *this + n;
	return *this;
}

/*
operator-=
Preconditions: input Binary is a valid,initialized Binary object type
Postconditions: this current Binary is set to the difference of this Binary instance and input Binary instance;
				its sign will reflect appropriately whether the number is positive or negative;
				its size will reflect the newly resulted difference.
*/
const Binary& Binary::operator-=(const Binary& n) {
	*this = *this - n;
	return *this;
}

/*
operator==
Preconditions: input Binary is a valid,initialized Binary object type
Postconditions: returns true if this Binary instance and input Binary have equal sign, size, and
				same sequence of Binary representation.
				returns false otherwise.
*/
bool Binary::operator==(const Binary& n) {

	//finds where the first non-zero entry is so we can compare the 2 arrays starting with first nonzero entry
	int firstNonZero = -1;
	for (int i = n.size - 1; i >= 0; i--) {
		if (n.bits[i]) {
			firstNonZero = i;
			break;
		}
	}

	int firstNonZero2 = -1;
	for (int i = this->size - 1; i >= 0; i--) {
		if (this->bits[i]) {
			firstNonZero2 = i;
			break;
		}
	}

	if (sign != n.sign || firstNonZero != firstNonZero2) {
		//compare the 2 indexes, if the first non-zero doesn't start at the same index, it means they are not equal in size
		return false; 
	}

	for (int i = 0; i <= firstNonZero; i++) {
		if (bits[i] != n.bits[i]) {
			return false;
		}
	}

	//note: even if sizes of bits arrays are different, we don't account for leading zeros so a comparison could still return true
	return true;
}

/*
operator!=
Preconditions:	input Binary is a valid,initialized Binary object type
Postconditions: returns false if this Binary instance and input Binary have equal sign, size, and
				same sequence of Binary representation.
				returns true otherwise.
*/
bool Binary::operator!=(const Binary& n) {
	return !(*this == n);
}

/*
output operator<<
Preconditions: input Binary is a valid Binary object type
Postconditions: the console outputs the Binary sequence representing the current Binary instance;
				if the Binary number is negative, a dash ("-") precedes the Binary sequence.
*/
ostream& operator<<(ostream& output, const Binary& n) {
	if (n.sign) {
		output << "-";
	}

	//finds where the first non-zero entry is so we don't print leading zeros
	int firstNonZero = -1;
	for (int i = n.size - 1; i >= 0; i--) {
		if (n.bits[i]) {
			firstNonZero = i;
			break;
		}
	}

	//if array doesn't have any non-zero entries, print one zero
	if (firstNonZero == -1) {
		output << "0";
	}

	//otherwise, print starting from the first non-zero entry
	for (int i = firstNonZero; i >=0 ; i--) {
		if (!n.bits[i]) {
			output << "0";
		}
		else {
			firstNonZero = true;
			output << "1";
		}
	}
	return output;
}

//accessor methods
/*
getBit
Preconditions: input int is valid, not out of bounds of the bits array (int >=0 && int < size)
Postconditions: a value representing the bit value at the specified index location is returned.
				if the bit is 1, getBit returns true;
				if the bit is 0, getBit returns false;
				if the input is out of bounds of the bits array, getBit returns false
*/
bool Binary::getBit(int n) {
	if (n < 0 || n >= size){
		return false;
	}
	return bits[n];
}

//mutator methods
/*
input operator>>
Preconditions: input Binary is a valid Binary object type
Postconditions: input console stores the value of the input integer from user's keyboard as a Binary instance
*/
istream& operator>>(istream& input, Binary& n) {
	int temp;
	input >> temp; //takes in user input as a decimal integer value
	Binary tmp(temp); //constructs new Binary integer instance from user input
	n = tmp; //assign n to tmp using assingment operator

	return input;
}

/*
setBit
Preconditions:	input int is valid, not out of bounds of the bits array (int >=0 && int < size)
Postconditions: sets bit value at specified index to true (1)
				if input int is out of bounds, input n is ignored
*/
void Binary::setBit(int n) {
	if (n >= 0 && n < size) {
		bits[n] = true;
	}
}

/*firstNonZeroHelper
Preconditions: a Binary instance exists with instantiated size and sign values
Postconditions: if after changing the bit values of certain entries and the Binary happens to become zero, change the sign to positive
				so the output stream doesn't print a negative zero value
				This method acts as a safe guard against unintentionally printing -0.
*/
void Binary::firstNonZeroHelper() {
	int firstNonZero = -1;
	for (int i = size - 1; i >= 0; i--) {
		if (bits[i]) {
			firstNonZero = i;
			break;
		}
	}

	if (firstNonZero == -1) {
		sign = false; //set sign to positive if after clearing the bit, the remainder number is just 0
					  //we don't want to print a negative zero so this step is necessary
	}
}
/*
clearBit
Preconditions:	input int is valid, not out of bounds of the bits array (int >=0 && int < size)
Postconditions:	sets bit value at specified index to false (0)
				if input int is out of bounds, input n is ignored
*/
void Binary::clearBit(int n) {
	if (n >= 0 && n < size) {
		bits[n] = false;

		firstNonZeroHelper();
	}
}

/*
toggleBit
Preconditions:	input int is valid, not out of bounds of the bits array (int >=0 && int < size)
Postconditions: switches bit value at specified index to true (1) if it was previously false (0) and vice versa
				if input int is out of bounds, input n is ignored
*/
void Binary::toggleBit(int n) {
	if (n >= 0 && n < size) {
		bits[n] = !bits[n];

		firstNonZeroHelper();
	}
}
/*bool *bits;
  bool positive;
  int numBits; size*/
bool Binary::operator<(const Binary& input)const {
	if (sign && !input.sign) { return true; }
	if (!sign && input.sign) { return false; }

	if (size < input.size) { return true; }
	if (size > input.size) { return false; }

	//2 are equal sizes now
	bool equal = true;

	for (int i = 0; i < size; i++) {
		if (bits[i] != input.bits[i]) {
			equal = false;
		}
	}
	if (equal) { return false; } //if both are exactly the same, return false because this Binary isn't smaller than input Binary

	for (int i = 0; i < size - 1; i++) {

		//an = bn and an+1…a1 > bn+1…b1
		bool c2 = bits[i] == input.bits[i]; //check if bits[i] and input.bits[i] are same value
		bool c3 = bits[i + 1] && !input.bits[i + 1];//check if bits[i+1] is true and b[i+1] is false; 
		if (c2 && c3) {
			//if enter, it means this Binary > input Binary, so we return false
			return false;
		}
	}
	return true;
}