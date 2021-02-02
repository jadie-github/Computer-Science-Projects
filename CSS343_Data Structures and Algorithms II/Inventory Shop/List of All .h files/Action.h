/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents an Action class that encapsulates action requests by the client to the Shop class.
It will perform actions depending on the type of request the client demands.
*/
#pragma once
#include "CustomerList.h"
#include "SearchTree.h"
class Shop;

class Action {
protected:
	Shop *s; //pointer to the calling Shop class
public:
	/* constructor
	Postconditions: initialize an empty Shop object
	*/
	Action();

	/* copy constructor
	Preconditions: input Shop is initialized
	Postconditions: input shop is copied to the Action class's Shop instance
	*/
	Action(Shop* s);

	/*setShop: set the Shop's instance to input shop
	Preconditions: input Shop is initialized
	Postconditions: Action class's Shop instance is set to the input shop
	*/
	virtual void setShop(Shop* s);

	/* process: carries out input request by client
	Preconditions: command string is nonempty
	Postconditions:  action is performed on the Items depending on the type of request the client inputs
	*/
	virtual void process(const string command);
	
};

