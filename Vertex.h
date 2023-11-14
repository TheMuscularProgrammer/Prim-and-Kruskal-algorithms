#pragma once

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <assert.h>
#include <string>

#define INIT_VAL -1                                     //Define of Initialization value of vertex SerialNum

using namespace std;

struct Edge                                            
{
	int FromVer;                                        //Vertex source (in edge).
	int ToVer;                                          //Vertex destination (in edge). 
	int weight;                                         //The weight of the edge (FromVer,ToVer).
};

class Vertex
{
private:
	int SerialNum;                                      //The serial number of the vertex.
	int Weight;                                         //The weight of the vertex (first vertex will be 0 , all others will be infinity in the init).
	Vertex* Next;                                       //The next vertex in the AdjList.
	Vertex* Prev;                                       //The previuos vertex in the AdjList.

public:

	//~Vertex() { delete[] Next; delete[] Prev; }
	Vertex(int SerialNum = INIT_VAL , Vertex* Next = nullptr, Vertex* Prev = nullptr, int Weight = INFINITY) :
		SerialNum(SerialNum), Next(Next), Prev(Prev), Weight(Weight) {}    //Vertex ctor

	Vertex* GetNext()const { return Next; }	           //Get the next vertex in List.
	void SetNext(Vertex* nextV) { Next = nextV; }      //Set the next vertex in List.

	Vertex* GetPrev()const { return Prev; }	           //Get the previous vertex in List
	void SetPrev(Vertex* prevV) { Prev = prevV; }      //Set the previous vertex in List

  	int GetVertexSerialNum()const { return SerialNum; }//Get the vertex's serial number.
	void SetVertexSerialNum(int NewSerialNum)          //Set the vertex's serial number.
	{
		SerialNum = NewSerialNum;
	}
	
	int GetVertexWeight()const { return Weight; }      //Get the vertex's weight.
	void SetVertexWeight(int NewWeight)                //Set the vertex's weight.
	{
		Weight = NewWeight;
	}
};
