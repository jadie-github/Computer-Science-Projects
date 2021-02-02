/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a Shop which stores information about its inventory and customers.
Clients will be able to read in text files which orders the Shop to do multiple things: generate inventory, generate customers,
or perform commands between Customers and Inventories.
*/

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Shop.h"

using namespace std;

/*constructor
Postconditions: Shop object is initialized, inventory is initilized with an array of SearchTree objects
*/
Shop::Shop() { 

	for (int i = 0; i < tableSize; i++) {
		inventory[i] = new SearchTree;
	}
}

/*	copy constructor
Preconditions: input Shop is initialized
Postconditions: a deep copy of the input Shop instance will be copied into a newly constructed Shop object
*/
Shop::Shop(const Shop& s) {
	for (int i = 0; i < s.tableSize; i++) {
		inventory[i] = s.inventory[i];
	}
}

/* ReadInventory: reads in infile and instantiate Items as the order they're read in from the infile
Preconditions: ifstream file exists in folder
Postconditions: items in inventory file will be instantiated with appropriate amounts and descriptions;
				If the character defining the item type is anything other than M,C,S, it will be ignored,
				the item won't be added to SearchTree, and an error message will be displayed.
*/
void Shop::ReadInventory(ifstream& infile) {
	for (;;) {
		if (infile.eof()) { //if reached end, stop parsing
			break;
		}

		string type = "", stringCount = "", description = ""; //initialize values

		getline(infile, type, ',');				//get type of inventory

		infile.get(); 							//discard space 

		getline(infile, stringCount, ',');		//get count

		int Count = atoi(stringCount.c_str());	//turn string to int

		infile.get(); 							//discard space

		getline(infile, description, '\n'); 	//get rest of info

		int index = hash(type);					//hash item to its enum type

		Item* i = ItemFactory::createItem(type); //create item based on type
		
		if(i != nullptr){

			i = i->create(description);
			
			inventory[index]->add(i, Count); //adds Item to the correct BST depending on the type, as determined by hash function, wont add if count <= 0
	
		}
		else {
			cout << "Invalid type entry " << type << endl;
		}

	}
}

/*ReadCustomer
Preconditions: ifstream file exists in folder
Postconditions: Customer objects will be instantiated and hashed with the appropriate ID number
				If the ID number is anything other than 3-digit int, it will be ignored, won't be added to CustomerList
*/
void Shop::ReadCustomer(ifstream& infile) {
	for (;;) {
		if (infile.eof()) {//if reached end, stop parsing
			break;
		}

		string ID = "", name = ""; //initialize values

		getline(infile, ID, ',');		//get ID

		int id = atoi(ID.c_str());		//turn string to int

		infile.get(); 					//discard space 

		getline(infile, name, '\n'); 	//get name

		if (id >=0 && id <= 999) { //only add if the ID is valid

			Customer* c = new Customer(name);//construct a Customer object by passing in name

			customers.add(id, c);			//add Customer to customerList

			delete c;
		}
		else {
			cout << "Invalid ID " << ID << endl;
		}
	}

}

/*ReadCommand
Preconditions: ifstream file exists in folder
Postconditions: commands from ifstream is carried out to modify item amounts/display customer history appropriately
				If the character isn't one of the five (S,B,D,C,H), command is ignored, error message is displayed
*/
void Shop::ReadCommand(ifstream& infile) {
	for (;;) {
		if (infile.eof()) {//if reached end, stop parsing
			break;
		}
		string commandType = "", command ="";		//initialize values

		commandType = infile.get(); 	//get commandType

		if (hashCommand(commandType) == -1) {
			getline(infile, command, '\n'); //discard rest of line
			cout << "Invalid command type " << commandType << endl;
		}
		else {

			getline(infile, command, '\n');

			Action* a = ActionFactory::createAction(commandType); //create the correct Action class
			a->setShop(this);
			
			a->process(command);

		}
	}
}

/*sell: removes an item to inventory, associate that item with a specified customer
Preconditions: ID is between 0 and 1000, type and Item input are initilized
Postconditions: Item's count decrements by 1 in inventory, customer with ID is associated with the transaction
*/
void Shop::sell(const int ID, const string type, Item* input) {
	Item* i = inventory[hash(type)]->retrieve(*input); //retrieve input item from the appropriate SearchTree

	if (i == nullptr) { //if can't find that item in the iventory, display error message (can't sell it)
		cout << "Item not in inventory: unavailable for sale" << endl;
	}
	else {
		inventory[hash(type)]->sell(*input);
		customers.sell(ID, input);
	}
}

/*buy: adds an item to inventory, associate that item with a specified customer
Preconditions: ID is between 0 and 999, type and Item input are initilized
Postconditions: Item's count increments by 1 in inventory, customer with ID is associated with the transaction
*/
void Shop::buy(const int ID, const string type, Item* input) {
	inventory[hash(type)]->buy(input);
	customers.buy(ID, input);
}

/*display:
Preconditions: calling Shop object is initialized
Postconditions: outputs the entire inventory of the store, including the number of each item in inventory
*/
void Shop::display() const {
	for (SearchTree *s : inventory) {
		if (s != nullptr) {
			s->display();
		}
	}
}

/*customer:
Preconditions: ID is between 0 and 999, calling Shop object is initialized
Postconditions: outputs all of the transactions for a customer (in chronological order), including the item
			   outputs error message if int ID is invalid
*/
void Shop::customer(const int ID) const {
	customers.display(ID);
}

/*history:
Preconditions: calling Shop object is initialized
Postconditions: outputs the history for every customer, with the customers in alphabetical order.
*/
void Shop::history() const {
	customers.display();
}

/*hashCommand: hashes a string command to its obejct type
Preconditions: type is initialized
Postconditions: an int representing the command
				return -1 if the command isn't one of the specified types
*/
const int Shop::hashCommand(const string type) const {
	if (type == "S") {
		return 0;
	}
	if (type == "B") {
		return 1;
	}
	if (type == "D") {
		return 2;
	}
	if (type == "C") {
		return 3;
	}
	if (type == "H") {
		return 4;
	}

	return -1; //invalid entry
}


/*hash function: hash input type into the correct Item in the Hash table
	Preconditions: type is valid type of Item
	Postconditions: if type is M, return Coin
					if type is C, return Comic
					if type is S, return SportsCard
					else, return nullptr
*/
const int Shop::hash(const string type) {
	if (type == "M") {
		return M;
	}
	if (type == "C") {
		return C;
	}
	if (type == "S") {
		return S;
	}

	return -1; //invalid entry
}


/*destructor
Preconditions: calling object is initialized
Postconditions: Shop object is deleted in memory
*/
Shop::~Shop() {
	for (int i = 0; i < tableSize; i++) {
		delete inventory[i];
	}
}