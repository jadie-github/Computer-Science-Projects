/*Jessica Nguyen
CSS 343, Program 4 Design
This driver class manages operations at a collectibles store, such as read in the inventory list, customer list,
and generate commands within a Shop to manage the inventories inside the shop.
*/

#include <iostream>
#include <fstream>
#include "Shop.h"
using namespace std;

int main() {

	//create a Shop item
	Shop s;

	//reads in inventory file
	ifstream infile1("hw4inventory.txt");
	if (!infile1) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

	//generates inventory from input file
	s.ReadInventory(infile1);

	//reads in customer file
	ifstream infile2("hw4customers.txt");
	if (!infile2) {
		cerr << "file could not be opened." << endl;
		return 1;
	}

	//generates customer from input file
	s.ReadCustomer(infile2);
	
	//reads command from input file
	ifstream infile3("hw4commands.txt");
	if (!infile3) {
		cerr << "File could not be opened." << endl;
		return 1;
	}

	//generates commands from input file
	s.ReadCommand(infile3);

	return 0;
}