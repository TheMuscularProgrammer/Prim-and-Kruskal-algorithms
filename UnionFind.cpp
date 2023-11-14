#include "UnionFind.h"

class Item
{
public:
	int parent;
	int size;
};

UnionFind::UnionFind(int n)
{
	arr = new Item[n];
	for (int j = 0; j <= n; j++)
	{
		arr[j].parent = -1;
		arr[j].size = 0;
	}
}

void UnionFind::MakeSet(int x)
{
	arr[x].parent = x;
	arr[x].size = 1;
}

int UnionFind::Find(int x)
{
	if (arr[x].parent == x)
	{
		return x;
	}
	else
	{
		return arr[x].parent = Find(arr[x].parent);
	}
}

void UnionFind::Union(int repx, int repy)
{
	if (arr[repx].size >= arr[repy].size)
	{
		arr[repy].parent = repx;
		arr[repx].size += arr[repy].size;
	}
	else
	{
		arr[repx].parent = repy;
		arr[repy].size += arr[repx].size;
	}
}

void UnionFind::Print()
{
	for (int i = 1; i <= 6; i++)
	{
		cout << i << " " << arr[i].parent << " " << arr[i].size << endl;
	}
}