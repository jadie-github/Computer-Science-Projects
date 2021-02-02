/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a Customer List which stores information about customers the Shop has.
Clients will be able to add/retrieve a Customer from the List, add transaction history (sell/buy) to a Customer,
and display one or all Customers' transation history.
*/

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "CustomerList.h"

using namespace std;

/*hash function: hash Customer object to an index in the customerList hash table
Preconditions: ID is valid positive 3-digit integer
Postconditions: returns the index at which the input customer will be hashed to its appropriate position in the customerList hash table
*/
const int CustomerList::hash(const int ID) const {
	if (ID < 0 || ID > 1000) {
		cout << "Invalid ID " << ID << endl;
		return -1;
	}

	return ID / 100; //returns the first digit
}

/*constructor
Preconditions: initialize an CustomerList object
Postconditions: CustomerList object is instantiated in memory
				root is nullptr
*/
CustomerList::CustomerList() {
	
	for (int i = 0; i < customerListSize; i++) {
		CustomerHashTable[i] = nullptr;
	}

}

/* add: adds a Customer into the CustomerList
Preconditions: ID is a three-digit positive integer
			   Customer is initialized
Postconditions: int ID is hashed to the Customer input in the CustomerList
				Customer name is added to the nameList to sort alphabetically
				returns false if ID is not a three-digit positive integer
				returns false if the Customer is already in CustomerList (it will not be inserted), or if Customer is nullptr
*/
bool  CustomerList::add(const int ID, Customer* customer) {
	if (ID < 0 || ID > 1000) { //safety check
		cout << "Invalid ID " << ID << endl;
		return false;
	}

	int index = hash(ID);
	
	nameList.push_back(make_pair(customer->getName(), ID)); //add name and ID to nameList to sort names alphabetically
	
	if (CustomerHashTable[index] == nullptr) { //insert head

		CustomerHashTable[index] = new CustomerNode;
		CustomerHashTable[index]->customer = new Customer;

		CustomerHashTable[index]->ID = ID;		
		*(CustomerHashTable[index]->customer) = *customer;

		CustomerHashTable[index]->next = nullptr;

	}
	else { //insert to back of linked list if collision in buckets
		CustomerNode* cur = CustomerHashTable[index];

		while (cur != nullptr && cur->next != nullptr) {
			cur = cur->next;
		}

		cur->next = new CustomerNode; //initialize new Node

		cur = cur->next;
		cur->ID = ID;
		*(cur->customer) = *customer;
		cur->next = nullptr;

	}

	return true;
}

/* sell: associate the sale item to the Customer's history transaction
Preconditions: ID is a three-digit positive integer
			   ID is hashed to valid Customer, type is valid, Item is initlialized
Postconditions: return true if the item is successfully added to the Customer's transaction history for bookkeeping
				returns false if ID is not a three-digit positive integer, type doesn't belong to any Item type, item doesn't exist, or item is nullptr
*/
bool  CustomerList::sell(const int ID, const Item* item) {
	if (ID < 0 || ID > 1000) { //safety check
		cout << "Invalid ID " << ID << endl;
		return false;
	}

	Customer* c = retrieve(ID);

	if (c == nullptr) {
		cout << "Cannot find customer with ID " << ID << endl;
		return false;
	}

	c->addToHistory("S", item);

	return true;
}


/*buy: add input item to the Customer's history transaction
Preconditions: ID is a three-digit positive integer;
			   ID is hashed to valid Customer, type is valid, Item is initlialized
Postconditions: return true if the item is successfully added to the Customer's transaction history for bookkeeping
				returns false if ID is not a three-digit positive integer, type doesn't belong to any Item type, item doesn't exist, or item is nullptr
*/
bool  CustomerList::buy(const int ID, const Item* item) {
	if (ID < 0 || ID > 1000) { //safety check
		cout << "Invalid ID " << ID << endl;
		return false;
	}

	Customer* c = retrieve(ID);

	if (c == nullptr) {
		return false; //not found customer with the given ID
	}
	c->addToHistory("B", item);

	return true;
}

/*retrieve: returns a Customer that has the ID number
Preconditions: ID is valid positive 3-digit integer, customer is initilized
Postconditions: returns Customer whose ID matches with the input int ID
				return nullptr if not found
*/
Customer* CustomerList::retrieve(const int ID) const {
	if (ID < 0 || ID > 1000) { //safety check
		cout << "Invalid ID " << ID << endl;
		return nullptr; 
	}

	int index = hash(ID);

	CustomerNode* cur = CustomerHashTable[index]; // Initialize cur

	while (cur != nullptr)
	{
		if (cur->ID == ID) {
			return cur->customer;
		}
		cur = cur->next;
	}

	return nullptr; //not found
}

/*display: displays input customer's past transaction history with the item in each transaction
Preconditions: ID is a three-digit positive integer
Postconditions: outputs all of the transactions for the Customer whose ID matches with input ID, including the item
				prints error message if ID is invalid
*/
void  CustomerList::display(const int ID) const {
	if (ID < 0 || ID > 1000) { //safety check
		cout << "Invalid ID " << ID << endl;
		return;
	}

	Customer* c = retrieve(ID);

	if (c == nullptr) {
		cout << "Customer with ID ";

		if (ID >= 0 && ID <= 9) { //if ID is single digit, add "00"
			cout << "00";
		}
		else if (ID >= 10 && ID <= 99) {//if ID is double digit, add "0"
			cout << "0";
		}
		cout << ID << " Not Found" << endl;

		return; //not found customer with the given ID
	}

	cout << c->getName() << ", ";

	if (ID >= 0 && ID <= 9) { //if ID is single digit, add "00"
		cout << "00";
	}
	else if (ID >= 10 && ID <= 99) {//if ID is double digit, add "0"
		cout << "0";
	}

	cout << ID << endl; // displays name and ID of customer

	c->printHistory();

}

/* display: displays all Customers' transaction history with the item in each transaction
Preconditions: Calling CustomerList object is initialized
Postconditions: outputs the history for every customer, with the customers in alphabetical order.
*/
void CustomerList::display() const {

	vector< pair <string, int> > temp = nameList; // sets temp value to sort 

	sort(temp.begin(), temp.end()); //sort nameList by alphabetical order 

	for (int i = 0; i < temp.size(); i++) {
		display(temp.at(i).second); //calls display method for each customer in namelist
	}
}

/* destructor: deletes CustomerList
Preconditions: calling CustomerList is initilized
Postconditions: calling CustomerList is deleted in memory 
*/
CustomerList::~CustomerList() {
	for (int i = 0; i < customerListSize; i++) {//for every CustomerNode in CustomerHashTable

		while (CustomerHashTable[i] != nullptr) {
			CustomerNode* toDelete = CustomerHashTable[i];	  //temp value to delete later

			CustomerHashTable[i] = CustomerHashTable[i]->next;//moves pointer up
			
			toDelete->ID = 0;
			delete toDelete->customer;   // deletes Customer
			toDelete->next = nullptr;	 //sets null
			
			delete toDelete;

			toDelete = nullptr; 
		}

	}
}