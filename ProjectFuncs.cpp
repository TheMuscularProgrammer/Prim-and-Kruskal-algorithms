#include "Header.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//Main Functions//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Prim algorithm on Graph 'G'
int* Prim(UndirectedGraph* Graph)
{
	//srand(time(NULL)); // for the randomness 
	//int StartVer = (rand() % Graph->GetAmountOfVertices()) + 1; //Randomize a number between 1 and (The Amount Of Vertices).
	int StartVer = 1; //get the number from 1 to the number of vertices

	int AmountOfVer = Graph->GetAmountOfVertices();
	VerticesMinHeap* TheHeap = new VerticesMinHeap(AmountOfVer);
	bool* IsOnTree = new bool[AmountOfVer];

	for (int i = 0; i <= AmountOfVer; i++)
	{
		IsOnTree[i] = false;
	}
	int* MinWeights = new int[AmountOfVer];
	int* Parents = new int[AmountOfVer];

	MinWeights[StartVer - 1] = 0;
	Parents[StartVer - 1] = -1;

	for (int j = 1; j <= AmountOfVer; j++)
	{
		if (j == StartVer)
		{
			MinWeights[StartVer] = 0;
		}
		else
		{
			MinWeights[j] = INFINITY;
		}
		Parents[j] = -1;
	}
	TheHeap->Build(AmountOfVer, MinWeights);
	//TheHeap->PrintHeap(); //for tests
	item* u;
	Vertex* vertex;

	while (!TheHeap->isEmpty())
	{
		u = TheHeap->DeleteMin();
		//cout << endl << "Deleted v: " << u->data << " " << u->key << endl; //for tests
		if (!IsOnTree[u->data])
		{
			IsOnTree[u->data] = true;
			vertex = Graph->GetAdjList(u->data).GetHead();
			while (vertex != nullptr)
			{
				if (!IsOnTree[vertex->GetVertexSerialNum()] && vertex->GetVertexWeight() < MinWeights[vertex->GetVertexSerialNum()])
				{
					int vSerial = vertex->GetVertexSerialNum();
					MinWeights[vSerial] = vertex->GetVertexWeight();
					Parents[vSerial] = u->data;
					TheHeap->DecreaseKey(vertex->GetVertexSerialNum(), MinWeights[vSerial]);
				}
				vertex = vertex->GetNext();
			}
		}
	}
	return Parents;
}

// Calculate sum of edge weights of the MST made by Prim algorithm on Graph 'G'.
int CalculatePrimWeight(int* parent, UndirectedGraph* G)
{
	int sum = 0;
	Vertex* Curr;
	for (int i = 1; i <= G->GetAmountOfVertices(); i++)
	{
		Curr = G->GetTheGraph()[i - 1].GetHead();
		while (parent[i] != -1 && Curr->GetVertexSerialNum() != parent[i])
		{
			Curr = Curr->GetNext();
		}

		if (parent[i] != -1)
		{
			sum += Curr->GetVertexWeight();
		}
	}
	return sum;
}

// Kruskal algorithm on Graph 'G' and return value of Edges vector representing the MST of the graph.
vector<Edge> Kruskal(UndirectedGraph* Graph)
{
	int OneEdge = 0, OntherEdge = 0;
	vector<Edge> GroupOfEdges;
	vector<Edge> TheFinalMinimalTree;


	UnionFind UF(Graph->GetAmountOfVertices() + 1);
	Edge Temp;

	Vertex* Curr = nullptr;
	for (int i = 0; i < Graph->GetAmountOfVertices(); i++)
	{
		Curr = Graph->GetTheGraph()[i].GetHead();
		while (Curr)
		{
			if (Curr->GetVertexSerialNum() > i + 1)        //to avoid duplicate edges
			{
				Temp.FromVer = i + 1;
				Temp.ToVer = Curr->GetVertexSerialNum();
				Temp.weight = Curr->GetVertexWeight();
				GroupOfEdges.push_back(Temp);
			}
			Curr = Curr->GetNext();
		}
	}
	Curr = nullptr;

	Quicksort(GroupOfEdges, 0, GroupOfEdges.size() - 1);   //sort the array by the weight filed

	for (int i = 1; i <= Graph->GetAmountOfVertices(); i++)
	{
		UF.MakeSet(i);
	}

	for (int j = 0; j < GroupOfEdges.size(); j++)
	{
		OneEdge = UF.Find(GroupOfEdges.at(j).FromVer);
		OntherEdge = UF.Find(GroupOfEdges.at(j).ToVer);

		if (OneEdge != OntherEdge)
		{
			Temp.FromVer = OneEdge;
			Temp.ToVer = OntherEdge;
			Temp.weight = GroupOfEdges.at(j).weight;
			TheFinalMinimalTree.push_back(Temp);
			UF.Union(OneEdge, OntherEdge);
		}
	}
	//cout << "The Weight of The Minimal Tree By Kruksal is: " << CalculateSum(TheFinalMinimalTree) << endl //for tests
	return TheFinalMinimalTree;
}

