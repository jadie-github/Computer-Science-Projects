/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a DisplayCustomer class to handle Buy requests by the client to the Shop class.
It will perform a DisplayCustomer action to the item being passed in.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include "DisplayCustomer.h"
#include "Shop.h"
using namespace std;

/* process: carries out input request by client
Preconditions: command string is nonempty
Postconditions:  action is performed on the Items depending on the type of request the client inputs
*/
void DisplayCustomer::process(string command) {
	stringstream s_stream(command); //create string stream from the string

	string ID = "";

	s_stream.get(); 
	s_stream.get();

	getline(s_stream, ID, ',');		//get ID

	int id = atoi(ID.c_str());		//turn string to int

	if (id < 0 || id > 999) {
		cout << "Invalid ID " << id << endl;
		return;
	}

	s->customer(id);
}