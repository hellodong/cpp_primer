

#include <fstream>
#include <vector>
#include <string>


class TextDecode {
	public:
		TextDecode(const std::string &path )
		{
			input.open(path, std::ios::in);
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
	std::fstream input;
	std::vector<std::string> words;
};
