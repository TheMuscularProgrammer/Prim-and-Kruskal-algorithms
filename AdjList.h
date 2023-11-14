#pragma once
#include "Vertex.h"

class Vertex;
class AdjList
{
private:
	Vertex* Head;                                                                                  //Pointer to the AdjList Head
	Vertex* Tail;                                                                                  //Pointer to the AdjList Tail

	bool isEmptyList()const { return Head == nullptr && Tail == nullptr; }                         //Checks if the AdjList is empty.
	Vertex* CreateVertex(int NewSerialNum, Vertex* NewNext, Vertex* NewPrev, int NewWeight )const; //Build new vertex.

public:
	AdjList(Vertex* newHead = nullptr, Vertex* newTail = nullptr) :Head(newHead), Tail(newTail) {} //Adjlist Ctor
	AdjList(const AdjList&) = delete;                                                              //Copy ctor
	~AdjList();                                                                                    //Dtor

	void SetHead(Vertex* newHead);                                                                 //Set AdjList head.
	Vertex* GetHead()const;                                                                        //Get AdjList head vertex.

	void addNodeToTheEndOfList(int v, int weight);                                                 //Add node to the end of the AdjList.

	Vertex* GetVertex(int vSerialNum)const;                                                        //Get pointer to a specific vertex using it's serial number.

	void DisconnectVEdge(int v);                                                                   //Find the vertex that the user asked to disconnect from vertex list.

	void PrintAdjList()const;                                                                      //Print the AdjList of a vertex - for tests
};

