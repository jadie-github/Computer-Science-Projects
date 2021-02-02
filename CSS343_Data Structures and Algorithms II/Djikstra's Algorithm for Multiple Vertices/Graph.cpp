/*Jessica Nguyen
CSS 343, Project 3
This class represents a Graph object containing <=100 vertices with weighted and directed edges,
and computes the shortest weighted distance between vertices using Djikstra's Algorithm.
Functions users can use include:
construct Graph, copy Graph, assign Graph to another Graph;
build Graph from an input text file; insert an edge between vertices;
remove an edge between vertices; find the shortest weighted paths between vertices;
display all results to the output console;
or display the shortest weighted path between 2 chosen vertices.
*/

#include <string>
#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;

/* default constructor
Postconditions: new Graph instance is instantiated
				vertices array stores adjacency list with each edgehead being nullptr; Graph will have no more than 100 vertices.
				Table T stores all visited values as false, dist = INT_MAX, path = 0
				size is 0
*/
Graph::Graph() {

	size = 0;

	for (int i = 0; i < MAX_VERTICES; i++) { //initialize adjacency list to all nullptr
		vertices[i].edgeHead = nullptr; 
		vertices[i].data = nullptr;
	}

	for (int i = 0; i < MAX_VERTICES; i++) { //initilize Table T to false visited, 0 dist, 0 path
		for (int j = 0; j < MAX_VERTICES; j++) {
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0; 
		}
	}
}

/* private helper: copyHelper
Preconditions: Graph object is initialized
Postconditions: a deep copy of the Graph input will be copied to the calling object's Graph instance
*/
void Graph::copyHelper(const Graph& input) {

	this->size = input.size; //copy size
	
	//copy vertices
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (input.vertices[i].data == nullptr) {
			this->vertices[i].data = nullptr;
		}
		else {
			vertices[i].data = new Vertex;
			*vertices[i].data = *input.vertices[i].data; //copying data value if not null
		}

		if (input.vertices[i].edgeHead == nullptr) {
			this->vertices[i].edgeHead = nullptr;
		}
		else { //copy edgeHead linkedlist 

			EdgeNode* cur = input.vertices[i].edgeHead; //set the head node
			this->vertices[i].edgeHead = new EdgeNode;
			this->vertices[i].edgeHead->adjVertex = cur->adjVertex;
			this->vertices[i].edgeHead->weight = cur->weight;
			this->vertices[i].edgeHead->nextEdge = nullptr;

			EdgeNode* thisCur = this->vertices[i].edgeHead;

			cur = cur->nextEdge;

			while (cur != nullptr) { //copy the rest of linkedlist
				thisCur->nextEdge = new EdgeNode;
				thisCur = thisCur->nextEdge;
				thisCur->adjVertex = cur->adjVertex;
				thisCur->weight = cur->weight;
				thisCur->nextEdge = nullptr;

				cur = cur->nextEdge;
			}
		}

	}

	//copy T
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			T[i][j].visited = input.T[i][j].visited;
			T[i][j].dist = input.T[i][j].dist;
			T[i][j].path = input.T[i][j].path;
		}

	}
}

/* copy constructor
Preconditions:Preconditions: Graph object is initialized
Postconditions: a deep copy of the Graph input will be copied to the calling object's Graph instance
*/
Graph::Graph(const Graph& input) {

	copyHelper(input);
}

/*private helper: destructor helper
Preconditions: Graph object is initialized
Postconditions: all contents of current Graph object are deleted in memory, vertices and Table array are deleted, size is set to 0
*/
void Graph::destructorHelper() {
	size = 0;

	for (int i = 0; i < MAX_VERTICES; i++) {
		
		while (vertices[i].edgeHead != nullptr) { //delete each linked list inside vertices adjacency list
			EdgeNode* toDelete = vertices[i].edgeHead;
			vertices[i].edgeHead = vertices[i].edgeHead->nextEdge;//move edgehead forward

			toDelete->nextEdge = nullptr; //sets null

			delete toDelete->nextEdge; 
			delete toDelete;			  //delete EdgeNodes one by one until reached end
			toDelete = nullptr;
		}

		if (vertices[i].data != nullptr) {
			delete vertices[i].data;	//delete data portion
			vertices[i].data = nullptr; //set Vertex data to nullptr
		}		
	}

	for (int i = 0; i < MAX_VERTICES; i++) { //set Table T to visited = false, dist = INT_MAX, path = 0
		for (int j = 0; j < MAX_VERTICES; j++) {
			T[i][j].visited = false;
			T[i][j].dist = 0;
			T[i][j].path = 0;
		}
	}
}

