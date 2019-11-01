#include <iostream>

constexpr int MAX_LEVEL = 4;

template<class T>
struct Node
{
	T Key;
	Node** Next;
};

template<class T>
class SkipList
{
public:
	SkipList();
	~SkipList();

	constexpr bool IsEmpty() const;
	
	T* SkipListSearch(const T&);
	int ChooseLevel();
	
	void ChoosePowers();
	void SkipListInsert(const T&);

private:
	Node<T>* root[MAX_LEVEL];
	int powers[MAX_LEVEL];
};

template<class T>
SkipList<T>::SkipList()
{
	for(int i = 0; i < MAX_LEVEL; i++)
	{
		root[i] = 0;
	}
}

template<class T>
SkipList<T>::~SkipList()
{
}

template<class T>
constexpr bool SkipList<T>::IsEmpty() const
{
	return root[0] == 0;
}

template<class T>
void SkipList<T>::ChoosePowers()
{
	powers[MAX_LEVEL -1] = (2 << (MAX_LEVEL - 1)) - 1;
	
	for(int i = MAX_LEVEL - 2, j = 0; i >= 0; i--, j++)
	{
		powers[i] = powers[i + 1] - (2 << j);
	}
}

template<class T>
int SkipList<T>::ChooseLevel()
{
	int i, r = rand() % powers[MAX_LEVEL - 1] + 1;
	for(i = 1; i < MAX_LEVEL; i++)
	{
		if(r < powers[i])
		{
			return i - 1;   // return a level < the highest level;
		}
	}

	return i - 1;           // return the highest level;
}

template<class T>
T* SkipList<T>::SkipListSearch(const T& key)
{
	if(isEmpty())
	{
		return 0;
	}

	nodePtr previous, current;
	int level;
	
	for(level = MAX_LEVEL - 1; level >= 0 && !root[level]; level--)  // find the highest non-null level
	{
	}

	previous = current = root[level];

	while(true)
	{
		if(key == current->key)      // success if equal;
		{
			return &current->key;
		}
		else if(key < current->key)  // if smaller, go down
		{
			if(level == 0)           // if possible,
			{
				return 0;
			}
			else if(current == root[level])  // by one level
			{
				current = root[--level];     // starting from the predecessor which can be the root
			}
			else
			{
				current = *(previous->next + --level);
			}
		}
		else        // if greater, go to the next non-null node on the same level
		{           // or to a list on a lower level;
			previous = current;
			
			if(*(current->next + level) != 0)
			{
				current = *(current->next + level);
			}
			else
			{
				for(level--; level >= 0 && *(current->next + level) == 0; level--)
				{
				}

				if(level >= 0)
				{
					current = *(current->next + level);
				}
				else
				{
					return 0;
				}
			}
		}
	}
}

template<class T>
void SkipList<T>::SkipListInsert(const T& key)
{
	Node<T>* current[MAX_LEVEL], previous[MAX_LEVEL], newNode;
	int level, i;
	current[MAX_LEVEL - 1] = root[MAX_LEVEL - 1];
	previous[MAX_LEVEL - 1] = 0;
	
	for(level = MAX_LEVEL - 1; level >= 0; level--)
	{
		while(current[level] && current[level]->key < key)    // go to the next
		{
			previous[level] = current[level];                 // if smaller
			current[level] = *(current[level]->next + level);
		}

		if(current[level] && current[level]->key == key)      // don't include
		{
			return;                                           // duplicates
		}

		if(level > 0)                                         // go one level down
		{
			if(previous[level] == 0)                          // if not the lowest
			{
				current[level - 1] = root[level - 1];         // level, using a link
				previous[level - 1] = 0;                      // either from the root
			}
			else                                              // or from the predecessor 
			{
				current[level - 1] = *(previous[level]->next + level-1);
				previous[level - 1] = previous[level];
			}
		}
	}

	level = ChooseLevel();                       // generate randomly level for newNode;
	newNode = new SkipListNode<T>;
	newNode->next = new nodePtr[sizeof(nodePtr) * (level + 1)];
	newNode->key = key;

	for(i = 0; i < level; i++)                   // initialize next fields of newNode and reset to newNode
	{                                            // either fields of the root or next fields of newNode's predecessors
		*(newNode->next + i) = current[i];

		if(previous[i] == 0)
		{
			root[i] = newNode;
		}
		else
		{
			*(previous[i]->next + i) = newNode;
		}
	}
}

int main()
{
}
