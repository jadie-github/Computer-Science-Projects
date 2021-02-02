/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a base class for Coins available in the Shop.
Clients will be able to construct a coin, 
compare 2 Coins (==,!=,<,>), and print the Coin's atrributes.
*/

#pragma once
#include <iostream>
#include "Item.h"
using namespace std;

class Coin : public Item {
private:
	//attributes of a Coin item
	string type;
	int year;
	int grade;
public:
	/*constructor
	Postconditions: instantiate a Coin object
	*/
	Coin();

	/*create: factory method that determines type of Coin to be initialized at runtime
	Preconditions: type is valid
	Postconditions: appropriate Coin that is hashed from the input type with be returned
	*/
	Coin* create(const string description) override;

	/*
	assignment operator=
	Preconditions: input Item is initialized
	Postconditions: the calling Item data is assigned to the current Item
	*/
	const Coin& operator=(const Item&) override;

	/*
	operator==
	Preconditions: input Coin is a valid, initialized Coin object type
	Postconditions: returns true if 2 Coins are the same "rank" in the inventory system
					returns false otherwise
	*/
	bool operator==(const Item& input) const override; 

	/*
	operator!=
	Preconditions: input Coin is a valid, initialized Coin object type
	Postconditions: returns false if if 2 Coins are not the same "rank" in the inventory system
					returns true otherwise
	*/
	bool operator!=(const Item& input) const override;

	/*
	operator<
	Preconditions: input Coin is a valid, initialized Coin object type
	Postconditions: returns true if input Coin is "higher ranked" than this Coin
					returns false otherwise
	*/
	bool operator<(const Item& input) const override;

	/*
	operator>
	Preconditions: input Coin is a valid, initialized Coin object type
	Postconditions: returns true if input Coin is "less ranked" than this Coin
					returns false otherwise
	*/
	bool operator>(const Item& input) const override;

	/*getType: returns type of item
	Preconditions: calling Item is initialized
	Postconditions:	if type is Comic, returns M
	*/
	const string getType() const override;

	/*print: helps print Item's attributes
	Preconditions: initialized Item object
	Postconditions: outputs Item's atrributes depending on the type inputted
	*/
	void print(ostream& output, const Item& input) const override;

	/*
	operator<<
	Preconditions: input Coin is a valid, initialized Coin object type
	Postconditions: the console outputs the Coin's attributes: type, year, and grade 
	*/
	friend ostream& operator<<(ostream& output, const Item& input);

};