/* destructor
Preconditions: Graph input is initialized
Postconditions: all contents of current Graph object are deleted in memory, vertices and Table array are deleted, size is set to 0
*/
Graph::~Graph() {
	destructorHelper();
}

/* operator=
Preconditions: Graph input is initialized
Postconditions:the calling Graph object is assigned to the current Graph object with a deep copy
			   and both objects share the same memory address
*/
const Graph& Graph::operator=(const Graph& input) {
	if (this != &input) { //check for self-assignment
		
		destructorHelper();//deallocate any previous data stored in left hand side

		copyHelper(input); //copy over right hand input after deallocation
	}

	return *this;
}

//-------------------------------- buildGraph ---------------------------------
// Builds a graph by reading data from an ifstream
// Preconditions:  infile has been successfully opened and the file contains
//                 properly formated data (according to the program specs)
// Postconditions: One graph is read from infile and stored in the object
void Graph::buildGraph(ifstream& infile) {

	infile >> size;						// data member stores array size
	if (infile.eof())
		return;
	infile.ignore();					// throw away '\n' to go to next line

	// get descriptions; of vertices
	for (int v = 1; v <= size; v++) {
		vertices[v].data = new Vertex;
		
		infile >> *vertices[v].data; //read in location from input to assign to data portion of Vertex
	}

	// fill cost edge array
	int src = 1, dest = 1, weight = 1;
	for (;;) {
		infile >> src >> dest >> weight; //read in source vertex, destination vertex, and weight between them

		if (src == 0 || infile.eof())
			break;

		insertEdge(src, dest, weight);

	}
}

/*private helper: insertHelper
Preconditions: root and toInsert are initialized EdgeNodes
Postconditions: insert toInsert into the adjacency list rooted at root
				if toInsert's adjVertex already existed inside the adjacency list, the weight of that adjVertex will be replaced by the new toInsert's weight
*/
void Graph::insertHelper(EdgeNode*& root, EdgeNode* toInsert) {
	if (root == nullptr) { //insert to head
		root = toInsert;
	}
	else { //insert to end
		EdgeNode* cur = root;

		while (cur != nullptr && cur->nextEdge != nullptr) {
			cur = cur->nextEdge;
		} //now cur points to last node

		cur->nextEdge = toInsert;
	}
}

/* insertEdge
Preconditions: src > 0 && src <= size, dest > 0 && dest <= size, weight > 0
Postconditions: insert new vertex into the adjacency list with the source src, destination dest, and weight
				if destination vertex already existed inside the adjacency list rooted at src, the weight of destination vertex will be replaced by the new weight
*/
void Graph::insertEdge(const int src, const int dest, const int weight) {
	if (src <= 0 || src > size || dest <= 0 || dest > size || weight < 0) { return; } //check for out of bounds input

	EdgeNode* toInsert = new EdgeNode;
	toInsert->adjVertex = dest;
	toInsert->weight = weight;
	toInsert->nextEdge = nullptr;

	if (vertices[src].edgeHead == nullptr) {
		vertices[src].edgeHead = toInsert; //insert to head
	}
	else { //insert to back
		EdgeNode* cur = vertices[src].edgeHead; 
		bool found = false; //used to identify when to insert new edges instead of replacing old edges

		//insert head
		if (cur != nullptr && cur->adjVertex == dest) {
			cur->weight = weight;
		}
		else {
			while (cur != nullptr && cur->nextEdge != nullptr) {
				if (cur->nextEdge->adjVertex == dest) { //replace weight if dest vertex is already existed
					cur->nextEdge->weight = weight;
					found = true;
					break;
				}
				cur = cur->nextEdge;
			}

			if (!found) { //only insert vertex if it hadn't existed before in the adjacency list
				cur->nextEdge = toInsert;
			}

		}
	}

}

