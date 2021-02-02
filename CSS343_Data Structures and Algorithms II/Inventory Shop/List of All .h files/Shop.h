/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a Shop which stores information about its inventory and customers.
Clients will be able to read in text files which orders the Shop to do multiple things: generate inventory, generate customers,
or perform commands between Customers and Inventories like buy/sell/display/customer/history.
*/

#pragma once
#include "CustomerList.h"
#include "SearchTree.h"
#include "ActionFactory.h"
#include "ItemFactory.h"


class Shop {
private:
	CustomerList customers;				//hash table that stores Customers

	static const int tableSize = 26;	//number of types of items (max is 26 for expansion)

	SearchTree* inventory[tableSize];	//array of binary search trees for Items

	enum itemType { M, C, S };			//enums for 3 types of items, add more if there are more items in future

	/*hashCommand: hashes a string command to its obejct type
	Preconditions: type is initialized
	Postconditions: an int representing the command
					return -1 if the command isn't one of the specified types
	*/
	const int hashCommand(const string type) const; //determines which command to do through hashing

public:	
	/*constructor
	Postconditions: Shop object is initialized, inventory is initilized with an array of SearchTree objects
	*/
	Shop();

	/*	copy constructor
	Preconditions: input Shop is initialized 
	Postconditions: a deep copy of the input Shop instance will be copied into a newly constructed Shop object
	*/
	Shop(const Shop& s);

	/* ReadInventory: reads in infile and instantiate Items as the order they're read in from the infile
	Preconditions: ifstream file exists in folder
	Postconditions: items in inventory file will be instantiated with appropriate amounts and descriptions;
					If the character defining the item type is anything other than M,C,S, it will be ignored,
					the item won't be added to SearchTree, and an error message will be displayed.
	*/
	void ReadInventory(ifstream& infile);
	

	/*ReadCustomer
	Preconditions: ifstream file exists in folder
	Postconditions: Customer objects will be instantiated and hashed with the appropriate ID number
					If the ID number is anything other than 3-digit int, it will be ignored, won't be added to CustomerList
	*/
	void ReadCustomer(ifstream& infile);	

	/*ReadCommand
	Preconditions: ifstream file exists in folder
	Postconditions: commands from ifstream is carried out to modify item amounts/display customer history appropriately
					If the character isn't one of the five (S,B,D,C,H), command is ignored, error message is displayed
	*/
	void ReadCommand(ifstream& infile);
	
	/*hash function: hash input type into the correct Item in the Hash table
	Preconditions: type is valid type of Item
	Postconditions: if type is M, return 0
					if type is C, return 1
					if type is S, return 2
					else, return -1
	*/
	static const int hash(const string type);

	/*sell: removes an item to inventory, associate that item with a specified customer 
	Preconditions: ID is between 0 and 1000, type and Item input are initilized
	Postconditions: Item's count decrements by 1 in inventory, customer with ID is associated with the transaction
	*/
	void sell(const int ID, const string type, Item* input);

	/*buy: adds an item to inventory, associate that item with a specified customer
	Preconditions: ID is between 0 and 999, type and Item input are initilized
	Postconditions: Item's count increments by 1 in inventory, customer with ID is associated with the transaction
	*/
	void buy(const int ID, const string type, Item* input);

	/*display: 
	Preconditions: calling Shop object is initialized
	Postconditions: outputs the entire inventory of the store, including the number of each item in inventory
	*/
	void display() const;

	/*customer:
	Preconditions: ID is between 0 and 999, calling Shop object is initialized
	Postconditions: outputs all of the transactions for a customer (in chronological order), including the item
				   outputs error message if int ID is invalid
	*/
	void customer(const int ID)const;

	/*history: 
	Preconditions: calling Shop object is initialized
	Postconditions: outputs the history for every customer, with the customers in alphabetical order.
	*/
	void history() const;

	/*destructor
	Preconditions: calling object is initialized
	Postconditions: Shop object is deleted in memory
	*/
	~Shop();
};