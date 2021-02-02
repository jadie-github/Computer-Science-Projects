#pragma one
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

#include "Comparable.h"
#include <iostream>
using namespace std;


class SearchTree {
private:
    //private struct defining a Node in SearchTree class
    struct Node {
        Comparable* item;  //pointer to the Comparable data
        int frequency;
        Node* left;        //left child
        Node* right;       //right child
    };

    Node* root;

    /*
    private helper: copyHelper
    Preconditions: input Nodes aren initialized Node structs
    Postconditions: a deep copy of the input Node instance will be copied into a newly constructed Node object
    */
    void copyHelper(Node*&, const Node*);

    /*
    private helper: destructorHelper
    Preconditions: input Node is an initialized Node struct
    Postconditions: all contents of current Node object are deleted in memory, root Node is set to nullptr
    */
    void destructorHelper(Node*&);

    /*
    private helper: isEqualHelper
    Preconditions: input Nodes are initialized Node structs
    Postconditions: returns true if two input Node matches frequency and character, OR if both Nodes are nullptr 
					returns false otherwise
    */
    bool isEqualHelper(const Node*, const Node*) const;

    /*
    private helper: outputHelper
    Preconditions: input Node is an initialized Node struct
    Postconditions: the ostream ouputs a frequency chart in sorted ASCII order of characters.
                    Every character is outputted with its frequency in input textfile.
    */
    friend ostream& outputHelper(ostream&, const Node*);

    /*
    private helper: insertHelper
    Preconditions: input Comparable and Node are initialized instances
    Postconditions: inserts a Comparable into the tree or increments the count if it is already in the tree.
                    returns false if the Comparable is found (not inserted)
    */
    bool insertHelper(Comparable*, Node*&);

    /*
    private helper: removeHelper
    Preconditions: input Comparable and Node aren initialized instances
    Postconditions: removes one occurrence of input Comparable from the tree. 
                    If it is the last occurrence, remove the Node that stores the Comparable.
                    Returns false if the Comparable is not found.
    */
    bool removeHelper(const Comparable&, Node*&);

    /*
    private helper: deleteRoot
    Preconditions: input Node is an initialized Node struct
    Postconditions: input Node is deleted in memory and is replaced by another Node in SearchTree class, determined by findAndDeleteReplacement(). 
    */
    Node* deleteRoot(Node*&);

    /*
    private helper: findAndDeleteReplacement
    Preconditions: input Node is an initialized Node struct
    Postconditions: returns the Comparable value of the replacement Node in the SearchTree class
                    Replacement Node's old position is then deleted in memory 
    */
    Node* findReplacement(Node*&);
    
    /*
    private helper: retrieveHelper
    Preconditions: input Comparable and Node are initialized instances
    Postconditions: returns a Comparable in the tree that has the same character value as input Comparable
                    returns nullptr if not found
    */
    const Comparable* retrieveHelper(const Comparable&, const Node*) const;

    /*
    private helper: heightHelper
    Preconditions: input Node is an initialized Node struct
    Postconditions: returns the height of the node storing the Comparable in the tree. 
                    A leaf has height 0. 
                    Return -1 if the Comparable is not found.
    */
    int heightHelper(const Node*) const;

    /*
    private helper: findNode
    Preconditions: input Comparable and Node are initialized instances
    Postconditions: returns Node in the tree that stores the input Comparable value.
                    returns nullptr if not found.
    */
    Node* findNode(const Comparable&, Node*) const;

public:
    SearchTree();

    /*
    copy constructor
    Preconditions: input SearchTree is an initialized SearchTree object
    Postconditions: a deep copy of the input SearchTree instance will be copied into a newly constructed SearchTree object
    */
    SearchTree(const SearchTree&);

    /*
    destructor
    Preconditions: this SearchTree instance is an initialized SearchTree object
    Postconditions: all contents of current SearchTree object are deleted in memory, root Node is set to nullptr
    */
    ~SearchTree();

    /*
    assignment operator
    Preconditions: input SearchTree is an initialized SearchTree object
    Postconditions: the calling SearchTree object is assigned to the current SearchTree object with a deep copy
					and both objects share the same memory address
    */
    const SearchTree& operator=(const SearchTree&);

    /*
    operator==
    Preconditions: input SearchTree is an initialized SearchTree object
    Postconditions: returns true if input SearchTree has all Nodes that matches this SearchTree's Nodes (in frequency and character)
					returns false otherwise
    */
    bool operator==(const SearchTree&) const;

    /*
    operator!=
    Preconditions: input SearchTree is an initialized SearchTree object
    Postconditions: returns false if input SearchTree has all Nodes that matches this SearchTree's Nodes (in frequency and character)
					returns true otherwise
    */
    bool operator!=(const SearchTree&) const;

    /*
    operator<<
    Preconditions: input SearchTree is an initialized SearchTree object
    Postconditions: the ostream ouputs a frequency chart in sorted ASCII order of characters.
                    Every character is outputted with its frequency it appared in input textfile.
    */
    friend ostream& operator<<(ostream&, const SearchTree&);

    /*
    insert
    Preconditions: input Comparable is an initialized Comparable object
    Postconditions: inserts a Comparable into the tree or increments the count if it is already in the tree.
                    returns false if the Comparable is already in SearchTree (it will not be inserted), or if Comparable is nullptr
    */
    bool insert(Comparable*);

    /*
    remove
    Preconditions: input Comparable is an initialized Comparable object
    Postconditions: removes one occurrence of input Comparable from the tree. 
                    If it is the last occurrence, remove the Node that stores the Comparable.
                    Returns false if the Comparable is not found.
    */
    bool remove(const Comparable&);

    /*
    makeEmpty
    Preconditions: this SearchTree instance is an initialized SearchTree object
    Postconditions: removes and deallocates all of the data from the tree.
    */
    void makeEmpty();

    /*
    retrieve
    Preconditions: input Comparable instance is an initialized Comparable object
    Postconditions: returns a Comparable in the tree that has the same character value as input Comparable
                    returns nullptr if not found
    */
    const Comparable* retrieve(const Comparable&) const;

    /*
    height
    Preconditions: input Comparable instance is an initialized Comparable object
    Postconditions: returns the int height of the node storing the Comparable in the tree. 
                    A leaf has height 0. 
                    Return -1 if the Comparable is not found.
    */
    int height(const Comparable&) const;
};