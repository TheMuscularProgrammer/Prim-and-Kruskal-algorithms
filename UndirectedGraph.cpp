#include "UndirectedGraph.h"
#include "AdjList.h"

using namespace std;

#include <iostream>

bool UndirectedGraph::isValidVertex(int VertexSerialNum)const
{
	return (VertexSerialNum >= 1 && VertexSerialNum <= AmountOfVerticesInTheGraph);
}

UndirectedGraph::UndirectedGraph(int AmountOfVerticesInTheGraph)
{
	MakeEmptyGraph(AmountOfVerticesInTheGraph);
}

UndirectedGraph::~UndirectedGraph()
{
	delete[] TheGraph;
}

UndirectedGraph::UndirectedGraph()
{
	MakeEmptyGraph(1);

}

void UndirectedGraph::MakeEmptyGraph(int AmountOfVerticesInTheGraph)
{
	this->AmountOfVerticesInTheGraph = AmountOfVerticesInTheGraph;
	TheGraph = new AdjList[AmountOfVerticesInTheGraph + 1];

	for (int i = 0; i <= AmountOfVerticesInTheGraph; i++)
	{
		TheGraph[i].SetHead(nullptr);
	}
}

bool UndirectedGraph::AddEdge(int u, int v, int weight)
{
	if (!isValidVertex(u) || !isValidVertex(v))
	{
		//cout << "Error! Invalid input " << endl;
		
		return false;
		//exit(1);//break
	}
	TheGraph[u - 1].addNodeToTheEndOfList(v, weight);
	TheGraph[v - 1].addNodeToTheEndOfList(u, weight);
	return true;
}

bool UndirectedGraph::RemoveEdge(int u, int v)
{
	if (!IsAdjacent(u, v))
	{
		return false;
	}
	else
	{
		TheGraph[u - 1].DisconnectVEdge(v);
		TheGraph[v - 1].DisconnectVEdge(u);
		return true;
	}
}

const AdjList& UndirectedGraph::GetAdjList(int u)
{
	if (!isValidVertex(u))
	{
		cout << "Error! Invalid input " << endl;
		exit(1);//break
	}
	return TheGraph[u - 1];
}

void UndirectedGraph::PrintGraph()const   //for tests
{
	cout << endl;
	if (isEmpty())
	{
		cout << "Error! Invalid input " << endl;
		exit(1);//break
	}
	for (int i = 1; i <= AmountOfVerticesInTheGraph; i++)
	{
		cout << " V: " << i << '\t' << "List: " ;
		TheGraph[i-1].PrintAdjList();
	}
}

bool UndirectedGraph::IsAdjacent(int u, int v)const
{ 
	Vertex* curr = TheGraph[u-1].GetHead();
	while (curr != nullptr) 
	{
		if (curr->GetVertexSerialNum() == v)
			return true;
		curr = curr->GetNext();
	}
	return false;
}

//DFS helper
void UndirectedGraph::traverse(int u, bool visited[])
{
	int** graph = new int* [AmountOfVerticesInTheGraph];

	for (int i = 0; i < AmountOfVerticesInTheGraph; ++i)
	{
		graph[i] = new int[AmountOfVerticesInTheGraph];
	}
	for (int i = 0; i < AmountOfVerticesInTheGraph; ++i)
	{
		for (int j = 0; j < AmountOfVerticesInTheGraph; ++j)
		{
			if (IsAdjacent(i+1, j+1)) 
			{
				graph[i][j] = 1;
			}
			else
			{
				graph[i][j] = 0;
			}
		}
	}
	visited[u] = true; 
	for (int v = 0; v < AmountOfVerticesInTheGraph; v++)
	{
		if (graph[u][v])
		{
			if (!visited[v])
				traverse(v, visited);
		}
	}
}
//DFS
bool UndirectedGraph::isConnected()
{
	bool* visible = new bool[AmountOfVerticesInTheGraph];
	//for all vertex u as start point, check whether all nodes are visible or not.
	for (int u = 0; u < AmountOfVerticesInTheGraph; u++)
	{
		for (int i = 0; i < AmountOfVerticesInTheGraph; i++)
			visible[i] = false;       //initialize as no node is visited.
		traverse(u, visible);
		for (int i = 0; i < AmountOfVerticesInTheGraph; i++)
		{
			if (!visible[i])          //if there is a node, not visited by traversal, graph is not connected.
				return false;
		}
	}
	return true;
}