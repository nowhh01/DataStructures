#include <iostream>

const int maxLevel = 4;

template<class T>
class SkipListNode
{
public:
	SkipListNode()
	{
	}
	T key;
	SkipListNode** next;
};

template<class T>
class SkipList
{
public:
	SkipList();
	bool isEmpty() const;
	void choosePowers();
	int chooseLevel();
	T* skipListSearch(const T&);
	void skipListInsert(const T&);

private:
	typedef SkipListNode<T> *nodePtr;
	nodePtr root[maxLevel];
	int powers[maxLevel];
};

template<class T>
SkipList<T>::SkipList()
{
	for(int i = 0; i < maxLevel; i++)
	{
		root[i] = 0;
	}
}

template<class T>
bool SkipList<T>::isEmpty() const
{
	return root[0] == 0;
}

template<class T>
void SkipList<T>::choosePowers()
{
	powers[maxLevel -1] = (2 << (maxLevel-1)) - 1;   // 2 ^ maxLevel - 1
	for(int i = maxLevel - 2, j = 0; i >= 0; i--, j++)
	{
		powers[i] = powers[i + 1] - (2 << j);        // 2 ^ (j + 1)
	}
}

template<class T>
int SkipList<T>::chooseLevel()
{
	int i, r = rand() % powers[maxLevel - 1] + 1;
	for(i = 1; i < maxLevel; i++)
	{
		if(r < powers[i])
		{
			return i - 1;   // return a level < the highest level;
		}
	}

	return i - 1;           // return the highest level;
}

template<class T>
T* SkipList<T>::skipListSearch(const T& key)
{
	if(isEmpty())
	{
		return 0;
	}

	nodePtr previous, current;
	int level;                // find the highest non-null
	
	for(level = maxLevel - 1; level >= 0 && !root[level]; level--)  // level
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
			else                             // if greater, go to the next non-null node on the same level
			{                                // or to a list on a list on a lower level;
				current = *(previous->next + -- level);
			}
		}
		else        // if greater, go to the next non-null node on the same level
		{           // or to a list on a list on a lower level;
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
void SkipList<T>::skipListInsert(const T& key)
{
	nodePtr current[maxLevel], previous[maxLevel], newNode;
	int level, i;
	current[maxLevel - 1] = root[maxLevel - 1];
	previous[maxLevel - 1] = 0;
	
	for(level = maxLevel - 1; level >= 0; level--)
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
			if(previous[level] == 0)                              // if not the lowest
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

	level = chooseLevel();                       // generate randomly level for newNode;
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
