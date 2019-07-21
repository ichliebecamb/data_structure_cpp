#pragma once
#include <iostream>

template<typename T = int >
class list
{
	private:
		struct _node
		{
			_node(const T& val = T())
				:_pre(nullptr)
				 ,_next(nullptr)
				 ,_data(val)
			{}
			_node *_pre;
			_node *_next;
			T _data;
		};
	public:
		list()
			:_length(0)
		{
			_head = new _node;
			_head->_pre = _head;
			_head->_next = _head;
		}
		~list()
		{}

		void push_back(const T &val)
		{
			insert(end(), val);
		}

		void push_front(T &val)
		{
			insert(begin(), val);
		}

		void erase()
		{
			
		}
		void pop_back()
		{
			if( empty() ) return;

		}

		void pop_front()
		{
			if( empty() ) return;

		}

		void clear()
		{}

		void remove()
		{}

		void unique()
		{}

		void splice()
		{}

		void merge()
		{}

		void reverse()
		{}

		void sort()
		{}


		class iterator
		{
			public:
				iterator(_node *p = nullptr)
					:_ptr(p) 
				{}
				void operator++() 
				{
					_ptr = _ptr->_next;
				}
				void operator--()
				{
					_ptr = _ptr->_pre;
				}
				bool operator!=(const iterator &it)
				{
					return _ptr != it._ptr;
				}
				bool operator==(const iterator &it)
				{
					return _ptr == it._ptr;
				}
				T& operator*()
				{
					return (*_ptr)._data;
				}

				_node* operator->()
				{
					return _ptr;
				}

				_node* _ptr;
		};

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		bool empty()
		{
			return begin() == end();
		}
		void insert(iterator pos, const T& val)
		{
			_node* node = new _node(val);
			if( empty() )
			{
				_head->_next = node;
				_head->_pre = node;
				node->_pre = _head;
				node->_next = _head;
			}
			else
			{
				node->_pre = pos._ptr->_pre;
				node->_next = pos._ptr;

				node->_pre->_next = node;
				node->_next->_pre = node;
			}
		}

		void destroy_node(iterator pos)
		{
			delete pos->_ptr;
		}

private:
		int _length;
		_node* _head;

};


