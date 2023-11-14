#include "AdjList.h"
#include "Vertex.h"

AdjList::~AdjList()
{
	for (Vertex* p = Head; Head; p = Head)
	{
		Head = Head->GetNext();
		delete p;
	}
}

Vertex* AdjList::GetHead() const
{
	return Head;
}

void AdjList::SetHead(Vertex* newHead)
{
	Head = newHead;
}

Vertex* AdjList::CreateVertex(int NewSerialNum, Vertex* NewNext , Vertex* NewPrev, int NewWeight)const
{
	Vertex* newVertex = new Vertex(NewSerialNum, NewNext, NewPrev, NewWeight);
	assert(newVertex);//check 'newVertex's validity
	return newVertex;
}

Vertex* AdjList::GetVertex(int vSerialNum)const//returns nullptr if it does not exist;
{
	if (this->isEmptyList())//if AdjList is empty
		return nullptr;

	Vertex* curr = Head;
	while (curr)
	{
		if (curr->GetVertexSerialNum() == vSerialNum)
			return curr;
		curr = curr->GetNext();
	}
	return curr;
}

void AdjList::addNodeToTheEndOfList(int v, int weight)
{
	Vertex* lastV = CreateVertex(v, nullptr, nullptr, int INFINITY);
	lastV->SetVertexWeight(weight);
	if (isEmptyList())//if the AdjList empty
	{
		Head = Tail = lastV;
	}
	else
	{
		Tail->SetNext(lastV);
		lastV->SetPrev(Tail);
		Tail = lastV;
	}
}

void AdjList::DisconnectVEdge(int v) //Find the Vertex of the Edge that should be removed.
{
	Vertex* VtoDel = this->GetVertex(v);
	if (!VtoDel)                     //If we try to delete a vertex that does not exist 
	{
		cout << "Error! Invalid input " << endl;
		exit(1);
	}

	if (VtoDel == Head)              //If we try to delete the head vertex.
	{
		if (Head->GetNext() == nullptr)
		{
			delete Head;
			Head = nullptr;
			Tail = nullptr;
		}
		else	    	             //delete and update the list is empty (and the tail as well)
		{
			Head = Head->GetNext();
			Head->SetPrev(nullptr);
			delete VtoDel;
		}
		return;
	}

	if (VtoDel == Tail)//If we try to delete the tail vertex.
	{
		Tail = Tail->GetPrev();
		Tail->SetNext(nullptr);
		delete VtoDel;
		return;
	}
	//else - Vertex exist && not head && not tail
	Vertex* newPrevV = VtoDel->GetPrev();
	Vertex* newNextV = VtoDel->GetNext();
	newPrevV->SetNext(newNextV);
	newNextV->SetPrev(newPrevV);
	delete VtoDel;
	return;
}

void AdjList::PrintAdjList()const //Prints an AdjList (for tests).
{
	Vertex* curr = Head;
	while (curr)
	{
		cout << curr->GetVertexSerialNum() << " " ;
		curr = curr->GetNext();
	}
	cout << endl;
	cout << "------------------" << endl;
}
