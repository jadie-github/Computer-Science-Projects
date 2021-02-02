/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents an ItemFactory class that produces Items depending on the type of request the client demands.
*/
#pragma once
#include <iostream>
using namespace std;

#include "Coin.h"
#include "Comic.h"
#include "SportsCard.h"

class ItemFactory {
public:
	/*createItem
	Preconditions: input string type is initialized
	Postconditions: returns Coin, Comic or SportsCard depending on input type
					returns nullptr if input type is invalid
	*/
	static Item* createItem(const string type) {
		
		if (type == "M") {
			return new Coin;
		}
		if (type == "C") {
			return new Comic;
		}
		if (type == "S") {
			return new SportsCard;
		}

		return nullptr;
	}
};