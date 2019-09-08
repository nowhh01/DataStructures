#include <iostream>
#include <vector>
#include <array>

/*
  O(n log n) 
 */

inline constexpr int LeftChild(const int i)
{
	return 2 * i + 1;
}

template<typename Comparable>
void Heapify(int i, const int size, std::vector<Comparable>* const outData)
{
	int child;
	Comparable tmp;

	for(tmp = std::move(outData->at(i)); LeftChild(i) < size; i = child)
	{
		child = LeftChild(i);

		if(child != size - 1 && outData->at(child) < outData->at(child + 1))  // find which child is bigger
		{
			++child;
		}

		if(tmp < outData->at(child))  // check if child is bigger than parent
		{
			outData->at(i) = std::move(outData->at(child));
		}
		else
		{
			break;
		}
	}
	
	outData->at(i) = std::move(tmp);
}

template<typename Comparable>
void HeapSort(std::vector<Comparable>* const outData)
{
	for(int i = outData->size() / 2 - 1; i >= 0; --i)
	{
		Heapify(i, outData->size(), outData);
	}

	for(int i = outData->size() - 1; i > 0; --i)
	{
		std::swap(outData->at(0), outData->at(i));
		Heapify(0, i, outData);
	}
}

int main()
{
	std::vector<int> a1{ 8, 6, 4, 4, 1, 9, 2 };
	HeapSort(&a1);

	for(const auto& x : a1)
	{
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
