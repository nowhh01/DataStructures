#include <iostream>
#include <vector>
#include <array>

template<typename Comparable>
void HeapSort(std::vector<Comparable>* const outData)
{
	for(size_t i = outData->size() / 2 - 1; i >= 0; i--)
	{
		Heapify(i, outData->size(), outData);
	}

	for(size_t i = outData->size() - 1; i > 0; i--)
	{
		std::swap(outData->at(0), outData->at(i));
		Heapify(0, i, outData);
	}
}

inline const size_t LeftChild(const size_t i)
{
	return 2 * i + 1;
}

template<typename Comparable>
void Heapify(size_t i, const size_t size, std::vector<Comparable>* const outData)
{
	size_t child;
	Comparable tmp;

	for(tmp = std::move(outData->at(i)); LeftChild(i) < size; i = child)
	{
		child = LeftChild(i);

		if(child != size - 1 && outData->at(child) < outData->at(child + 1))
		{
			++child;
		}

		if(tmp < outData->at(child))
		{
			outData(i) = std::move(outData->at(child));
		}
		else
		{
			break;
		}
	}
	outData->at(i) = std::move(tmp);
}

int main()
{
}
