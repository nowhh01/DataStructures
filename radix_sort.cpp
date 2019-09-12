#include <iostream>
#include <vector>
#include <string>

/*
worst: O(w * n), where w is the number of bits required to store each key
Also known as bucket or digital sort
 */

/*
   Radix sort an array of Strings
   Assume all are all ASCII
   Assume all have same length
 */
void RadixSortWithFixedLength(const int stringLen, std::vector<std::string>* const outData)
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

/*
   Counting radix sort an array of Strings
   Assume all are all ASCII
   Assume all have same length
 */
void CountingRadixSort(const int stringLen, std::vector<std::string>* const outData)
{
	const int BUCKETS = 256;

	int n = outData->size();
	std::vector<std::string> buffer(n);

	std::vector<std::string>* in = outData;
	std::vector<std::string>* out = &buffer;

	for(int pos = stringLen - 1; pos >= 0; --pos)
	{
		std::vector<int> count(BUCKETS + 1);

		for(int i = 0; i < n; i++)
		{
			++count[in->at(i)[pos] + 1];
		}
		for(int b = 1; b <= BUCKETS; b++)
		{
			count[b] += count[b - 1];
		}
		for(int i = 0; i < n; i++)
		{
			out->at(count[in->at(i)[pos]]++) = std::move(in->at(i));
		}

		// swap in and out roles
		std::swap(in, out);
	}

	if(stringLen % 2 == 1)   // if odd number of passes, in is buffer, out is outData, so move back
	{
		for(int i = 0; i < outData->size(); i++)
		{
			outData->at(i) = std::move(in->at(i));
		}
	}
}

/*
   Radix sort an array of Strings
   Assume all are all ASCII
   Assume all have length bounded by maxLen
 */
void RadixSortWithVariableLengths(const int maxLen, std::vector<std::string>* const outData)
{
	const int BUCKETS = 256;

	std::vector<std::vector<std::string>> wordsByLength(maxLen + 1);
	std::vector<std::vector<std::string>> buckets(BUCKETS);

	for(std::string& s : *outData)
	{
		wordsByLength[s.length()].push_back(std::move(s));
	}

	int index{ 0 };
	for(auto& wordList : wordsByLength)
	{
		for(std::string& s : wordList)
		{
			outData->at(index++) = std::move(s);
		}
	}

	int startingIndex = outData->size();
	for(int pos = maxLen - 1; pos >= 0; pos--)
	{
		startingIndex -= wordsByLength[pos + 1].size();

		for(int i = startingIndex; i < outData->size(); i++)
		{
			buckets[outData->at(i)[pos]].push_back(std::move(outData->at(i)));
		}

		index = startingIndex;
		for(auto& bucket : buckets)
		{
			for(std::string& s : bucket)
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
