/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a base class for Comics available in the Shop.
Clients will be able to construct a Comic,
compare 2 Comics (==,!=,<,>), and print the Comic's atrributes.
*/

#pragma once
#include <iostream>
#include "Item.h"
using namespace std;

class Comic : public Item {
private:
	//attributes of a Comic item
	string title;
	string publisher;
	int year;
	string grade;
public:
	/*constructor
	Postconditions: instantiate a Comic object
	*/
	Comic();

	/*create: factory method that determines type of Comic to be initialized at runtime
	Preconditions: type is valid
	Postconditions: appropriate Comic that is hashed from the input type with be returned
	*/
	Comic* create(const string description) override;

	/*
	assignment operator=
	Preconditions: input Item is initialized
	Postconditions: the calling Item data is assigned to the current Item
	*/
	const Comic& operator=(const Item&) override;

	/*
	operator==
	Preconditions: input Comic is a valid, initialized Comic object type
	Postconditions: returns true if 2 Comics are the same "rank" in the inventory system
					returns false otherwise
	*/
	bool operator==(const Item& input) const override;

	/*
	operator!=
	Preconditions: input Comic is a valid, initialized Comic object type
	Postconditions: returns false if if 2 Comics are not the same "rank" in the inventory system
					returns true otherwise
	*/
	bool operator!=(const Item& input) const override;

	/*
	operator<
	Preconditions: input Comic is a valid, initialized Comic object type
	Postconditions: returns true if input Comic is "higher ranked" than this Comic
					returns false otherwise
	*/
	bool operator<(const Item& input) const override;

	/*
	operator>
	Preconditions: input Comic is a valid, initialized Comic object type
	Postconditions: returns true if input Comic is "less ranked" than this Comic
					returns false otherwise
	*/
	bool operator>(const Item& input) const override;

	/*getType: returns type of item
	Preconditions: calling Item is initialized
	Postconditions: returns C
	*/
	const string getType() const override;

	/*print: helps print Item's attributes
	Preconditions: initialized Item object
	Postconditions: outputs Item's atrributes depending on the type inputted
	*/
	void print(ostream& output, const Item& input) const override;

	/*
	operator<<
	Preconditions: input Comic is a valid, initialized Comic object type
	Postconditions: the console outputs the Comic's attributes: type, year, and grade
	*/
	friend ostream& operator<<(ostream& output, const Item& input);
	
};