/*Jessica Nguyen
CSS 342, Project 4
This file describes the interface to the Container class.
Functionality includes:
default constructor, constructor with input PixelInfo struct;
copy constructor, assignment operator, destructor;
accessor methods: size, seed, average color;
mutator methods: add, remove, merge;
*/

#include "Container.h"
#include <iostream>
using namespace std;

/*	Container()
	Postconditions: creates a new Container object with its head, last, next node set to null;
					PixelInfo struct values are all set to 0. */
Container::Container() {
	head = nullptr;

	last = head;

	size = 0;
}

/*	Container()
	Preconditions:	input PixelInfo is a valid, intialized PixelInfo object type
	Postconditions: creates a new Container object with its head node containing the input PixelInfo struct. */
Container::Container(PixelInfo& input) {
	head = new Node();
	head->pixelInfo.red = input.red;
	head->pixelInfo.green = input.green;
	head->pixelInfo.blue = input.blue;
	head->pixelInfo.row = input.row;
	head->pixelInfo.col = input.col;

	head->next = nullptr;

	last = head;

	size = 1;
}

/*	Container()
	Preconditions:	input Container is a valid, initialized Container object type
	Postconditions: a deep copy of the image Container will be copied into a newly constructed Container object,
					including the linked list with all associated pixels. */
Container::Container(const Container& input) {
	if (input.head == nullptr) {
		this->head = nullptr;
		this->last = nullptr;
		size = 0;
	}
	else {
		this->size = input.size;

		Node* cur = input.head;
		this->head = new Node();
		
		this->head->pixelInfo.red = cur->pixelInfo.red;
		this->head->pixelInfo.green = cur->pixelInfo.green;
		this->head->pixelInfo.blue = cur->pixelInfo.blue;
		this->head->pixelInfo.row = cur->pixelInfo.row;
		this->head->pixelInfo.col = cur->pixelInfo.col;

		this->head->next = nullptr;
		
		Node* curCopy = this->head;
		this->last = curCopy;

		cur = cur->next;
	
		while (cur != nullptr) {
			
			curCopy->next = new Node();

			curCopy = curCopy->next;
			this->last = curCopy;

			curCopy->pixelInfo.red = cur->pixelInfo.red;
			curCopy->pixelInfo.green = cur->pixelInfo.green;
			curCopy->pixelInfo.blue = cur->pixelInfo.blue;
			curCopy->pixelInfo.row = cur->pixelInfo.row;
			curCopy->pixelInfo.col = cur->pixelInfo.col;

			curCopy->next = nullptr;

			cur = cur->next;
		}
	}
}

/*	~Container()
	Postconditions: all contents of current Container object are deleted in memory. */
Container:: ~Container() {
	while (head != nullptr) {
		Node* tmp = head;
		head = head->next;
		delete tmp;
		tmp = nullptr;
	}
	head = nullptr;
	last = nullptr;
	size = 0;
}

/*	assignment operator=
	Preconditions:	input Container is a valid,initialized Container object type
	Postconditions: the calling Container object is assigned to the current Container object
					and both objects share the same memory address to the Container object.	*/	
const Container& Container:: operator=(const Container& input) {
	if (this != &input) {
		//deallocate left hand side, avoid memory leaks
		while (head != nullptr) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
			tmp = nullptr;
		}
		head = nullptr;
		last = nullptr;
		size = 0;

		//re assign this Container's reference to input Container
		Container temp(input);
		swap(temp.head, head);
		this->size = input.size;
		
	}
	return *this;
	
}

/*	isEmpty()
	Preconditions:	current Container object must exist and is not null
	Postconditions:	Returns true if there are PixelInfo objects inside the current Container, false otherwise. */
bool Container::isEmpty() const {
	return size == 0;
}

// getter methods

/*	getSize()
	Preconditions:	current Container object must exist and is not null
	Postconditions:	Returns an int count of total number of PixelInfo objects in the current Container */
int Container::getSize() const {
	return size;
}

/*	getSeed()
	Preconditions:	current Container object must exist and is not null
	Postconditions: a reference to the seed pixel in the Container is returned.
					If there is no seed pixel in the Container, returns empty PixelInfo object (0,0,0,0,0) */
PixelInfo& Container::getSeed() const {
	return head->pixelInfo;
}

/*	getAverageColor()
	Preconditions:	current Container object must exist and is not null
	Postconditions:	returns a PixelInfo containing the average RGB color of all PixelInfo objects in the Container. */
