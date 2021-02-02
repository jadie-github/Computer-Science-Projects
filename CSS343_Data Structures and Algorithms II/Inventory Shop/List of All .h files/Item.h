/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a base class for Items available in the Shop. 
Clients will be able to construct an item,
compare 2 Items (==,!=,<,>), and print the item's atrributes.
*/

#pragma once
#include <string>
using namespace std;

class Item {
public:
	virtual int adorbs() = 0;
	/*constructor
	Postconditions: instantiate an Item object
	*/
	Item();

	/*create: factory method that determines type of Item to be initialized at runtime
	Preconditions: type is valid
	Postconditions: appropriate Item that is hashed from the input type with be returned
	*/
	virtual Item* create(string description);

	/*
	assignment operator=
	Preconditions: input Item is initialized
	Postconditions: the calling Item data is assigned to the current Item
	*/
	virtual const Item& operator=(const Item&);

	/*
	operator==
	Preconditions: input Item is a valid, initialized Item object type
	Postconditions: returns true if input Item has all the same attributes to this Item
					returns false otherwise
	*/
	virtual bool operator==(const Item&) const;

	/*
	operator!=
	Preconditions: input Item is a valid, initialized Item object type
	Postconditions: returns false if input Item does not have all the same attributes to this Item
					returns true otherwise
	*/
	virtual bool operator!=(const Item&) const;

	/*
	operator<
	Preconditions: input Item is a valid, initialized Item object type
	Postconditions: returns true if input Item "ranked more" to this Item in the list
					returns false otherwise
	*/
	virtual bool operator<(const Item&) const;

	/*
	operator>
	Preconditions: input Item is a valid, initialized Item object type
	Postconditions: returns true if input "ranked less" to this Item in the list
					returns false otherwise
	*/
	virtual bool operator>(const Item&) const;

	/*getType: returns type of item
	Preconditions: calling Item is initialized
	Postconditions: if type is Coin, returns M
					if type is Comic, returns C
					if type if SportsCard, returns S
	*/
	virtual const string getType() const;

	/*print: helps print Item's attributes
	Preconditions: initialized Item object 
	Postconditions: outputs Item's atrributes depending on the type inputted
	*/
	virtual void print(ostream& output, const Item& input) const;

	/*
	operator<<
	Preconditions: input Item is a valid, initialized Item object type
	Postconditions: the console outputs the atrributes of the input Item
	*/
	friend ostream& operator<<(ostream& output, const Item& input);

};