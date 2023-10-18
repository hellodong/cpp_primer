

#include <fstream>
#include <iterator>
#include <vector>
#include <string>


class TextDecode {
	public:
		TextDecode(const std::string &path, std::vector<std::string> *vec_str = nullptr)
		{
			input.open(path, std::ios::in);
			if(is_open() && nullptr != vec_str)
			{
				std::istream_iterator<std::string> in_iter(input), eof;
				while(in_iter != eof)
				{
					vec_str->push_back(*in_iter);
					words.push_back(*in_iter);
					in_iter++;
				}
			}
		}

		~TextDecode()
		{
			input.close();
		}

		bool is_open()
		{
			return input.is_open();
		}

		int decode(void);

		int copy(std::vector<std::string> &dest_vecStr);

		void dump();
	private:
		size_t word_get(const char ch_arr[]);

	private:
	std::ifstream input;
	std::vector<std::string> words;
};
