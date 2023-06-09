#pragma once
template<class t>
class Node
{
	t Item;
	Node<t>* Next;
	float Priority;
public:
	Node()
	{
		Next = nullptr;
		Priority = -1;
	};
	Node(t It)
	{
		Item = It;
		Next = nullptr;
		Priority = -1;
	}
	Node(t It, float Prio)
	{
		Item = It;
		Next = nullptr;
		Priority = Prio;
	}
	Node<t>* GetNext() const
	{
		return Next;
	}
	t Getitem() const
	{
		return Item;
	}
	void Setitem(t It)
	{
		Item = It;
	}
	void SetNext(Node<t>* nxt)
	{
		Next = nxt;
	}
	float GetPriority() const
	{
		return Priority;
	}
};