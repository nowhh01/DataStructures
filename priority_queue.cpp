// problem is to allow relatively fast enqueuing and dequeuing
// adding: O(n)
// searching: O(n)

template<typename T>
struct Node
{
	T Data;
	Node* Next;
};

template<typename T, typename C>  // Type, Compare
class Queue
{
public:
	Queue();
	~Queue();

	int GetSize() const;
	bool IsEmpty() const;

	void Push(const T&);
	T& Top();
	T& Pop();

private:
	Node* mFront;
	int mSize;
};

template<typename T, typename C>
Queue<T, C>::Queue() : mFront{nullptr}, mSize{0}
{
	//decltype
}

template<typename T, typename C>
Queue<T, C>::~Queue()
{
}

template<typename T, typename C>
int Queue<T, C>::GetSize() const
{
	return mSize;
}

template<typename T, typename C>
bool Queue<T, C>::IsEmpty() const
{
	return mFront == nullptr;
}

template<typename T, typename C>
void Queue<T, C>::Push(const T& data)
{
	
}

template<typename T, typename C>
T& Queue<T, C>::Top()
{
	return;
}

template<typename T, typename C>
T& Queue<T, C>::Pop()
{
	return;
}

int main()
{
}
