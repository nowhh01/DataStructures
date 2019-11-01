#include <vector>
#include <list>
#include <algorithm>
#include <string>

template<typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101):mSize{size}{}

	constexpr bool Contains(const HashedObj& x) const;

	void Clear();
	bool Insert(const HashedObj& x);
	bool Insert(HashedObj&& x);
	bool Remove(const HashedObj& x);

private:
	std::vector<std::list<HashedObj>> mLists;   // The array of Lists
	int mSize;

	void rehash();
	size_t hash(const HashedObj& x) const;
};

template<typename Key>
class Hash
{
public:
	size_t operator() (const Key& k) const;
};

template<typename HashedObj>
size_t HashTable<HashedObj>::hash(const HashedObj& x) const
{
	static Hash<HashedObj> hf;
	return hf(x) % mLists.size();
}

template<typename HashedObj>
void HashTable<HashedObj>::Clear()
{
	for(auto& list : mLists)
	{
		list.clear();
	}
}

template<typename HashedObj>
constexpr bool HashTable<HashedObj>::Contains(const HashedObj& x) const
{
	auto& list = mLists[hash(x)];
	return std::find(begin(list), end(list), x) != end(list);
}

template<typename HashedObj>
bool HashTable<HashedObj>::Remove(const HashedObj& x)
{
	auto& list = mLists[hash(x)];
	auto itr = std::find(begin(list), end(list), x);

	if(itr == end(list))
	{
		return false;
	}

	list.erase(itr);
	--mSize;
	return true;
}

template<typename HashedObj>
bool HashTable<HashedObj>::Insert(const HashedObj& x)
{
	auto& list = mLists[hash(x)];
	if(std::find(begin(list), end(list), x) != end(list))
	{
		return false;
	}
	
	list.push_back(x);

	// rehash;
	if(++mSize > mLists.size())
	{
		rehash();
	}
	return true;
}

int main()
{
	HashTable<std::string> h{};
	//h.Insert("aa");
	//h.Insert("bb");
	//h.Insert("cc");
	//h.Insert("dd");
	//h.Insert("ee");

}
