#include <iostream>
#include <vector>
#include <array>

// average: O(n * n)
// presorted: O(n)

template<typename Comparable>
void InsertionSort(const int size, Comparable* const outData)  // for fixed array
{
	for(int i = 1; i < size; i++)
	{
		Comparable tmp{ *(outData + i) };         // two copies of data[i]

		int j;
		for(j = i; j > 0 && tmp < *(outData + j - 1); j--)
		{
			*(outData + j) = *(outData + j - 1);  // two copies of data[j - 1]
		}
		*(outData + j) = tmp;                     // two copies of tmp and a discarded copy of data[j]
	}
}

template<typename Comparable, size_t N>
void InsertionSort(std::array<Comparable, N>* const outData) // for std::array
{
	for(auto i = 1; i < N; i++)
	{
		Comparable tmp{ outData->at(i) }; 

		size_t j;
		for(j = i; j > 0 && tmp < outData->at(j - 1); j--)
		{
			outData->at(j) = outData->at(j - 1);
		}
		outData->at(j) = tmp;
	}
}

template<typename Comparable>
void InsertionSort(std::vector<Comparable>* const outData)  // for std::vector
{
	// https://en.wikipedia.org/wiki/C%2B%2B11#Rvalue_references_and_move_constructors
	for(int i = 1; i < outData->size(); i++)
	{
		Comparable tmp = std::move(outData->at(i)); // C++11: use rvalue reference copying the pointer so it prevents deep copy

		int j;
		for(j = i; j > 0 && tmp < outData->at(j - 1); j--)
		{
			outData->at(j) = std::move(outData->at(j - 1));
		}
		outData->at(j) = std::move(tmp);
	}
}

template<typename T>
void Swap(T* const outFirst, T* const outSecond)  // same as std::swap()
{
	T temp{ std::move(*outFirst) };
	*outFirst = std::move(*outSecond);
	*outSecond = std::move(temp);
}

/*
int main()
{
	int a1[7]{ 8, 6, 4, 4, 1, 9, 2 };
	InsertionSort(7, a1);
	std::array<int, 7> a2{ 8, 6, 4, 4, 1, 9, 2 }; // better than fixed array since fixed arrays lose its length info and dynamic arrays have messy deallocation issue and it is hard to resize them without error
	InsertionSort(&a2);
	std::vector<int> a3{ 5, 3, 1, 2, 9, 8, 7 };
	InsertionSort(&a3);

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
	
	for(const auto& x : a3)
	{
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
*/
