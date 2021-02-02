/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a base class for SportsCards available in the Shop.
Clients will be able to construct a SportsCard,
compare 2 SportsCards (==,!=,<,>), and print the SportsCard's atrributes.
*/

#pragma once
#include <iostream>
#include "Item.h"
using namespace std;

class SportsCard : public Item {
private:
	//attributes of a SportsCard item
	string player;
	string manufacturer;
	int year;
	string grade;
public:	
	/*constructor
	Postconditions: instantiate a SportsCard object
	*/
	SportsCard();

	/*create: factory method that determines type of SportsCard to be initialized at runtime
	Preconditions: type is valid
	Postconditions: appropriate SportsCard that is hashed from the input type with be returned
	*/
	SportsCard* create(const string description) override;

	/*
	assignment operator=
	Preconditions: input Item is initialized
	Postconditions: the calling Item data is assigned to the current Item
	*/
	const SportsCard& operator=(const Item&) override;

	/*
	operator==
	Preconditions: input SportsCard is a valid, initialized SportsCard object type
	Postconditions: returns true if 2 SportsCards are the same "rank" in the inventory system
					returns false otherwise
	*/
	bool operator==(const Item& input) const override;

	/*
	operator!=
	Preconditions: input SportsCard is a valid, initialized SportsCard object type
	Postconditions: returns false if if 2 SportsCards are not the same "rank" in the inventory system
					returns true otherwise
	*/
	bool operator!=(const Item& input) const override;

	/*
	operator<
	Preconditions: input SportsCard is a valid, initialized SportsCard object type
	Postconditions: returns true if input SportsCard is "higher ranked" than this SportsCard
					returns false otherwise
	*/
	bool operator<(const Item& input) const override;

	/*
	operator>
	Preconditions: input SportsCard is a valid, initialized SportsCard object type
	Postconditions: returns true if input SportsCard is "less ranked" than this SportsCard
					returns false otherwise
	*/
	bool operator>(const Item& input) const override;

	/*getType: returns type of item
	Preconditions: calling Item is initialized
	Postconditions: returns S
	*/
	const string getType() const override;

	/*print: helps print Item's attributes
	Preconditions: initialized Item object
	Postconditions: outputs Item's atrributes depending on the type inputted
	*/
	void print(ostream& output, const Item& input) const override;

	/*
	operator<<
	Preconditions: input SportsCard is a valid, initialized SportsCard object type
	Postconditions: the console outputs the SportsCard's attributes: type, year, and grade
	*/
	friend ostream& operator<<(ostream& output, const Item& input);
	
};