// Returns the result of sum of Edge Weights of input graph represented as Edges vector.
int CalculateKruskalWeight(vector<Edge> vec)
{
	int sum = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		sum += vec.at(i).weight;
	}
	return sum;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//Auxiliary Functions//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Partition for 'QuickSort'
int Partition(vector<Edge>& v, int start, int end)
{
	int pivot = end;
	int j = start;

	for (int i = start; i < end; ++i) 
	{
		if (v[i].weight < v[pivot].weight)
		{
			swap(v[i], v[j]);
			++j;
		}
	}
	swap(v[j], v[pivot]);
	return j;
}

// Sort the edges in the vector using last element as pivot in 'QuickSort'.
void Quicksort(vector<Edge>& v, int start, int end)
{
	if (start < end)
	{
		int p = Partition(v, start, end);
		Quicksort(v, start, p - 1);
		Quicksort(v, p + 1, end);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//Test Functions//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

bool check_number(string str)
{
	if (isdigit(str[0]) == false || str[0] == '0')
	{
		return false;
	}
	else
	{
		for (int i = 1; i < str.length(); i++)
			if (isdigit(str[i]) == false)
			{
				return false;
			}
	}
	return true;
}

bool check_line_params(vector<string> paramsVector, int n, int& s, int& d, int& w)
{
	//int s, d, w;
	float testW;
	if (paramsVector.size() != 3 && paramsVector.size() != 2)
	{
		return false;
	}
	if (paramsVector.size() == 3)
	{
		if (check_number(paramsVector.at(0)))
		{
			s = stoi(paramsVector.at(0));
			if (s > n || s < 1)
			{
				return false;
			}
		}
		else
			return false;

		if (check_number(paramsVector.at(1)))
		{
			d = stoi(paramsVector.at(1));
			if (d > n || d < 1)
			{
				return false;
			}
		}
		else
			return false;

		if (check_number(paramsVector.at(2)) || paramsVector.at(2)[0] == '-' && check_number(paramsVector.at(2).substr(1, paramsVector.at(2).length())))
		{
			testW = stof(paramsVector.at(2));
			w = stoi(paramsVector.at(2));
			if (w != (int)testW)
			{
				return false;
			}
		}
		else
			return false;

	}
	else//paramsVector.size()==2
	{
		if (check_number(paramsVector.at(0)))
		{
			s = stoi(paramsVector.at(0));
			if (s > n || s < 1)
			{
				return false;
			}
		}
		else
			return false;

		if (check_number(paramsVector.at(1)))
		{
			d = stoi(paramsVector.at(1));
			if (d > n || d < 1)
			{
				return false;
			}
		}
		else
			return false;
	}
	return true;
}

vector<string> ParseStringLine(string str)
{
	string delim = " ";
	vector<string> words{};

	size_t pos = 0;
	while ((pos = str.find(delim)) != string::npos)
	{
		words.push_back(str.substr(0, pos));
		str.erase(0, pos + delim.length());
	}
	words.push_back(str.substr(0, '\n'));

	return words;
}