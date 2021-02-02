/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a History class to handle Buy requests by the client to the Shop class.
It will perform a History action to the item being passed in.
*/
#pragma once
#include "Action.h"

class History :	public Action {
public:
	/* process: carries out input request by client
	Preconditions: command string is nonempty
	Postconditions:  action is performed on the Items depending on the type of request the client inputs
	*/
	void process(const string command) override;
};

