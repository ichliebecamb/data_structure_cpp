//#include "myvector.h"
#include "list.h"
#include "deque.h"
#include "myvector.h"
int main()
{
	/*
	Vector<int> data;
	for(int i = 0; i < 10 ; i++)
	{
		data.push_back(i);
	}
	
	data.show();
	*/
	/*
	list< int > data;
	deque<int > data1;
	for(int i = 0; i < 10; i++)
	{
		data.push_front(i);
	}

	auto it = data.begin();
	for(; it != data.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	*/
	Vector<int>  data;
	for(int i = 0; i < 10; i++)
	{
		data.push_back(i);
	}
	for( auto i = data.begin() ; i !=  data.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
	return 0;
}
