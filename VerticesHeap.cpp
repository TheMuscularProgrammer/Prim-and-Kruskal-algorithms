#include "VerticesHeap.h"
#include <iostream>

using namespace std;

int VerticesMinHeap::Left(int indexOfVertex)
{
	return (2 * indexOfVertex);
}

int VerticesMinHeap::Right(int indexOfVertex)
{
	return (2 * indexOfVertex + 1);
}

int VerticesMinHeap::Parent(int indexOfVertex)
{
	return ((indexOfVertex - 1) / 2);
}

VerticesMinHeap::VerticesMinHeap(int n)
{
	Positions = nullptr;
	NumOfVerticesAtINIT = 0;
	HeapSize = 0;
	minHeap = new item * [n +1];
}

VerticesMinHeap::VerticesMinHeap()
{
	NumOfVerticesAtINIT = 0;
	HeapSize = 0;
	minHeap = new item * [1];
	Positions = new int[1];
}


bool VerticesMinHeap::isEmpty()
{
	return HeapSize == 0;
}

void VerticesMinHeap::Build(int vSize, int* WeightsArr)
{
	Positions = new int[vSize + 1];
	NumOfVerticesAtINIT = vSize + 1;
	for (int i = 0; i < vSize; i++)
	{
		minHeap[i] = new item;
		minHeap[i]->data = i + 1;
		minHeap[i]->key = WeightsArr[i + 1];
		Positions[i + 1] = i;
		HeapSize++;
	}
	for (int i = HeapSize / 2 - 1; i >= 0; i--)
	{
		FixHeap(i);
	}
}

void VerticesMinHeap::PrintHeap() //For tests
{
	for (int i = 0; i < HeapSize; i++)
	{
		cout << endl << minHeap[i]->data << " " << minHeap[i]->key << endl;
	}
	for (int j = 0; j < HeapSize; j++)
	{
		cout << endl << Positions[j] << " " << endl;
	}
}

item* VerticesMinHeap::GetVertexBySerialNum(int indexOfVertex)
{
	int exactPositionInHeapArray = Positions[indexOfVertex];
	if (isVertexInHeap(indexOfVertex))
	{
		return minHeap[exactPositionInHeapArray];
	}
	return nullptr;
}

bool VerticesMinHeap::isVertexInHeap(int indexOfVertex)
{
	for (int i = 0; i <= HeapSize; i++)
	{
		if (minHeap[i]->data == indexOfVertex)
			return true;
	}
	return false;
}

void VerticesMinHeap::SwapElemsInHeap(item* FirstElem, item* SecondEleme)
{
	int FirstPosition = Positions[FirstElem->data];
	int SecondPosition = Positions[SecondEleme->data];
	item* tempElem = minHeap[FirstPosition];
	minHeap[FirstPosition] = minHeap[SecondPosition];
	minHeap[SecondPosition] = tempElem;
	Positions[FirstElem->data] = SecondPosition;
	Positions[SecondEleme->data] = FirstPosition;
}

void VerticesMinHeap::DecreaseKey(int indexOfVertex, int newKey)
{
	if (indexOfVertex > 0 && indexOfVertex <= NumOfVerticesAtINIT)
	{
		int index = Positions[indexOfVertex];

		minHeap[index]->key = newKey;
		while (index != 0 && minHeap[index]->key < minHeap[Parent(index)]->key)
		{
			SwapElemsInHeap(minHeap[index], minHeap[Parent(index)]);
			index = Parent(index);
		}
	}
}

void VerticesMinHeap::FixHeap(int indexOfVertex)
{
	int min;
	int left = Left(indexOfVertex);
	int right = Right(indexOfVertex);
	if ((right <= HeapSize) && (minHeap[right]->key < minHeap[indexOfVertex]->key))
	{
		min = right;
	}
	else
	{
		min = indexOfVertex;
	}
	if ((left <= HeapSize) && (minHeap[left]->key < minHeap[min]->key))
	{
		min = left;
	}

	if (min != indexOfVertex)
	{
		SwapElemsInHeap(minHeap[indexOfVertex], minHeap[min]);
		FixHeap(min);
	}
}

item* VerticesMinHeap::DeleteMin()
{
	if (HeapSize < 1)
	{
		cout << "Error" << endl;
		return nullptr;//break
	}
	else if (HeapSize == 1)
	{
		HeapSize--;
		return minHeap[0];
	}
	else
	{
		item* min = minHeap[0];
		HeapSize--;
		minHeap[0] = minHeap[HeapSize];
		Positions[minHeap[0]->data] = 0;
		Positions[min->data] = -1;
		FixHeap(0);
		return min;
	}
}