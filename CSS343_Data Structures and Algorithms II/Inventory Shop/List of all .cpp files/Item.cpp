/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a base class for Items available in the Shop.
Clients will be able to construct an item,
compare 2 Items (==,!=,<,>), and print the item's atrributes.
*/

#pragma once
#include <iostream>
#include "Item.h"

using namespace std;

Item::Item() {}

/*create: factory method that determines type of Item to be initialized at runtime
Preconditions: type is valid
Postconditions: appropriate Item that is hashed from the input type with be returned
*/
Item* Item::create(string description) { return nullptr; }

/*
assignment operator=
Preconditions: input Item is initialized
Postconditions: the calling Item data is assigned to the current Item
*/
const Item& Item::operator=(const Item& input) { return input; }

/*
operator==
Preconditions: input Item is a valid, initialized Item object type
Postconditions: returns true if input Item has all the same attributes to this Item
				returns false otherwise
*/
bool Item::operator==(const Item& input) const { return false; } 

/*
operator!=
Preconditions: input Item is a valid, initialized Item object type
Postconditions: returns false if input Item does not have all the same attributes to this Item
				returns true otherwise
*/
bool Item::operator!=(const Item&) const { return false; }

/*
operator<
Preconditions: input Item is a valid, initialized Item object type
Postconditions: returns true if input Item "ranked more" to this Item in the list
				returns false otherwise
*/
bool Item:: operator<(const Item& input) const { return false; }

/*
operator>
Preconditions: input Item is a valid, initialized Item object type
Postconditions: returns true if input "ranked less" to this Item in the list
				returns false otherwise
*/
bool Item:: operator>(const Item&) const { return false; }

/*getType: returns type of item
Preconditions: calling Item is initialized
Postconditions: if type is Coin, returns M
				if type is Comic, returns C
				if type if SportsCard, returns S
*/
const string Item::getType() const { return ""; }

/*print: helps print Item's attributes
Preconditions: initialized Item object
Postconditions: outputs Item's atrributes depending on the type inputted
*/
void Item::print(ostream& output, const Item& input) const { }

/*
operator<<
Preconditions: input Item is a valid, initialized Item object type
Postconditions: the console outputs the atrributes of the input Item
*/
ostream& operator<<(ostream& output, const Item& input) { 

	input.print(output, input); //will call the correct subclass's print()

	return output; 
}