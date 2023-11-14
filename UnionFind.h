#pragma once

#include "Header.h"

class UnionFind
{
	struct Item
	{
		int parent;                //The parent of the vertex (and item) in the disjoint set.
		int size;                  //The number of elemnts in the group of the vertex (the item).
	};
private:

	Item* arr;                     //Array of items in the UnionFind structure.

public:
	
	UnionFind(int n);              //UnionFind Ctor, gets as input number of members 'n'.
	
	void MakeSet(int x);           //Make new disjoint-set with representative 'x'.
	
	int Find(int x);               //find the represntative of vertex 'x'.
	
	void Union(int repx, int repy);//Unions between the group of 'x' and the group of 'y'.
	
	void Print();                  //Print disjoint-set (for tests)
};

