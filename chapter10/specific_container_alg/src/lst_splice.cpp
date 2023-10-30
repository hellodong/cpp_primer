
#include <iostream>
#include <fstream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <list>
#include <forward_list>


std::ostream &print(std::ostream &os, int val, char c)
{
	return os << val << c;
}

std::ostream_iterator<int> &tostr(std::ostream_iterator<int> &ostr_ite, int val)
{
	*ostr_ite++ = val;
	return ostr_ite;
}


int main(int argc, char *argv[])
{
	std::ifstream odd_file_input(argv[1]), even_file_input(argv[2]);
	std::istream_iterator<int> odd_istream(odd_file_input), even_istream(even_file_input), eof;
	std::list<int> lst_odd, lst_even, lst;
	std::forward_list<int> fwd_list, fwd_lst_even;
	while(odd_istream != eof)
	{
		lst_odd.push_back(*odd_istream);
		lst.push_back(*odd_istream);

		fwd_list.push_front(*odd_istream);

		odd_istream++;
	}
	while(even_istream != eof)
	{
		lst_even.push_back(*even_istream);

		fwd_lst_even.push_front(*even_istream);

		even_istream++;
	}

	std::cout <<"list size:" <<lst.size() << std::endl;
	std::for_each(lst.begin(), lst.end(),std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));
	std::cout << "\n even_list size:"<< lst_even.size() << std::endl;
	std::for_each(lst_even.begin(), lst_even.end(),std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	lst.splice(lst.begin(),lst_even);

	std::cout <<std::endl << "splice list size: " <<lst.size() << " even_list size: " << lst_even.size() << std::endl;
	std::for_each(lst.begin(), lst.end(),std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));


	std::cout << "\n forward list " << std::endl;
	for_each(fwd_list.begin(), fwd_list.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));
	std::cout << "\n forward list even" << std::endl;
	for_each(fwd_lst_even.begin(), fwd_lst_even.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	fwd_list.splice_after(fwd_list.before_begin(),fwd_lst_even);


	std::cout << std::endl << "splice forward list:" << std::endl;
	for_each(fwd_list.begin(), fwd_list.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	std::cout << std::endl << "forward list even:" << std::endl;
	for_each(fwd_lst_even.begin(), fwd_lst_even.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	return 0;
}

