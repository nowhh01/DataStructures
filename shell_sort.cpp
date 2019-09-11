#include <iostream>
#include <vector>
#include <utility>

/*
worst: O(n * n)
average: depends on gap sequence
best: O(n log n) 
 */

template<typename Comparable>
void ShellSort(std::vector<Comparable>* outData)
{
	for(int gap = outData->size() / 2; gap > 0; gap /= 2)
	{
		for(int i = gap; i < outData->size(); ++i)
		{
			Comparable tmp = std::move(outData->at(i));
			int j = i;

			for( ; j >= gap && tmp < outData->at(j - gap); j -= gap)
			{
				outData->at(j) = std::move(outData->at(j - gap));
			}
			
			outData->at(j) = std::move(tmp);
		}
	}
}

int main()
{
	std::vector<int> a1{ 8, 6, 4, 4, 1, 9, 2, 78, 25, 45, 11, 35 };
	ShellSort(&a1);

	for(const auto& x : a1)
	{
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
