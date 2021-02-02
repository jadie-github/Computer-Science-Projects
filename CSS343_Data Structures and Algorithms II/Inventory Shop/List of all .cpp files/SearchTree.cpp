/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents an Inventory List template for coins, comics, and sports cards Inventory lists.
Clients will be able to retrieve, add, sell, buy an Item from the Shop, and command the Shop to display all the inventory it has.
*/

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "SearchTree.h"

/*constructor: initialize an SearchTree object
Postconditions: SearchTree object is instantiated in memory
				root node is nullprtr
*/
SearchTree::SearchTree() {
	root = nullptr;
}

/*	private helper: retrieveHelper
Preconditions: input Item and Node are initialized instances
Postconditions: returns a Item in the tree that has the same as attributes as input Item
				returns nullptr if not found
*/
Item* SearchTree::retrieveHelper(const Item& input, Node* root) const {
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

/*retrieve: retrieve an item and returns its pointer from the SearchTree
Preconditions: input Item instance is initialized
Postconditions: returns a Item in the SearchTree that has the same attributes
				(year, grade, type/title/player, publisher/manufacture) as input Item;
				returns nullptr if not found
*/
Item* SearchTree::retrieve(const Item& input) const {
	
	return retrieveHelper(input, root);
}

/* private helper: addHelper
Preconditions: input Comparable and Node are initialized instances
Postconditions: inserts an Item into the tree or increments the count if it is already in the tree.
				returns false if the Item is found (not inserted)
*/
bool SearchTree::addHelper(Item* input, Node*& root, const int count) {
	if (root == nullptr) {
		root = new Node;
		root->item = input; 
		root->count = count;
		root->left = nullptr;
		root->right = nullptr;

		return true;
	}

	//if item already exists in tree, adjust the count but don't add new Node
	if (*root->item == *input) { 
		root->count+= count;

		return false;
	}

	//if item isn't found, recurse left to insert if item value is smaller than root
	if (*input < *root->item) {
		return addHelper(input, root->left, count);
	}
	else { //recurse right otherwise
		return addHelper(input, root->right, count);
	}
}

/* add: adds Item to the SearchTree
Preconditions: input Item is initialized
Postconditions: Item is added to SearchTree
				returns false if the Item is already in SearchTree (it will not be inserted), or if Item is nullptr
*/
bool SearchTree::add(Item* input, const int count) {
	if (count <= 0) {
		cout << "Invalid item count " << count << endl;
		return false;
	}

	if (input == nullptr) {
		return false;
	}
	return addHelper(input, this->root, count);
}

/* 	private helper: deleteRoot
Preconditions: input Node is an initialized Node struct
Postconditions: input Node is deleted in memory and is replaced by another Node in SearchTree class, determined by findReplacement().
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
	*(root->item) =  *(successor->item);
	root->count = successor->count;

	//delete successor and deturn root
	delete successor->item;
	delete successor;
	return root;
	

}

/*	private helper: sellHelper
Preconditions: input Item and Node aren initialized instances
Postconditions: removes one occurrence of input Item from the tree.
				If it is the last occurrence, remove the Node that stores the Item.
				Returns false if the Item is not found.
*/
bool SearchTree::sellHelper(const Item& input, Node*& root) {
	if (root == nullptr || root->item == nullptr) { //if target not found
		cout << "the item doesn't exist" << endl;
		return false;
	}

	if (*root->item == input) { //if target equals to input value
		//normal case: decrease frequency by one
		if (root->count > 1) {
			root->count--;
		}
		else { //special case: if frequency is 0, completely remove the node
			root = deleteRoot(root);
		}
		return true;
	}

	if (*root->item > input) { //if not found, recurse left if Comparable is smaller than root's Comparable
		return sellHelper(input, root->left);
	}
	else {
		return sellHelper(input, root->right);
	}
}

/* sell: remove one occurence of Item from SearchTree
Preconditions: type is valid and item is initialized
Postconditions: returns false if Item is nullptr, or Item doesn't exist in SearchTree, error message displayed;
				returns true if Item exists, one occurence of Item is removed from SearchTree;
				returns true if Item is the only one left in SearchTree, the whole Item will be deleted from SearchTree
*/
bool SearchTree::sell(const Item& input) {
	return sellHelper(input, this->root);
}

/* buy: increase one occurence of Item from SearchTree (the shop "buys" the Item from Customer)
Preconditions: type is valid and item is initialized
Postconditions: If Item isn't in the SearchTree, add it to the SearchTree;
				If Item already existed in the SearchTree, increment the Item count one more;
*/
bool SearchTree::buy(Item* item) {
	return add(item, 1);
}

/*	private helper: displayHelper
Preconditions: input Node is initialized
Postconditions: outputs all coins, then all comics, then all sports cards
				by the ordering of their attributes
*/
void SearchTree::displayHelper(Node* root) const {
	if (root == nullptr) {
		return;
	}
	displayHelper(root->left);

	cout << root->item->getType() << ", " << root->count << ", " << *root->item << endl;

	displayHelper(root->right);
}

/*display: prints items in SearchTree by coins, comics, and cards
Preconditions: calling SearchTree object is initialized
Postconditions: items in SearchTree are printed in order of coins, comics, and cards
				and each Item is sorted appropriately by its type;
				Coins are sorted first by type, then by year, then by grade;
				Comics are sorted first by publisher, then by title, then by year, then by grade;
				Sports cards are sorted by player, then by year, then by manufacturer, then by grade;

*/
void SearchTree::display() const {
	displayHelper(root);
}

/* private helper: findNode
Preconditions: input Item and Node are initialized instances
Postconditions: returns Node in the tree that stores the input Item value.
				returns nullptr if not found.
*/
SearchTree::Node* SearchTree::findNode(Item& input, Node* root) const {
	if (root == nullptr || *root->item == input) {
		return root;
	}

	if (*root->item > input) {
		return findNode(input, root->left);
	}

	return findNode(input, root->right);
}

/* setItemCount: sets count of input Item to input int count
Preconditions: input is initialized, count > 0
Postconditions: Item's count in inventory is set to input count
				return true if count change successful
				return false if count is <=0 or input item is nullptr
*/
bool SearchTree::setItemCount(Item& input, int count) {
	if (count <= 0) {
		cout << "Invalid count " << count << endl;
		return false; 
	}

	Node* item = findNode(input, this->root);

	if (item == nullptr) {
		return false;
	}

	item->count = count;

	return true;
}

/* private helper: destructorHelper
Preconditions: input Node is an initialized Node struct
Postconditions: all contents of current Node object are deleted in memory, root Node is set to nullptr
*/
void SearchTree::destructorHelper(Node*& root) {
	if (root != nullptr) { //only if root isn't a nullptr
		root->item = nullptr;

		destructorHelper(root->left);
		destructorHelper(root->right);

		delete root->item;
		delete root;
		root = nullptr;
	}
}

/* destructor
Preconditions:calling SearchTree object is initialized
Postconditions: calling SearchTree object is deleted in memory
*/
SearchTree::~SearchTree(){
	destructorHelper(this->root);
}