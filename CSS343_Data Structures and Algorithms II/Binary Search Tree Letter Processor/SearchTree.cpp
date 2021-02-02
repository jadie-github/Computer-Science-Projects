/*Jessica Nguyen
CSS 343, Project 2
This class represents a SearchTree object. The SearchTree is made up of Nodes that contain a Comparable item,
its frequency, and each Node has 2 children on the left and right. Users will be able to construct a SearchTree instance either by default,
or by copying in another SearchTree instance, or by assigning another SearchTree instance to the memory location of this SearchTree instace.
Users can also perform operators like comparing SearchTree's to see if they are equal (==), unequal(!=), and output the frequency table of
the SearchTree in inorder traversal.
Mutator functions include insert, remove, or makeEmpty a SearchTree.
Accessor functions include retrieval and calculate height of a root Node.
*/


#include <iostream>
#include "SearchTree.h"
using namespace std;

/*
default constructor
Postconditions: the root Node is initialized to nullptr
*/
SearchTree::SearchTree() {
	root = nullptr;
}

/*
private helper: copyHelper
Preconditions: input Nodes are initialized Node structs
Postconditions: a deep copy of the input Node instance will be copied into a newly constructed Node object
*/
void SearchTree::copyHelper(Node*& copy, const Node* original) {
	if (original == nullptr) {
		copy = nullptr;
	}
	else { //initialize new Node if not null
		copy = new Node;
		copy->item = original->item;
		*copy->item = *original->item;
		copy->frequency = original->frequency;

		copyHelper(copy->left, original->left);
		copyHelper(copy->right, original->right);
	}
}

/*
copy constructor
Preconditions: input SearchTree is an initialized SearchTree object
Postconditions: a deep copy of the input SearchTree instance will be copied into a newly constructed SearchTree object
*/
SearchTree::SearchTree(const SearchTree& input) {
	copyHelper(this->root, input.root);
}

/*
private helper: destructorHelper
Preconditions: input Node is an initialized Node struct
Postconditions: all contents of current Node object are deleted in memory, root Node is set to nullptr
*/
void SearchTree::destructorHelper(Node*& root) {
	if (root != nullptr) { //only if root isn't a nullptr
		root->item = nullptr;
		root->frequency = 0;

		destructorHelper(root->left);
		destructorHelper(root->right);

		delete root->item;
		delete root;
		root = nullptr;
	}
}

/*
destructor
Preconditions: this SearchTree instance is an initialized SearchTree object
Postconditions: all contents of current SearchTree object are deleted in memory, root Node is set to nullptr
*/
SearchTree:: ~SearchTree() {
	destructorHelper(this->root);
}

/*
assignment operator
Preconditions: input SearchTree is an initialized SearchTree object
Postconditions: the calling SearchTree object is assigned to the current SearchTree object with a deep copy
				and both objects share the same memory address
*/
const SearchTree& SearchTree:: operator=(const SearchTree& input) {
	if (this != &input) { //safeguard for self assignment
		delete root;
		copyHelper(this->root, input.root); //copy over the data from input SearchTree to this instance using copy constructor
	}
	return *this;
}


/*
private helper: isEqualHelper
Preconditions: input Nodes are initialized Node structs
Postconditions: returns true if two input Node matches frequency and character, OR if both Nodes are nullptr
				returns false otherwise
*/
bool SearchTree::isEqualHelper(const Node* current, const Node* input) const {
	if (current == nullptr && input == nullptr) {
		return true;
	}
	if ((current == nullptr && input != nullptr) || (current != nullptr && input == nullptr)) {
		return false;
	}

	if ((*current->item != *input->item) || (current->frequency != input->frequency)) {
		return false;
	}

	return isEqualHelper(current->left, input->left) && isEqualHelper(current->right, input->right);
}

/*
operator==
Preconditions: input SearchTree is an initialized SearchTree object
Postconditions: returns true if input SearchTree has all Nodes that matches this SearchTree's Nodes (in frequency and character)
				returns false otherwise
*/
bool SearchTree:: operator==(const SearchTree& input) const {
	return isEqualHelper(this->root, input.root);
}

