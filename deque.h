#pragma once

template< typename T = int >
class deque
{
private:
	struct iterator
	{
		T* cur;
		T* first;
		T* last;
		T** map_node;
	};
public:
	iterator begin() { return start; }
	iterator end() { return finish; }
	T& operator[](int n )
	{
		return start[n];
	}
	T front() { return *start; }
	T back()
	{
		iterator tmp = finish;
		tmp--;
		return *tmp;
	}

private:
	T** map;
	int map_size;
	iterator start;
	iterator finish;
};
