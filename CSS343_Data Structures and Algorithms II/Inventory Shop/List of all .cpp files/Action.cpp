/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents an Action class that encapsulates action requests by the client to the Shop class.
It will perform actions depending on the type of request the client demands.
*/

#include "Action.h"

/* constructor
Postconditions: initialize an empty Shop object
*/
Action::Action() {
	s = nullptr;
}

/* copy constructor
Preconditions: input Shop is initialized
Postconditions: input shop is copied to the Action class's Shop instance
*/
Action::Action(Shop* s) {
	this->s = s;
}

/*setShop: set the Shop's instance to input shop
Preconditions: input Shop is initialized
Postconditions: Action class's Shop instance is set to the input shop
*/
void Action:: setShop(Shop* s) {
	this->s = s;
}

/* process: carries out input request by client
Preconditions: command string is nonempty
Postconditions:  action is performed on the Items depending on the type of request the client inputs
*/
void Action::process(string command){}
