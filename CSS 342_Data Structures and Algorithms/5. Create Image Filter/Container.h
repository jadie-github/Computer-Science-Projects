/* Jessica Nguyen
CSS 342, Project 4
This file describes the interface to the Container class. 
Functionality includes: 
default constructor, constructor with input PixelInfo struct;
copy constructor, assignment operator, destructor;
accessor methods: size, seed, average color;
mutator methods: add, remove, merge;
*/

#include <iostream>
using namespace std;

// a struct that encapsulates info about a pixel in a node
struct PixelInfo {	
	int red;
	int green;
	int blue;
	int row;
	int col;
};

class Container {
public:
	
	/* Container()
	Postconditions: creates a new Container object with its head, last, next node set to null; 
					PixelInfo struct values are all set to 0. */
	Container();

	/* Container()
	Preconditions:	input PixelInfo is a valid, intialized PixelInfo object type
	Postconditions: creates a new Container object with its head node containing the input PixelInfo struct. */
	Container(PixelInfo& input);
	
	/* Container()
	Preconditions:	input Container is a valid, initialized Container object type
	Postconditions: a deep copy of the image Container will be copied into a newly constructed Container object, 
					including the linked list with all associated pixels. */
	Container(const Container&);

	/*~Container()
	Postconditions: all contents of current Container object are deleted in memory */
	~Container();

	/*assignment operator=
	Preconditions:	input Container is a valid,initialized Container object type
	Postconditions: the calling Container object is assigned to the current Container object 
					and both objects share the same memory address to the Container object.	*/
	const Container& operator=(const Container&);

	/*isEmpty()
	Preconditions:	current Container object must exist and is not null
	Postconditions:	Returns true if there are PixelInfo objects inside the current Container, false otherwise. */
	bool isEmpty() const;

	// getter methods
	/*getSize()
	Preconditions:	current Container object must exist and is not null
	Postconditions:	Returns an int count of total number of PixelInfo objects in the current Container */
	int getSize() const;

	/*getSeed()
	Preconditions:	current Container object must exist and is not null
	Postconditions: a reference to the seed pixel in the Container is returned.
					If there is no seed pixel in the Container, returns empty PixelInfo object (0,0,0,0,0) */
	PixelInfo& getSeed() const;

	/*getAverageColor()
	Preconditions:	current Container object must exist and is not null
	Postconditions:	returns a PixelInfo containing the average RGB color of all PixelInfo objects in the Container. */
	PixelInfo& getAverageColor() const;
	
	//modifier methods

	/*addPixel
	Preconditions:	input PixelInfo is a valid struct that has been initialized
	Postconditions: input PixelInfo is added to the Container. */
	bool add(PixelInfo&);

	/*remove() Retrieves a PixelInfo object from the Container.
	Preconditions:	input PixelInfo is a valid, intialized PixelInfo object type.
	Postconditions: If the Container is not empty, input PixelInfo
					will contain the pixel that was removed and the PixelInfo is removed from Container
					Returns false if the Container is empty, true otherwise. */
	bool remove(PixelInfo&);

	/*merge
	Preconditions:	input Container object must exist and is not null
	Postconditions: returns a reference to the current Container object that merges PixelInfo objects
					from the input Container together into a bigger Container.
					The input Container input object is unchanged.  */
	Container& merge(const Container&);

private:

	/*	The Container is implemented as a linked list
		with one external pointer to the front of the Container
		and a second external pointer to the back of the Container. */

	struct Node { 				// a node on a LinkedList in a Container object
		PixelInfo pixelInfo;
		Node* next;       		// pointer to next node in Container
	};

	int size;
	Node* head; 				// pointer to first seed node in a linked List of nodes
	Node* last;					// pointer to last seed node in a linked List of nodes
};
