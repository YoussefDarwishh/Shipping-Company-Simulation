#pragma once
#include "Node.h"
template<class t>
class PriorityQueue
{
	Node<t>* FrontPointer;
	Node<t>* BackPointer;
	int Counter;
public:
	PriorityQueue()
	{
		FrontPointer = nullptr;
		BackPointer = nullptr;
		Counter = 0;
	}

	bool Isempty() const
	{
		if (FrontPointer)
			return false;
		return true;
	}
	
	void EnQueue(const t& Item,float Priority)
	{
		Node<t>* NPtr = new Node<t>(Item,Priority);
		if (Isempty())
		{
			FrontPointer = NPtr;
			BackPointer = NPtr;
		}
		else
		{
			if (NPtr->GetPriority() > FrontPointer->GetPriority())
			{
				NPtr->SetNext(FrontPointer);
				FrontPointer = NPtr;
			}
			else 
			{
				Node<t>* p = FrontPointer;
				Node<t>* Prev;
				while (p->GetPriority() >= NPtr->GetPriority())
				{
					Prev = p;
					p = p->GetNext();
					if (p == nullptr)
						break;
				}
				Prev->SetNext(NPtr);
				NPtr->SetNext(p);
				if (p == nullptr)
					BackPointer = NPtr;
			}
			
		}
		Counter++;
	}
	
	bool DeQueue(t& It)
	{
		if (Isempty())
			return false;
		Counter--;
		if (FrontPointer == BackPointer)
		{
			It = FrontPointer->Getitem();
			delete FrontPointer;
			FrontPointer = nullptr;
			BackPointer = nullptr;
			return true;
		}
		It = FrontPointer->Getitem();
		Node<t>* Temp = FrontPointer->GetNext();
		delete FrontPointer;
		FrontPointer = Temp;
		return true;
	}

	bool Peek(t& It)
	{
		if (Isempty())
			return false;
		It = FrontPointer->Getitem();
		return true;
	}
	int Count()
	{
		return Counter;
	}
	//copy construcTor
	PriorityQueue(const PriorityQueue<t>& LQ)
	{
		Node<t>* NodePtr = LQ.FrontPointer;
		if (!NodePtr) //LQ Is empty
		{
			FrontPointer = BackPointer = nullptr;
			return;
		}

		//insert the first node
		Node<t>* Ptr = new Node<t>(NodePtr->Getitem());
		FrontPointer = BackPointer = Ptr;
		NodePtr = NodePtr->GetNext();

		//insert remaining nodes
		while (NodePtr)
		{
			Node<t>* Ptr = new Node<t>(NodePtr->Getitem());
			BackPointer->SetNext(Ptr);
			BackPointer = Ptr;
			NodePtr = NodePtr->GetNext();
		}
	}
	void Print() const
	{
		Node < t >*Ptr= FrontPointer;
		while (Ptr)
		{
			if (Ptr->GetNext())
			{
				cout << Ptr->Getitem()<< ", ";
			}
			else
			{
				cout << Ptr->Getitem();
			}
			Ptr = Ptr->GetNext();
		}
	}
};