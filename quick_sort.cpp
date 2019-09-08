#include <iostream>
#include <vector>
#include <utility>

// best: O(n log n)
// average: O(n log n)
// worst: O(n * n)

template<typename Comparable>
void QuickSort1(const int left, const int right, std::vector<Comparable>* const outData)
{
	if(right > left)
	{
		const Comparable pivot = std::move(outData->at(left));

		// begin partitioning
		int i{ left + 1 };
		int j{ right };

		for( ; ; )
		{
			while(i < right && outData->at(i) < pivot) 
			{
				i++;
			}
			while(i > left && pivot < outData->at(j))
			{
				j--;
			}

			if(i < j)
			{
				std::swap(outData->at(i), outData->at(j));
			}
			else
			{
				std::swap(outData->at(j), outData->at(left));
				break;
			}
		}

		QuickSort1(left, j - 1, outData);
		QuickSort1(j + 1, right, outData);
	}
}

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
void InsertionSort(const int left, const int right, std::vector<Comparable>* const outData)
{
	for(int i = left + 1; i < right + 1; i++)
	{
		Comparable tmp = std::move(outData->at(i));

		int j;
		for(j = i; j > 0 && tmp < outData->at(j - 1); j--)
		{
			outData->at(j) = std::move(outData->at(j- 1));
		}
		outData->at(j) = std::move(tmp);
	}
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
				std::swap(outData->at(i), outData->at(right - 1));
				break;
			}
		}

		QuickSort2(left, i - 1, outData);
		QuickSort2(i + 1, right, outData);
	}
	else // do insertion sort on the subarray
	{
		InsertionSort(left, right, outData);
	}
}

/*
average: O(n) due to saving a recursive call
Worst: O(n * n)
paces the k-th smallest item in outData[k - 1]
k is the desired rank (1 is minimum) in the entire array.
 */
template<typename Comparable>
void QuickSelect(const int left, const int right, const int k, std::vector<Comparable>* const outData)
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

		if(k <= i)  // With S1 and S2 based on pivot, the kth smallest element must be in S1
		{
			QuickSelect(left, i - 1, k, outData);
		}
		else if(k > i + 1)  // the kth smallest element lies in S2
		{
			QuickSelect(i + 1, right, k, outData);
		}
	}
	else
	{
		InsertionSort(left, right, outData);
	}
}

template<typename Comparable>
void QuickSort1(std::vector<Comparable>* const outData)
{
	QuickSort1(0, outData->size() - 1, outData);
}

template<typename Comparable>
void QuickSort2(std::vector<Comparable>* const outData)
{
	QuickSort2(0, outData->size() - 1, outData);
}

template<typename Comparable>
void QuickSelect(std::vector<Comparable>* const outData)
{
	QuickSelect(0, outData->size() - 1, 12, outData);
}

int main()
{
	std::vector<int> a1{ 8, 6, 4, 4, 1, 9, 2, 78, 25, 45, 11, 35 };
	std::vector<int> a2{ 8, 6, 4, 4, 1, 9, 2, 78, 25, 45, 11, 35 };
	std::vector<int> a3{ 8, 6, 4, 4, 1, 9, 2, 78, 25, 45, 11, 35 };
	QuickSort1(&a1);
	QuickSort2(&a2);
	QuickSelect(&a3);

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
