#include <iostream>
#include <vector>
#include <utility>

/*
	worst: O(n log n)
 */

template<typename Comparable>
void Merge(int leftPos, int rightPos, int rightEnd, std::vector<Comparable>* const outData, std::vector<Comparable>* const outTmp)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	while(leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if(outData->at(leftPos) <= outData->at(rightPos))
		{
			outTmp->at(tmpPos++) = std::move(outData->at(leftPos++));
		}
		else
		{
			outTmp->at(tmpPos++) = std::move(outData->at(rightPos++));
		}
	}

	while(leftPos <= leftEnd)
	{
		outTmp->at(tmpPos++) = std::move(outData->at(leftPos++));
	}

	while(rightPos <= rightEnd)
	{
		outTmp->at(tmpPos++) = std::move(outData->at(rightPos++));
	}

	for(int i = 0; i < numElements; ++i, --rightEnd)
	{
		outData->at(rightEnd) = std::move(outTmp->at(rightEnd));
	}
}

template<typename Comparable>
void MergeSort(const int left, const int right, std::vector<Comparable>* const outData, std::vector<Comparable>* const outTmp)
{
	if(left < right)
	{
		int center = (left + right) / 2;
		MergeSort(left, center, outData, outTmp);
		MergeSort(center + 1, right, outData, outTmp);
		Merge(left, center + 1, right, outData, outTmp);
	}
}

template<typename Comparable>
void MergeSort(std::vector<Comparable>* const outData)
{
	std::vector<Comparable> tmp(int(outData->size()));

	MergeSort(0, int(tmp.size() - 1), outData, &tmp);
}

int main()
{
	std::vector<int> a1{ 8, 6, 4, 4, 1, 9, 2, 78, 25, 45, 11, 35 };
	MergeSort(&a1);

	for(const auto& x : a1)
	{
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
