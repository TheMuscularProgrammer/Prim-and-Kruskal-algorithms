#pragma once

#include "AdjList.h"
#include <vector>

class Vertex;
class AdjList;
class UndirectedGraph
{
private:
	AdjList* TheGraph;                                              //Pointer to AdjList that represent the graph.
	int AmountOfVerticesInTheGraph;                                 //The number of vertices all over the grapth (final value).
	bool v_isEmptyGraph;                                            //Flag that becomes 'True' if the graph is empty, else it becomes 'False'.
	bool isValidVertex(int VertexSerialNum)const;                   // Private Func that checks if the required vertex is valid 
		                                                            // returns 'True' if yes and 'False' else
public:
	UndirectedGraph();                                              //UndirectedGraph basic Ctor
	UndirectedGraph(int AmountOfVerticesInTheGraph);                //UndirectedGraph Ctor, gets as input num of vertices.
	~UndirectedGraph();                                             //UndirectedGraph Dtor

	int GetAmountOfVertices() { return AmountOfVerticesInTheGraph; }//Returns the amount of vertices in the graph.

	void MakeEmptyGraph(int AmountOfVerticesInTheGraph);            //Build empty graph with 'AmountOfVerticesInTheGraph' vertices

	bool AddEdge(int u, int v, int weight);                         //Add Edge (u,v,w) from the graph

	bool RemoveEdge(int u, int v);                                  //Removes Edge (u,v) from the graph

	void PrintGraph()const;                                         //prints the graph values

	bool isEmpty()const { return v_isEmptyGraph; }                  //Checks whether the graph is empty or not

	bool IsAdjacent(int u, int v)const;                             //Returns true if edge (u,v) in the Graph

	const AdjList& GetAdjList(int u);                               //Returns a linked list of the vertex's neighbors.

	AdjList* GetTheGraph() { return TheGraph; }                     //Returns the graph (It's AdjList repesntation)

	bool isConnected();                                             //Recursive function to find out whether a graph is connected or not (using helper function - 'traverse').

	void traverse(int u, bool visited[]);                           //Helper function used in the function 'isConnected()'.
};