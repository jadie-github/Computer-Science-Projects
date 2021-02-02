/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a Customer object.
Clients will be able to construct a Customer from name, add items to the transaction history, and print the transaction history by chronological order.
*/

#pragma once
#include <iostream>
#include <vector> 

#include "Customer.h"
using namespace std;

/* constructor
Postconditions: Customer object is created with empty name, history is empty
*/
Customer::Customer() {
	name = "";
}

/*constructor
Postconditions: Customer object is created with input string as name, history is empty
*/
Customer::Customer(string name) {
	this->name = name;
}

/*
assignment operator=
Preconditions: input Customer is initialized
Postconditions: the calling Customer data is assigned to the current Customer
*/
const Customer& Customer::operator=(const Customer& input) {
	if (this != &input) {// check for self assignment
		//deallocate left side
		destructorHelper();

		//assign right side to left side
		this->name = input.name;
		for (int i = 0; i < input.history.size(); i++) { //copy elements from input Customer to this history
			history.push_back(input.history[i]);
		}
	}
	return *this;
}

/*getName
Postconditions: returns name of calling Customer object
*/
const string Customer::getName() const {
	return this->name;
}

/*addToHistory: add Item into callinng Customer's transaction history for bookkeeping
Preconditions: type is valid and item is initialized
Postconditions: return true if Item and its type is successfully added to the Customer's transaction history
				return false if type is invalid, or item is nullptr
*/
bool Customer::addToHistory(const string transactionType, const Item* item) {
	if (item == nullptr) { return false; }
	history.push_back(make_pair(transactionType, item));
	return true;
}

/*printHistory: prints transaction history of a Customer
Preconditions: calling Customer object is initialized
Postconditions: outputs all of the transactions for the Customer whose ID matches with input ID, including the item
*/
void Customer::printHistory() {
	for (int i = 0; i < history.size(); i++) { //for every transaction in customer's history
		
		cout << "	" << history.at(i).first << ", " << (*history.at(i).second).getType() << ", " << *history.at(i).second << endl; 
					   //prints transaction type		  prints Item type						     prints Item attributes
	}
}

/*destructorHelper
Postcondition: Customer instance is deleted from memory
*/
void Customer::destructorHelper() {
	name = "";
	for (int i = 0; i < this->history.size(); i++) { //clear current history vector
		history[i].first = "";
		history[i].second = nullptr;
	}
}


/*destructor
Postcondition: Customer instance is deleted from memory
*/
Customer::~Customer() {
	destructorHelper();
}