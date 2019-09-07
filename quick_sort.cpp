#include <iostream>
#include <vector>
#include <utility>
#include "insertion_sort.cpp"

// best: O(n log n)
// average: O(n log n)
// worst: O(n * n)

/*
   return median of left, center and right.
   - better than choosing first element as pivot as the pivot provides a poor partition when the input is presorted.
   - better than choosing pivot randomly as ramdom number generation is generally an expensive commodity and does not reduce the average running time of the rest of the algorithm at all.
 */
template<typename Comparable>
const Comparable& GetMedian(const int left, const int right, std::vector<Comparable>* const outData)
{
	int center = (left + right) / 2;

	if(outData->at(center) < outData->at(left))
	{
		std::swap(outData->at(left), outData->at(center));
	}

	if(outData->at(right) < outData->at(left))
	{
		std::swap(outData->at(left), outData->at(right));
	}

	if(outData->at(right) < outData->at(center))
	{
		std::swap(outData->at(center), outData->at(right));
	}

	std::swap(outData->at(center), outData->at(right - 1));
	return outData->at(right - 1);
}

template<typename Comparable>
void QuickSort1(const int left, const int right, std::vector<Comparable>* const outData)
{
	const Comparable& pivot = GetMedian(left, right, outData);

	// begin partitioning
	int i{ left };
	int j{ right - 1 };

	for( ; ; )
	{
		while(outData->at(++i) < pivot) { }
		while(pivot < outData->at(--j)) { }

		if(i < j)
		{
			std::swap(outData->at(i), outData->at(j));
		}
		else
		{
			std::swap(outData->at(i), outData->at(right - 1));
			break;
		}
	}

	QuickSort1(left, i - 1, outData);
	QuickSort1(i + 1, right - 1, outData);
}

/*
   For very small arrays(N <= 20), quick sort does not perform as well as insertion sort.
   A good cutoff range is N = 10 although any cutoff between 5 and 20 is likely to produce similar results.
   It saves some cases, such as taking the median of three elements when there are only one or two.
 */
template<typename Comparable>
void QuickSort2(const int left, const int right, std::vector<Comparable>* const outData)
{
	if(left + 10 <= right)
	{
		const Comparable& pivot = GetMedian(left, right, outData);

		int i{ left };
		int j{ right - 1 };

		for( ; ; )
		{
			while(outData->at(++i) < pivot) { }
			while(pivot < outData->at(--j)) { }

			if(i < j)
			{
				std::swap(outData->at(i), outData->at(j));
			}
			else
			{
				break;
			}
		}

		std::swap(outData->at(i), outData->at(right - 1));
		QuickSort2(left, i - 1, outData);
		QuickSort2(i + 1, right, outData);
	}
	else // do insertion sort on the subarray
	{
		//InsertionSort(left, right, outData);
	}
}

/*
	average: O(n)
	Worst: O(n * n)
	paces the k-th smallest item in outData[k - 1]
	k is the desired rank (1 is minimum) in the entire array.
 */
template<typename Comparable>
void QuickSort3(const int left, const int right, const int k, std::vector<Comparable>* const outData)
{
	if(left + 10 <= right)
	{
		const Comparable& pivot = GetMedian(left, right, outData);

		int i{ left };
		int j{ right - 1 };

		for( ; ; )
		{
			while(outData->at(++i) < pivot) { }
			while(pivot < outData->at(--j)) { }

			if(i < j)
			{
				std::swap(outData->at(i), outData->at(j));
			}
			else
			{
				std::swap(outData->at(i), outData->at(right - 1));
				break;
			}
		}

		if(k <= i)
		{
			QuickSort3(left, i - 1, k, outData);
		}
		else if(k > i + 1)
		{
			QuickSort3(i + 1, right, k, outData);
		}
	}
	else
	{
		InsertSort(left, right, outData);
	}
}

template<typename Comparable>
void QuickSort(std::vector<Comparable>* const outData)
{
	QuickSort1(0, outData->size() - 1, outData);
}

int main()
{
	std::vector<int> a1{ 8, 6, 4, 4, 1, 9, 2, 78, 25, 45, 11, 35 };
	QuickSort(&a1);

	for(const auto& x : a1)
	{
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
