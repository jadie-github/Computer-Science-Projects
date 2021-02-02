/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a Buy class to handle Buy requests by the client to the Shop class.
It will perform a Buy action to the item being passed in.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Buy.h"
#include "Shop.h"
using namespace std;

/* process: carries out input request by client
Preconditions: command string is nonempty
Postconditions:  action is performed on the Items depending on the type of request the client inputs
*/
void Buy::process(string command) {
	stringstream s_stream(command); //create string stream from the string

	string ID = "", type = "", description = "";

	s_stream.get();
	s_stream.get();

	getline(s_stream, ID, ',');			  //get first string delimited by comma
	int id = atoi(ID.c_str());			  //convert string id to int id

	s_stream.get(); 					  //discard space 

	getline(s_stream, type, ',');		  //get type

	s_stream.get(); 					  //discard space 
	getline(s_stream, description, '\n'); //get rest of item description

	if (id < 0 || id > 999) {
		cout << "Invalid ID " << id << endl;
		return;
	}

	if (Shop::hash(type) == -1) {
		getline(s_stream, description, '\n'); //discard rest of line
		cout << "Invalid item type " << type << endl;
	}
	else {
		Item* i = ItemFactory::createItem(type);

		i = i->create(description);//create based on description

		if (i == nullptr) {
			cout << "Item is null, unavailable to buy" << endl;
			return;
		}

		s->buy(id, type, i);

	}
}