/*Jessica Nguyen
CSS 343, Program 4 Design
This class represents an Inventory List template for coins, comics, and sports cards Inventory lists.
Clients will be able to retrieve, add, sell, buy an Item from the Shop, and command the Shop to display all the inventory it has.
*/

#pragma once
#include <iostream>
#include "Item.h"

class SearchTree {
protected:
	struct Node { //struct representing an Item Node with pointers to its children
		Item* item;
		int count;
		Node* left;
		Node* right;
	};

	Node* root; //root of the Item BST


	//helpers
	/*	private helper: displayHelper
	Preconditions: input Node is initialized
	Postconditions: outputs all coins, then all comics, then all sports cards 
					by the ordering of their attributes
	*/
	void displayHelper(Node* root) const;

	/*	private helper: retrieveHelper
	Preconditions: input Item and Node are initialized instances
	Postconditions: returns a Item in the tree that has the same as attributes as input Item
					returns nullptr if not found
	*/
	Item* retrieveHelper(const Item& input, Node* root) const;

	/* private helper: addHelper
	Preconditions: input Comparable and Node are initialized instances
	Postconditions: inserts an Item into the tree or increments the count if it is already in the tree.
					returns false if the Item is found (not inserted)
	*/
	bool addHelper(Item* input, Node*& root, const int count);

	/*	private helper: findNode
	Preconditions: input Item and Node are initialized instances
	Postconditions: returns Node in the tree that stores the input Item value.
					returns nullptr if not found.
	*/
	Node* findNode(Item& input, Node* root) const;

	/*	private helper: sellHelper
	Preconditions: input Item and Node aren initialized instances
	Postconditions: removes one occurrence of input Item from the tree.
					If it is the last occurrence, remove the Node that stores the Item.
					Returns false if the Item is not found.
	*/
	bool sellHelper(const Item& input, Node*& root);

	/* 	private helper: deleteRoot
	Preconditions: input Node is an initialized Node struct
	Postconditions: input Node is deleted in memory and is replaced by another Node in SearchTree class, determined by findReplacement().
	*/
	Node* deleteRoot(Node*& root);

	/* private helper: destructorHelper
	Preconditions: input Node is an initialized Node struct
	Postconditions: all contents of current Node object are deleted in memory, root Node is set to nullptr
	*/
	void destructorHelper(Node*& root);

public:
	/*constructor: initialize an SearchTree object
	Postconditions: SearchTree object is instantiated in memory
					root node is nullprtr
	*/
	SearchTree();

	/*retrieve: retrieve an item and returns its pointer from the SearchTree
    Preconditions: input Item instance is initialized
    Postconditions: returns a Item in the SearchTree that has the same attributes 
				    (year, grade, type/title/player, publisher/manufacture) as input Item;
				    returns nullptr if not found
   */
	virtual Item* retrieve(const Item& item) const;

	/* add: adds Item to the SearchTree
	Preconditions: input Item is initialized
    Postconditions: Item is added to SearchTree
                    returns false if the Item is already in SearchTree (it will not be inserted), or if Item is nullptr
    */
	virtual bool add(Item* item, const int count);

	/* sell: remove one occurence of Item from SearchTree
	Preconditions: type is valid and item is initialized
	Postconditions: returns false if Item is nullptr, or Item doesn't exist in SearchTree, error message displayed;
					returns true if Item exists, one occurence of Item is removed from SearchTree;
					returns true if Item is the only one left in SearchTree, then the whole Item will be deleted from SearchTree
	*/
	virtual bool sell(const Item& item); 

	/* buy: increase one occurence of Item from SearchTree (the shop "buys" the Item from Customer)
	Preconditions: type is valid and item is initialized
	Postconditions: If Item isn't in the SearchTree, add it to the SearchTree;
					If Item already existed in the SearchTree, increment the Item count one more;
					returns false if Item is null
	*/
	virtual bool buy(Item* item); 

	/* setItemCount: sets count of input Item to input int count
	Preconditions: input is initialized, count > 0
	Postconditions: Item's count in inventory is set to input count
					return true if count change successful
					return false if count is <=0 or input item is nullptr
	*/
	virtual bool setItemCount(Item& input, int count);

	/*display: prints items in SearchTree by coins, comics, and cards
	Preconditions: calling SearchTree object is initialized
	Postconditions: items in SearchTree are printed in order of coins, comics, and cards 
					and each Item is sorted appropriately by its type;
					Coins are sorted first by type, then by year, then by grade;
					Comics are sorted first by publisher, then by title, then by year, then by grade;
					Sports cards are sorted by player, then by year, then by manufacturer, then by grade;

	*/
	virtual void display() const; 
	
	/* destructor
	Preconditions:calling SearchTree object is initialized
	Postconditions: calling SearchTree object is deleted in memory
	*/
	virtual ~SearchTree();
};