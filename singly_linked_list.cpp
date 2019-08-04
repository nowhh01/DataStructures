#include <iostream>

struct Node
{
	int Data;
	Node* Next;
};

class List
{
public:
	void Add(int value);
	void Insert(int index, int value);
	void Remove(int index, int value);
	int Size();

private:
	Node* head;
	Node* tail;

	int mSize;
};

void List::Add(int value)
{
}

void List::Insert(int index, int value)
{
}

void List::Remove(int index, int value)
{
}

int List::Size()
{
	return mSize;
}

int main()
{
}