/*removeEdge: removes the edge between source vertex and adjacent vertex
Preconditions: source > 0 && source <= size, adjacent > 0
Postconditions: returns true if removal was successful
				returns false if invalid input, or cannot find destination vertex
*/
bool Graph::removeEdge(const int source, const int adjacent) {
	if (source <= 0 || source > size || adjacent <= 0) { return false; } //check for out of bounds input

	EdgeNode* cur = vertices[source].edgeHead;

	if (cur == nullptr) { //if head node is null
		return false;
	}

	EdgeNode* toDelete;

	//remove head
	if (cur->adjVertex == adjacent) {
		toDelete = vertices[source].edgeHead; //placeholder
		vertices[source].edgeHead = vertices[source].edgeHead->nextEdge;
		
		delete toDelete; //delete the input vertex
		toDelete = nullptr;

		return true;
	} 

	//remove node after head
	while (cur != nullptr && cur->nextEdge!=nullptr) {
		if (cur->nextEdge->adjVertex == adjacent) {
			toDelete = cur->nextEdge; //placeholder
			cur->nextEdge = cur->nextEdge->nextEdge;

			delete toDelete; //delete the input vertex
			toDelete = nullptr;

			return true;
		}
		cur = cur->nextEdge;
	}
		
	return false;
}

/*private helper: findNextVertex
Preconditions: source > 0 && source <=size
Postconditions: finds the next adjacent vertex with minimum weight to the calling vertex objext
				returns -1 if not found
*/
int Graph::findNextVertex(int source) {
	int min = INT_MAX;
	int ans = -1;

	//find the next vertex which is unvisited and adjacent to source vertex
	for (int v = 1; v <= size; v++) {
		if (!T[source][v].visited && T[source][v].dist <= min) {
			min = T[source][v].dist;
			ans = v;
		}
	}

	return ans;
}

/*private helper: isThereEdge
Preconditions: source > 0 && source <= size, dest > 0
Postconditions: returns true if there exists an edge between the source and dest vertices
				returns false if not found
*/
bool Graph::isThereEdge(int source, int dest) {
	EdgeNode* cur = vertices[source].edgeHead;
	while (cur != nullptr) {
		if (cur->adjVertex == dest) {
			return true;
		}
		cur = cur->nextEdge;
	}
	return false;
}

/*private helper: getWeight
Preconditions: source > 0 && source <= size, dest > 0
Postconditions: returns weight between source and dest vertices
				returns -1 if not found an edge between 2 vertices
*/
int Graph::getWeight(int source, int dest) {
	EdgeNode* cur = vertices[source].edgeHead;

	while (cur != nullptr) {
		if (cur->adjVertex == dest) {
			return cur->weight;
		}
		cur = cur->nextEdge;
	}

	return -1;
}

/*private helper: djikstra
Preconditions: source > 0 && source <= size
Postconditions: performs djikstra's shortest weighted path algorithm from given source vertex;
				updates visited vertices, shortest distance, and path values in Table T 
*/
void Graph::djikstra(int source) {
	T[source][source].dist = 0; //set distance from source vertex to itself to 0

	for (int count = 1; count <= size; count++) {
		int u = findNextVertex(source);  //let u be the unvisited vertex with minimum distance Du

		T[source][u].visited = true; //mark vertex u as visited

		for (int w = 1; w <= size; w++) { //for each wertex w adjacent to u

			//if w is not wisited and Dw > Dw + dw,w
			if (!T[source][w].visited && isThereEdge(u, w) && T[source][u].dist != INT_MAX &&
				(T[source][u].dist + getWeight(u, w) < T[source][w].dist)) {

				T[source][w].dist = T[source][u].dist + getWeight(u, w); //set Dw = Dv + du,w

				T[source][w].path = u; // remember that the best path to w goes through u
			}
		}
	}
}

