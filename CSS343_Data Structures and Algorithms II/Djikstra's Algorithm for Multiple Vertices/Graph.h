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

#include "Vertex.h"
#include <iostream>
using namespace std;

class Graph {

private:
	static const int MAX_VERTICES = 101;
		
	struct EdgeNode {
		int adjVertex;			// subscript of the adjacent vertex 
		int weight;				// weight of edge
		EdgeNode *nextEdge;
	};

	struct VertexNode {
		EdgeNode* edgeHead;		// head of the list of edges
		Vertex* data;			// store vertex data here
	};

	// adjacency list of VertexNodes
	VertexNode vertices[MAX_VERTICES];

	// table of information for Dijkstra's algorithm
	struct Table {
		bool visited;			// whether vertex has been visited
		int dist;				// shortest known distance from source
		int path;				// previous vertex in path of min dist
	};

	int size;					// number of vertices in the graph
	
	// Table stores visited, distance, path - two dimensional in order to solve for all sources
	Table T[MAX_VERTICES][MAX_VERTICES];

	/* private helper: copyHelper
	Preconditions: Graph object is initialized
	Postconditions: a deep copy of the Graph input will be copied to the calling object's Graph instance
	*/
	void copyHelper(const Graph& input);

	/*private helper: destructor helper
	Preconditions: Graph object is initialized
	Postconditions: all contents of current Graph object are deleted in memory, vertices and Table array are deleted, size is set to 0
	*/
	void destructorHelper();

	/*private helper: insertHelper
	Preconditions: root and toInsert are initialized EdgeNodes
	Postconditions: insert toInsert into the adjacency list rooted at root
					if toInsert's adjVertex already existed inside the adjacency list, the weight of that adjVertex will be replaced by the new toInsert's weight
	*/
	void insertHelper(EdgeNode*& root, EdgeNode* toInsert);

	/* private helper: resetTable
	Postconditions: Table T of calling Graph instance will be reset: all visited will be false, all dist will be INT_MAX, all path will be 0
	*/
	void resetTable();

	/*private helper: findNextVertex
	Preconditions: source > 0 && source <=size
	Postconditions: finds the next adjacent vertex with minimum weight to the calling vertex objext
					returns -1 if not found
	*/
	int findNextVertex(int source);

	/*private helper: isThereEdge
	Preconditions: source > 0 && source <= size, dest > 0
	Postconditions: returns true if there exists an edge between the source and dist vertex
					returns false if not found
	*/
	bool isThereEdge(int source, int dest);

	/*private helper: getWeight
	Preconditions: source > 0 && source <= size, dest > 0
	Postconditions: returns weight between source and dest vertices
					returns -1 if not found an edge between 2 vertices
	*/
	int getWeight(int source, int dest);

	/*private helper: djikstra
	Preconditions: source > 0 && source <= size
	Postconditions: performs djikstra's shortest weighted path algorithm from given source vertex;
					updates visited vertices, shortest distance, and path values in Table T after execution
	*/
	void djikstra(int source);

	/* private helper: findPath
	Preconditions: from > 0 && from <= size, to > 0 && to <= size
	Postconditions: displays the path taken to go from source vertex to ending vertex with the shortest path
	*/
	void findPath(const int from, const int to) const;

	/*private helper: displayLocation
	Preconditions: from > 0 && from <= size, to > 0 && to <= size
	Postconditions: displays the path's location names to go from source vertex to ending vertex 
	*/
	void displayLocation(const int from, const int to) const;

public:
	const int numEdge() const;
	/* default constructor
	Postconditions: new Graph instance is instantiated
					vertices array stores adjacency list with each edgehead being nullptr; Graph will have no more than 100 vertices.
					Table T stores all visited values as false, dist = INT_MAX, path = 0
					size is 0
	*/
	Graph();

	/* copy constructor
	Preconditions:Preconditions: Graph object is initialized
	Postconditions: a deep copy of the Graph input will be copied to the calling object's Graph instance
	*/
	Graph(const Graph&);

	/* destructor
	Preconditions: Graph input is initialized
	Postconditions: all contents of current Graph object are deleted in memory, vertices and Table array are deleted, size is set to 0
	*/
	~Graph();

	/* operator=
	Preconditions: Graph input is initialized
	Postconditions:the calling Graph object is assigned to the current Graph object with a deep copy
				   and both objects share the same memory address
	*/
	const Graph& operator=(const Graph&);

	/*buildGraph: Builds a Graph by reading data from an ifstream
	Preconditions:  infile has been successfully opened and the file contains
	                properly formated data (according to the program specs)
	Postconditions: One Graph is read from infile and stored in the object
	*/
	void buildGraph(ifstream&);

	/* insertEdge
	Preconditions: src > 0 && src <= size, dest > 0 && dest <= size, weight > 0 
	Postconditions: insert new vertex into the adjacency list with the source src, destination dest, and weight
					if destination vertex already existed inside the adjacency list rooted at src, the weight of destination vertex will be replaced by the new weight
	*/
	void insertEdge(const int src, const int dest, const int weight);

	/*removeEdge: removes the edge between source vertex and adjacent vertex
	Preconditions: source > 0 && source <= size, adjacent > 0 
	Postconditions: returns true if removal was successful
					returns false if invalid input, or cannot find destination vertex
	*/
	bool removeEdge(const int source, const int adjacent);

	/*findShortestPath
	Preconditions: calling Graph object is instantiated
	Postconditions: performs Djikstra's algorithm to find the shortest weighted path from all source vertices to other vertices in Graph 
	*/
	void findShortestPath();

	/*displayAll
	Preconditions: calling Graph object is instantiated
	Postconditions: displays location name, source vertex, destination vertex, shortest weighted path between the source and destination, 
					and the path taken from source to get to destination vertex;
					if there are no path, displays "--"
	*/
	void displayAll();

	/* display
	Preconditions: from > 0 && from <= size, to > 0 && to <= size
	Postconditions: displays the source vertex, destination vertex, the shortest weighted edge between them, and path taken to get from source to destination
					displays location name from source to get to destination
	*/
	void display(const int from, const int to);
};
