/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents an ActionFactory class that produces Actions depending on the type of request the client demands.
*/

#pragma once
#include <iostream>
using namespace std;

#include "Sell.h"
#include "Buy.h"
#include "Display.h"
#include "DisplayCustomer.h"
#include "History.h"

class ActionFactory {
public:
	/*createAction
	Preconditions: input string type is initialized
	Postconditions: returns Sell, Buy, Display, DisplayCustomer, or History depending on input type
					returns nullptr if input type is invalid
	*/
    static Action* createAction(const string type) {
        if (type == "S") {
			return new Sell;
		}
		if (type == "B") {
			return new Buy;
		}
		if (type == "D") {
			return new Display;
		}
		if (type == "C") {
			return new DisplayCustomer;
		}
		if (type == "H") {
			return new History;
		}

		return nullptr;
    }
};