/* private helper: resetTable: for every time insert or removal was performed, need to reset the table to redo the findShortestPath algorithm
Postconditions: Table T of calling Graph instance will be reset: all visited will be false, all dist will be INT_MAX, all path will be 0
*/
void Graph::resetTable() {
	for (int i = 0; i < MAX_VERTICES; i++) { //initilize Table T to false visited, 0 dist, 0 path
		for (int j = 0; j < MAX_VERTICES; j++) {
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
		}
	}
}

/*findShortestPath
Preconditions: calling Graph object is instantiated
Postconditions: performs Djikstra's algorithm to find the shortest weighted path from all source vertices to other vertices in Graph
*/
void Graph::findShortestPath() {
	for (int source = 1; source <= size; source++) { //repeat for every source in graph
		djikstra(source);
	}
}

/* private helper: findPath
Preconditions: from > 0 && from <= size, to > 0 && to <= size
Postconditions: displays the path taken to go from source vertex to ending vertex with the shortest path
*/
void Graph::findPath(const int from, const int to) const { //recursion
	if (from <= 0 || from > size || to <= 0 || to > size) { return; } //check for out of bounds input 

	if (from == to) {
		cout << to << " ";
		return;
	}

	findPath(from, T[from][to].path);
	cout << to << " "; //
}

/*displayAll
Preconditions: calling Graph object is instantiated
Postconditions: displays location name, source vertex, destination vertex, shortest weighted path between the source and destination,
				and the path taken from source to get to destination vertex;
				if there are no path, displays "--"
*/
void Graph::displayAll() {
	resetTable();
	findShortestPath(); //calculate shortest path again in case graph has changed

	cout << "Description                  From  To    Dist  Path" << endl;
	for (int i = 1; i <= size; i++) {

		cout << *vertices[i].data << endl;

		for (int j = 1; j <= size; j++) {
			
			if (i != j) { //don't print distant to itself

				cout << "                             " << i << "     " << j << "     ";

				if (T[i][j].dist == INT_MAX) { //if no path found, display --
					cout << "--";
				}
				else {
					cout << T[i][j].dist << "    ";
					if (T[i][j].dist < 10) { //extra indentation for single-digit numbers
						cout << " ";
					}

					findPath(i, j); //displays path recursively
				}

				cout << endl;
			}
		}
		
	}

}

/*private helper: displayLocation
Preconditions: from > 0 && from <= size, to > 0 && to <= size
Postconditions: displays the path's location names to go from source vertex to ending vertex
*/
void Graph::displayLocation(const int from, const int to) const {
	if (from <= 0 || from > size || to <= 0 || to > size) { return; } //check for out of bounds input 

	if (from == to) {
		cout << *vertices[to].data << endl;
		return;
	}

	displayLocation(from, T[from][to].path);
	cout << *vertices[to].data << endl; //
}

/* display
Preconditions: from > 0 && from <= size, to > 0 && to <= size
Postconditions: displays the source vertex, destination vertex, the shortest weighted edge between them, and path taken to get from source to destination
				displays location name from source to get to destination
*/
void Graph::display(const int from, const int to) {
	if (from <= 0 || from > size || to <= 0 || to > size) { return; }

	resetTable();		//if there were any changes to the adjacency list (insert, removal), need to reset the table to redo findShortestPath.
	findShortestPath(); //calculate shortest path again in case graph has changed

	cout << from << "     " << to << "     ";
	if (T[from][to].dist == INT_MAX) { //if no path exists
		cout << "--" << endl;
	}
	else {
		cout << T[from][to].dist << "    ";

		if (T[from][to].dist < 10) { //extra indentation for single-digit numbers
			cout << " ";
		}

		findPath(from, to); //need extra for locations
		cout << endl;
		displayLocation(from, to);
	}
}

const int Graph::numEdge() const { int total = 0;	for (int i = 1; i <= size; i++) { EdgeNode* v = vertices[i].edgeHead;		while (v != nullptr) { total++;			v = v->nextEdge; } }	return total; }