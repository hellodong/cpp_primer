

#include <iostream>
#include <algorithm>
#include <cstring>
#include "textDecode.h"


size_t TextDecode::word_get(const char ch_arr[])
{
	int start = 0;
	for(int idx = 0;idx < strlen(ch_arr) + 1;idx++)
	{
		if (ch_arr[idx] == ' ' || ch_arr[idx] == '\0' )
		{
			words.push_back(std::string(ch_arr+start, idx - start));
			start = idx + 1;
		}
	}
	return words.size();
}

int TextDecode::decode(void) 
{
	char ch_array[1024];
	int words_counter = 0;
	while(!input.eof())
	{
		input.getline(ch_array, sizeof(ch_array));
		int ret = word_get(ch_array);
		if (ret > 0)
		{
			words_counter += ret;
		}
	}
	return words_counter;
}

void TextDecode::dump(void)
{
	std::cout << "TextDecode Size: " << words.size() << std::endl;
	for_each(words.begin(), words.end(),
			[](const std::string &a) {std::cout << a << " ";});	
	std::cout << std::endl;
}

int TextDecode::copy(std::vector<std::string> &dest_vecStr)
{
	dest_vecStr=words;
	return 0;
}
