#include "Node.h"

template <typename T>
class LinkedLIst
{
private:
	Node<T> *Head;	
	int ItemCount;

public:
	LinkedLIst()
	{
		Head = nullptr;
		ItemCount = 0;
	}

	bool IsEmpty() const
	{
		return (Head == nullptr);
	}

	int GetLength() const
	{
		return ItemCount;
	}

	void Insert(const T& It)
	{
			Node<T>* newNodePtr = new Node<T>(It);
			if (!Head)
			{
				newNodePtr->SetNext(Head);
				Head = newNodePtr;
				ItemCount++;
				return;
			}
			Node<T>*Temp = Head;
			while (Temp->GetNext())
			{
				Temp->GetNext();
			}
			Temp->SetNext(newNodePtr);
			ItemCount++;
	}

	bool ReMove(const T& It)
	{
		Node<T>*Temp = Head;
		if (!Head)
			return false;

		if (Head->Getitem() == It)
		{
			Head = Head->GetNext();
			delete Temp;
			return true;
		}
		while (Temp->GetNext())
		{
			if (Temp->GetNext() == It)
			{
				Node<T>*ReMove = Temp->GetNext();
				Temp->SetNext(Temp->GetNext()->GetNext());
				delete ReMove;
			}
			Temp = Temp->GetNext();
		}
	}

	T GetEntry(const T&Item) const
	{
		Node<T>*Temp = Head;
		while (Temp)
		{
			if (Temp == Item)
				return Item;
		}
		return 0;
	}

	void Clear()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->GetNext();
			delete Head;
			Head = P;
		}
	}

	~LinkedLIst()
	{
		Clear();
	}
};