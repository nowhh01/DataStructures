#include <iostream>

struct Node
{
	Node* Next;
	int Data;
};

class List
{
public:
	List();
	~List();

	int GetHead() const;
	int GetTail() const;
	int GetSize() const;  // not modify return value

	void Add(int value);
	void Insert(int index, int value);
	void Remove(int index);

private:
	Node* mHead;
	Node* mTail;

	int mSize;           // size of List
};

List::List() : mHead(nullptr), mTail(nullptr), mSize(0) 
{
}

List::~List()
{
	Node* currentNode = nullptr;
	Node* nextNode = mHead;

	while(nextNode)   // while(nextNode != nullptr)
	{
		currentNode = nextNode;
		nextNode = nextNode->Next;

		delete currentNode;
	}
}

int List::GetHead() const
{
	return mHead->Data;
}

int List::GetTail() const
{
	return mTail->Data;
}

int List::GetSize() const
{
	return mSize;
}

void List::Add(int value)
{
	Node* temp = new Node;
	temp->Data = value;
	temp->Next = nullptr;

	if(mHead)    // if(mHead != nullptr)
	{
		mTail->Next = temp;
	}
	else
	{
		mHead = temp;
	}

	mTail = temp;
	mSize++;
}

void List::Insert(int index, int value)
{
	if(index >= 0 && index <= mSize)
	{
		Node* temp = new Node;
		temp->Data = value;

		if(index == 0)
		{
			temp->Next = mHead;
			mHead = temp;
		}
		else
		{
			Node* previousNode = nullptr;
			Node* currentNode = mHead;
		
			for(int i = 0; i < index; i++)
			{
				previousNode = currentNode;
				currentNode = currentNode->Next;
			}

			previousNode->Next = temp;
			temp->Next = currentNode;
		
			if(index == mSize)
			{
				mTail = temp;
			}
		}

		mSize++;
	}
}

void List::Remove(int index)
{
	if(index >= 0 && index < mSize)
	{
		Node* currentNode = mHead;

		if(index == 0)
		{
			mHead = currentNode->Next;
		}
		else
		{	
			Node* previousNode = nullptr;
			
			for(int i = 0; i < index; i++)
			{
				previousNode = currentNode;
				currentNode = currentNode->Next;
			}
	
			previousNode->Next = currentNode->Next;
		
			if(index == mSize - 1)
			{
				mTail = previousNode;
			}
		}

		delete currentNode;
		mSize--;
	}
}

int main()
{
	List list{};
	
	for(int i = 0; i < 5; i++)
	{
		list.Add(i);
	}

	list.Remove(0);
	list.Insert(0, 7);

	list.Remove(2);
	list.Insert(2, 9);

	list.Remove(4);
	list.Insert(4, 10);
}
