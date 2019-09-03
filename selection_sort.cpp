#include <iostream>
#include <utility>  // std::swap()
#include <vector>

// O(n * n)

template<typename Comparable>
void SelectionSort(const int size, Comparable* const outData)
{
	for(int i = 0; i < size - 1; i++)
	{
		int least = i;
		for(int j = i + 1; j < size; j++)
		{
			if(*(outData + j) < *(outData + least))
			{
				least = j;
			}
		}

		if(i != least)  // if the elements in data are large compound entities such as arrays or structures
		{               // then one swap may take much time so using a conditional swap() is recommended.
			std::swap(*(outData + least), *(outData + i));
		}
	}
}

template<typename Comparable>
void SelectionSort(std::vector<Comparable>* outData)
{
	size_t size{ outData->size() };
	for(size_t i = 0; i < size; i++)
	{
		size_t least = i;
		for(size_t j = i + 1; j < size; j++)
		{
			if(outData->at(j) < outData->at(least))
			{
				least = j;
			}
		}

		if(i != least)
		{
			std::swap(outData->at(least), outData->at(i));
		}
	}
}

template<typename T>
void Swap(T* const outFirst, T* const outSecond)   // same as std::swap()
{
	T tmp{ std::move(*outFirst) };
	*outFirst = std::move(*outSecond);
	*outSecond = std::move(tmp);
}

int main()
{	
	int a1[7]{ 8, 6, 4, 4, 1, 9, 2 };
	SelectionSort(7, a1);
	std::vector<int> a2{ 5, 3, 1, 2, 9, 8, 7 };
	SelectionSort(&a2);

	for(const auto& x : a1)
	{
		std::cout << x << ' ';
	}
	std::cout << '\n';

	for(const auto& x : a2)
	{
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
