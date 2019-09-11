#include <iostream>
#include <vector>
#include <string>

/*
   Radix sort an array of Strings
   Assume all are all ASCII
   Assume all have same length
 */
void RadixSort(const int stringLen, std::vector<std::string>* const outData)
{
	const int BUCKETS = 256;
	std::vector<std::vector<std::string>> buckets(BUCKETS);

	for(int pos = stringLen - 1; pos >= 0; --pos)
	{
		for(std::string& s : *outData)
		{
			buckets[s[pos]].push_back(std::move(s));
		}

		int index = 0;
		for(auto bucket : buckets)
		{
			for(std::string& s: bucket)
			{
				outData->at(index++) = std::move(s);
			}

			bucket.clear();
		}
	}
}

int main()
{
}
