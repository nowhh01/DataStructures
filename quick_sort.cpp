#include <iostream>
#include <vector>
#include <utility>

template<typename Comparable>
void QuickSort(std::vector<Comparable>* outData)
{
	QuickSort1(0, outData.size() - 1, outData);
}

template<typename Comparable>
void QuickSort1(int left, int right, std::vector<Comparable>* const outData)
{
	const Comparable& pivot = GetMedian(left, right, outData);

	int i = left;
	int j = right - 1;

	for( ; ; )
	{
		while(outData[++i] < pivot) { }
		while(pivot < outData[--j]) { }

		if(i < j)
		{
			std::swap(outData[i], outData[j]);
		}
		else
		{
			std::swap(outData[i], outData[right - 1]);
			break;
		}
	}

	QuickSort(left, i - 1, outData);
	QuickSort(i + 1, right, outData);
}

template<typename Comparable>
void QuickSort2(int left, int right, std::vector<Comparable>* const outData)
{
	if(left + 10 <= right)
	{
		const Comparable& pivot = GetMedian(left, right, outData);

		int i = left;
		int j = right - 1;

		for( ; ; )
		{
			while(outData[++i] < pivot) { }
			while(pivot < outData[--j]) { }

			if(i < j)
			{
				std::swap(outData[i], outData[j]);
			}
			else
			{
				std::swap(outData[i], outData[right - 1]);
				break;
			}
		}

		QuickSort(left, i - 1, outData);
		QuickSort(i + 1, right, outData);
	}
	else
	{
		//InsertionSort(left, right, outData);
	}
}

/*
   return median of left, center and right.

 */
template<typename Comparable>
const Comparable& GetMedian(int left, int right, std::vector<Comparable>* const outData)
{
	int center = (left + right) / 2;

	if(outData[center] < outData[left])
	{
		std::swap(outData[left], outData[center]);
	}

	if(outData[right] < outData[left])
	{
		std::swap(outData[left], outData[right]);
	}

	if(outData[right] < outData[center])
	{
		std::swap(outData[center], outData[right]);
	}

	std::swap(outData[center], outData[right - 1]);
	return outData[right - 1];
}

int main()
{
}
