/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a Customer List which stores information about customers the Shop has.
Clients will be able to add/retrieve a Customer from the List, add transaction history (sell/buy) to a Customer, 
and display one or all Customers' transation history.
*/

#pragma once
#include <iostream>

#include "Customer.h"

using namespace std;

class CustomerList {
private:
	static const int customerListSize = 10;	//10 slots for Customer objects
	
	struct CustomerNode {
		int ID;
		Customer* customer;
		CustomerNode* next;
	};

	CustomerNode* CustomerHashTable[customerListSize];	//hash table (with linkedlists) stores ID and Customer
		
	vector< pair <string, int> > nameList;				//string vector to sort customers by name, int ID as key value

	/*hash function: hash Customer object to an index in the customerList hash table
	Preconditions: ID is valid positive 3-digit integer
	Postconditions: returns the index at which the input customer will be hashed to its appropriate position in the customerList hash table
	*/
	const int hash(const int ID) const;

public:
	/*constructor
	Preconditions: initialize an CustomerList object
	Postconditions: CustomerList object is instantiated in memory
					root is nullptr
	*/
	CustomerList();

	/* add: adds a Customer into the CustomerList
	Preconditions: ID is a three-digit positive integer
				   Customer is initialized 
	Postconditions: int ID is hashed to the Customer input in the CustomerList
					Customer name is added to the nameList to sort alphabetically 
					returns false if ID is not a three-digit positive integer
					returns false if the Customer is already in CustomerList (it will not be inserted), or if Customer is nullptr
	*/
	bool add(const int ID, Customer* customer); //calls the hash function

	/* sell: associate the sale item to the Customer's history transaction
	Preconditions: ID is a three-digit positive integer
				   ID is hashed to valid Customer, type is valid, Item is initlialized
	Postconditions: return true if the item is successfully added to the Customer's transaction history for bookkeeping
					returns false if ID is not a three-digit positive integer, type doesn't belong to any Item type, item doesn't exist, or item is nullptr
	*/
	bool sell(const int ID, const Item* item);

	/*buy: add input item to the Customer's history transaction
	Preconditions: ID is a three-digit positive integer; 
				   ID is hashed to valid Customer, type is valid, Item is initlialized
	Postconditions: return true if the item is successfully added to the Customer's transaction history for bookkeeping
					returns false if ID is not a three-digit positive integer, type doesn't belong to any Item type, item doesn't exist, or item is nullptr
	*/
	bool buy(const int ID, const Item* item);

	/*retrieve: returns a Customer that has the ID number
	Preconditions: ID is valid positive 3-digit integer, customer is initilized
	Postconditions: returns Customer whose ID matches with the input int ID
					return nullptr if not found
	*/
	Customer* retrieve(const int ID) const;

	/*display: displays input customer's past transaction history with the item in each transaction
	Preconditions: ID is a three-digit positive integer
	Postconditions: outputs all of the transactions for the Customer whose ID matches with input ID, including the item
					prints error message if ID is invalid
	*/
	void display(const int ID) const;

	/* display: displays all Customers' transaction history with the item in each transaction 
	Preconditions: Calling CustomerList object is initialized
	Postconditions: outputs the history for every customer, with the customers in alphabetical order.
	*/
	void display() const;
	
	/* destructor: deletes CustomerList
	Preconditions: calling CustomerList is initilized
	Postconditions: calling CustomerList is deleted in memory , root is nullptr
	*/
	~CustomerList();
};