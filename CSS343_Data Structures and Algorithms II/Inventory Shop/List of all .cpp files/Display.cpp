/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents a Display class to handle Buy requests by the client to the Shop class.
It will perform a Display action to the item being passed in.
*/
#include "Display.h"
#include "Shop.h"
using namespace std;

/* process: carries out input request by client
Preconditions: command string is nonempty
Postconditions:  action is performed on the Items depending on the type of request the client inputs
*/
void Display:: process(string command) {
	s->display();
}