/*
operator!=
Preconditions: input SearchTree is an initialized SearchTree object
Postconditions: returns false if input SearchTree has all Nodes that matches this SearchTree's Nodes (in frequency and character)
				returns true otherwise
*/
bool SearchTree:: operator!=(const SearchTree& input) const {
	return !isEqualHelper(this->root, input.root);
}

/*
private helper: outputHelper
Preconditions: input Node is an initialized Node struct
Postconditions: the ostream ouputs a frequency chart in sorted ASCII order of characters.
				Every character is outputted with its frequency in input textfile.
*/
ostream& outputHelper(ostream& output, const SearchTree::Node* input) {
	if (input == nullptr) {
		return output;
	}
	outputHelper(output, input->left);

	output << *input->item << " " << input->frequency << endl;

	outputHelper(output, input->right);
}

/*
operator<<
Preconditions: input SearchTree is an initialized SearchTree object
Postconditions: the ostream ouputs a frequency chart in sorted ASCII order of characters.
				Every character is outputted with its frequency it appared in input textfile.
*/
ostream& operator<<(ostream& output, const SearchTree& input) {
	return outputHelper(output, input.root);
}

/*
private helper: insertHelper
Preconditions: input Comparable and Node aren initialized instances
Postconditions: inserts a Comparable into the tree or increments the count if it is already in the tree.
				returns false if the Comparable is found (not inserted)
*/
bool SearchTree::insertHelper(Comparable* input, SearchTree::Node*& root) {
	if (root == nullptr) {
		root = new Node;
		root->item = input;
		root->frequency = 1;
		root->left = nullptr;
		root->right = nullptr;
		return true;
	}

	//if item already exists in tree, increment the count but don't add new Node
	if (*root->item == *input) {
		root->frequency++;

		return false;
	}

	//if item isn't found, recurse left to insert if item value is smaller than root
	if (*input < *root->item) {
		return insertHelper(input, root->left);
	}
	else {
		return insertHelper(input, root->right);
	}
}

/*
insert
Preconditions: input Comparable is an initialized Comparable object
Postconditions: inserts a Comparable into the tree or increments the count if it is already in the tree.
				returns false if the Comparable is already in SearchTree (it will not be inserted), or if Comparable is nullptr
*/
bool SearchTree::insert(Comparable* input) {
	if (input == nullptr) {
		return false;
	}
	return insertHelper(input, this->root);
}

/*
private helper: findAndDeleteReplacement
Preconditions: input Node is an initialized Node struct
Postconditions: returns the Comparable value of the replacement Node in the SearchTree class
				Replacement Node's old memory is then deleted as it replaces current root
*/
SearchTree::Node* SearchTree::findReplacement(SearchTree::Node*& root)
{
	Node* cur = root;
	while (cur != nullptr && cur->left != nullptr) {
		cur = cur->left;
	}
	return cur;
}

/*
private helper: deleteRoot
Given a binary search tree and a key, this function deletes the key
and returns the new root
Preconditions: input Node is an initialized Node struct
Postconditions: input Node is deleted in memory and is replaced by another Node in SearchTree class, determined by findAndDeleteReplacement().
*/
SearchTree::Node* SearchTree::deleteRoot(SearchTree::Node*& root) {

	if (root->left == nullptr) { //if root has 1 child node
		Node* temp = root->right;

		free(root);

		return temp;
	}
	else if (root->right == nullptr) { //root.left != nullptr
		Node* temp = root->left;

		free(root);

		return temp;
	}
	//if root node has 2 children, have to find the appropriate replacement
	Node* parentOfSuccessor = root;

	//Find successor
	Node* successor = root->right;
	while (successor->left != nullptr) {
		parentOfSuccessor = successor;
		successor = successor->left;
	}

	//Delete successsor (most left of right subtree)	
	if (parentOfSuccessor != root) {
		parentOfSuccessor->left = successor->right;
	}
	else {
		parentOfSuccessor->right = successor->right;
	}

	//Copy successor data to root
	root->item = successor->item;
	root->frequency = successor->frequency;

	//delete successor and deturn root
	delete successor;
	return root;
}

