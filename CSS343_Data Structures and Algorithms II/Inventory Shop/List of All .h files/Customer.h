/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a Customer object.
Clients will be able to construct a Customer from name, add items to the transaction history, and print the transaction history by chronological order.
*/

#pragma once
#include <iostream>
#include <vector> 

#include "Item.h"
using namespace std;


class Customer {
private:
	string name; //name of customer
	vector<pair <string, const Item*>> history; //vector containing past sell/buy transaction history of this customer, 
												// pair contains string type and Item
public:
	/* constructor
	Postconditions: Customer object is created with empty name, history is empty 
	*/
	Customer();

	/*constructor
	Postconditions: Customer object is created with input string as name, history is empty 
	*/
	Customer(string name);

	/*
	assignment operator=
	Preconditions: input Customer is initialized
	Postconditions: the calling Customer data is assigned to the current Customer
	*/
	const Customer& operator=(const Customer&);

	/*getName
	Postconditions: returns name of calling Customer object
	*/
	const string getName() const;

	/*addToHistory: add Item into callinng Customer's transaction history for bookkeeping
	Preconditions: type is valid and item is initialized
	Postconditions: return true if Item and its type is successfully added to the Customer's transaction history
					return false if type is invalid, or item is nullptr
	*/
	bool addToHistory(const string transactionType, const Item* item);

	/*printHistory: prints transaction history of a Customer
	Preconditions: calling Customer object is initialized
	Postconditions: outputs all of the transactions for the Customer whose ID matches with input ID, including the item
	*/
	void printHistory();

	/*destructorHelper
	Postcondition: Customer instance is deleted from memory
	*/
	void destructorHelper();

	/*destructor
	Postcondition: Customer instance is deleted from memory
	*/
	~Customer();
};