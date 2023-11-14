#pragma once

class item
{
public:
	int data;                                               //Vertex serial number.
	int key;                                                //minimal weighted Vertex of edge that connects it to the Prim MST.
};

class VerticesMinHeap
{
private:
	int HeapSize;                                           //Current amount of vertices in the heap.
	int NumOfVerticesAtINIT;                                //The starting amount of vertices in the heap.
	int* Positions;                                         //Array of he indexes of the vertices in the heap.
	item** minHeap;                                         //Array of pointers to the to the items of the heap (pairs of serial number , distance).

    int Left(int indexOfVertex);                            //Gets as input index of vertex in the heap and returns its' left child index.
    int Right(int indexOfVertex);                           //Gets as input index of vertex in the heap and returns its' right child index.
    int Parent(int indexOfVertex);                          //Gets as input index of vertex in the heap and returns its' parent index.

public:
	VerticesMinHeap(int n);                                 //VerticesMinHeap Ctor, gets as input amount of vertices.
	VerticesMinHeap();                                      //Default VerticesMinHeap Ctor.
	bool isEmpty();                                         //Checks if the heap structure is empty - returns 'True' if it is and 'False' else.
	
	void Build(int vSize, int* WeightsArr);                 //Builds new heap accordint to vSize (amount of vertices in the heap) and array d
	void PrintHeap();                                       //Prints heap values (for tests).

	item* GetVertexBySerialNum(int indexOfVertex);          //Returns pointer to Vertex (item with data, key) by its'serial number.
	bool isVertexInHeap(int indexOfVertex);                 //Returns 'True' if vertex is in the heap structure and 'False' else (using input vertex index).
	
	void SwapElemsInHeap(item* FirstElem, item* SecondElem);//Swaps between 2 items (input) in the minHeap.

	void DecreaseKey(int indexOfVertex, int newKey);        //Updates the Vertex key to 'newKey' and according to its' index in the heap.
	void FixHeap(int indexOfVertex);                        //Fixes heap after changes (according to the index of the vertex and the new key value).
	item* DeleteMin();                                      //Delete minimal item from the heap.
};