/*
private helper: removeHelper
Preconditions: input Comparable and Node are initialized instances
Postconditions: removes one occurrence of input Comparable from the tree.
			   If it is the last occurrence, remove the Node that stores the Comparable.
			   Returns false if the Comparable is not found.
*/
bool SearchTree::removeHelper(const Comparable& input, SearchTree::Node*& root) {
	if (root == nullptr) { //if target not found
		return false;
	}

	if (*root->item == input) { //if target equals to input value
		//normal case: decrease frequency by one
		if (root->frequency > 1) {
			root->frequency--;
		}
		else { //special case: if frequency is 0, completely remove the node
			root = deleteRoot(root);
		}
		return true;
	}

	if (*root->item > input) { //if not found, recurse left if Comparable is smaller than root's Comparable
		return removeHelper(input, root->left);
	}
	else {
		return removeHelper(input, root->right);
	}

}

/*
remove
Preconditions: input Comparable is an initialized Comparable object
Postconditions: removes one occurrence of input Comparable from the tree.
				If it is the last occurrence, remove the Node that stores the Comparable.
				Returns false if the Comparable is not found.
*/
bool SearchTree::remove(const Comparable& input) {
	return removeHelper(input, this->root);
}

/*
makeEmpty
Preconditions: this SearchTree instance is an initialized SearchTree object
Postconditions: removes and deallocates all of the data from the tree.
*/
void SearchTree::makeEmpty() {
	destructorHelper(this->root);
	this->root = nullptr;
}

/*
private helper: retrieveHelper
Preconditions: input Comparable and Node are initialized instances
Postconditions: returns a Comparable in the tree that has the same character value as input Comparable
				returns nullptr if not found
*/
const Comparable* SearchTree::retrieveHelper(const Comparable& input, const SearchTree::Node* root) const {
	if (root == nullptr || root->item == nullptr) {
		return nullptr;
	}

	if (*root->item == input) {
		return root->item;
	}
	if (*root->item > input) {
		return retrieveHelper(input, root->left);
	}
	else {
		return retrieveHelper(input, root->right);
	}
}

/*
retrieve
Preconditions: input Comparable instance is an initialized Comparable object
Postconditions: returns a Comparable in the tree that has the same character value as input Comparable
				returns nullptr if not found
*/
const Comparable* SearchTree::retrieve(const Comparable& input) const {
	return retrieveHelper(input, this->root);
}

/*
private helper: heightHelper
Preconditions: input Node is an initialized Node struct
Postconditions: returns the height of the node storing the Comparable in the SearchTree class.
				A leaf has height 0.
				Return -1 if the Comparable is not found.
*/
int SearchTree::heightHelper(const SearchTree::Node* root) const {
	if (root == nullptr) {
		return 0;
	}

	//if leaf, height is 0
	if (root->left == nullptr && root->right == nullptr) {
		return 0;
	}

	int leftHeight = heightHelper(root->left);
	int rightHeight = heightHelper(root->right);

	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}
}

/*
private helper: findNode
Preconditions: input Comparable and Node are initialized instances
Postconditions: returns Node in the tree that stores the input Comparable value.
				returns nullptr if not found.
*/
SearchTree::Node* SearchTree::findNode(const Comparable& input, SearchTree::Node* root) const {
	if (root == nullptr || *root->item == input) {
		return root;
	}

	if (*root->item > input) {
		return findNode(input, root->left);
	}

	return findNode(input, root->right);
}

/*
height
Preconditions: input Comparable instance is an initialized Comparable object
Postconditions: returns the int height of the node storing the Comparable in the tree.
				A leaf has height 0.
				Return -1 if the Comparable is not found.
*/
int SearchTree::height(const Comparable& input) const {
	Node* tempRoot = findNode(input, this->root); //finds where the Node we're looking for in the SearchTree first

	if (tempRoot == nullptr) { return -1; } //if not found, return -1

	return heightHelper(tempRoot);
}