PixelInfo& Container::getAverageColor() const {
	PixelInfo ans = { 0,0,0,0,0 };
	
	if (head == nullptr) {
		cout << "No pixels in Container.";
		return ans;
	}

	Node* cur = head;
	int count = 0;
	int redSoFar = 0, blueSoFar = 0, greenSoFar = 0;

	while (cur != nullptr) {
		count++;
		redSoFar += cur->pixelInfo.red;
		greenSoFar += cur->pixelInfo.green;
		blueSoFar += cur->pixelInfo.blue;
		cur = cur->next;
	}
	ans.red = redSoFar / count;
	ans.green = greenSoFar / count;
	ans.blue = blueSoFar / count;

	return ans;
}

//modifier methods

/*	add()
	Preconditions:	input PixelInfo is a valid struct that has been initialized
	Postconditions: input PixelInfo is added to the Container. */
bool Container::add(PixelInfo& input) {
	Node* toAdd = new Node();
	toAdd->pixelInfo = input;

	if (isEmpty()) { //if inserting to empty container
		head = toAdd;
	}
	else {
		last->next = toAdd;
	}

	last = toAdd; //new node at back
	size++;

	return true;
}

/*	remove() Retrieves a PixelInfo object from the Container.
	Preconditions:	input PixelInfo is a valid, intialized PixelInfo object type.
	Postconditions: If the Container is not empty, input PixelInfo
					will contain the pixel that was removed (in no particular order) 
					PixelInfo is removed from Container.
					Returns false if the Container is empty, true otherwise. */
bool Container::remove(PixelInfo& input) {
	// remove does not reveal the linked list implementation, 
	// passes back to the user values in no particular order, until Container is empty.
	if (isEmpty()) {
		return false;
	}

	input = head->pixelInfo; //head node is removed and stored in input parameter
	head = head->next;
	size--;

	return true;
}

/*	merge
	Preconditions:	input Container object must exist and is not null
	Postconditions: returns a reference to the current Container object that merges PixelInfo objects
					from the input Container together into a bigger Container.
					The input Container input object is unchanged.  */
Container& Container::merge(const Container& input) {
	//merges input container into current container as deep copy
	if (this-> head == nullptr && input.head == nullptr) { //if both this and the input container are empty
		this->head = nullptr;
		this->last = nullptr;
		size = 0;
		return *this;
	} 
		
	if (this->head == nullptr && input.head != nullptr) { //first merge: if this container is empty but input is not empty
		
		this->size = input.size;

		Node* cur = input.head;
		this->head = new Node();

		this->head->pixelInfo.red = cur->pixelInfo.red;
		this->head->pixelInfo.green = cur->pixelInfo.green;
		this->head->pixelInfo.blue = cur->pixelInfo.blue;
		this->head->pixelInfo.row = cur->pixelInfo.row;
		this->head->pixelInfo.col = cur->pixelInfo.col;

		this->head->next = nullptr;

		Node* curCopy = this->head;
		this->last = curCopy;

		cur = cur->next;

		while (cur != nullptr) {
			curCopy->next = new Node();

			curCopy = curCopy->next;
			this->last = curCopy;

			curCopy->pixelInfo.red = cur->pixelInfo.red;
			curCopy->pixelInfo.green = cur->pixelInfo.green;
			curCopy->pixelInfo.blue = cur->pixelInfo.blue;
			curCopy->pixelInfo.row = cur->pixelInfo.row;
			curCopy->pixelInfo.col = cur->pixelInfo.col;

			curCopy->next = nullptr;

			cur = cur->next;
		}

		return *this;
		
	}
	
	/*all other cases: if both this and input containers have values, take the last node of this container's PixelInfo and copies over the 
	values from the input container */
	this->size += input.size; //updates size of this Container

	Node* cur = input.head;		
	Node* curCopy = this->last; 
		
	while (cur != nullptr) {
		curCopy->next = new Node();

		curCopy = curCopy->next;
		this->last = curCopy;

		curCopy->pixelInfo.red = cur->pixelInfo.red;
		curCopy->pixelInfo.green = cur->pixelInfo.green;
		curCopy->pixelInfo.blue = cur->pixelInfo.blue;
		curCopy->pixelInfo.row = cur->pixelInfo.row;
		curCopy->pixelInfo.col = cur->pixelInfo.col;

		curCopy->next = nullptr;

		cur = cur->next;
	}

	return *this;
}