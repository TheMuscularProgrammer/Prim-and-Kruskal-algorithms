/**************************************************************************************
Project by:
1. Lior Roife     , ID: 206257826
2. Ori Leibovich  , ID: 307837096
 **************************************************************************************/

#pragma once

#include "UndirectedGraph.h"
#include "AdjList.h"
#include "VerticesHeap.h"
#include "UnionFind.h"
#include "Vertex.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdlib.h> 
#include <ctype.h>
#include <vector>
#include <time.h>  

#define INFINITY INT32_MAX
#define ERROR_MSG_IN_FILE "Error! Can't read the file."
#define ERROR_MSG_INVALID_INPUT "Invalid input."
#define ERROR_MSG_NO_MST "No MST."

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main Functions      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//Prim Algorithm, gets as input an undirected graph and returns int array of parents indexes that represent the edges in the MST of the given graph.
int* Prim(UndirectedGraph* Graph);
int CalculatePrimWeight(int* parent, UndirectedGraph* G);

//Kruskal Algorithm, gets as input an undirected graph' G' and returns vector of edges that represent the MST of the given graph.
vector<Edge> Kruskal(UndirectedGraph* Graph);
int CalculateKruskalWeight(vector<Edge> vec);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Auxiliary Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//QuickSort algorithm, gets as input vector of edges, 'start' index (0), 'end' index (vectors' size) and sorts the elements of the vector by the edge weights.
void Quicksort(vector<Edge>& v, int start, int end);
int Partition(vector<Edge>& v, int start, int end);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Test Functions      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//check_number function to check validity of string 'str' that represents number n (0 < n , int n)
bool check_number(string str);

//check_line_params function to check validity of strings vector that represents a single line from the input file
//(Edge To Add - in format: (s , d , w) Or Edge To Remove - in format : (s , d).
bool check_line_params(vector<string> paramsVector, int n, int& s, int& d, int& w);

//ParseStringLine function, gets as input string 'str' that represts a line from the input file and returns strings vectorwith the elements of the string.
vector<string> ParseStringLine(string str);