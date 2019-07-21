#pragma once
#include <iostream>
template<typename T>

struct myallocator
{
	// 内存开辟
	T* allocate(size_t size)
	{
		return (T*)malloc(size * sizeof(T));
	}

	// 内存释放
	void deallocate(T *ptr)
	{
		free(ptr);
	}

	// 对象构造 1.new 2.new const 3.定位new
	void construct(T *ptr, const T &obj)
	{
		new (ptr) T(obj); // 定位new
	}

	// 对象析构
	void destroy(T *ptr)
	{
		ptr->~T();
	}
};

template<typename T = int, typename _Alloc = myallocator<T>>
class Vector
{
public:
	Vector():mpvec(nullptr),mcur(0),msize(0)
	{}

	~Vector()
	{
		for (int i = 0; i < mcur; ++i)
    	{
			// 析构容器中有效的对象
     		malloctor.destroy(mpvec + i);
		}
		// 把容器内存释放掉
    	malloctor.deallocate(mpvec);
    	mpvec = nullptr;
	}

	Vector(const Vector<T> &vec)
		:mcur(vec.mcur), msize(vec.msize)
	{
		mpvec = malloctor.allocate(msize);
		for (int i = 0; i < vec.mcur; i++)
		{
			malloctor.construct(mpvec + i, vec.mpvec[i]);
		}
	}

	Vector(Vector<T> &&vec) 
		:mcur(vec.mcur), msize(vec.msize)
	{
		mpvec = vec.mpvec;
		vec.mpvec = nullptr;
	}

	void operator=(const Vector<T> &vec)
	{
		if (this == &vec) return;
    	T* ptem = malloctor.allocate(msize);
    	for (int i = 0; i < vec.mcur; i++)
    	{
	    	malloctor.construct(ptem + i, vec.mpvec[i]);
    	}
    	for (int i = 0; i < mcur; ++i)
    	{
	    	malloctor.destroy(mpvec + i);
    	}
    	malloctor.deallocate(mpvec);
    	mpvec = ptem;
	}

	void operator=(Vector<T> &&vec)
	{
		for (int i = 0; i < mcur; ++i)
	    {
			malloctor.destroy(mpvec + i);
		}
		malloctor.deallocate(mpvec);
		mpvec = vec.mpvec;
		vec.mpvec = nullptr;
		mcur = vec.mcur;
		msize = vec.msize;
	}


	void reserve(int size) // 预留函数
	{
		if (size < mcur) return;
		T* ptem = malloctor.allocate(size);
		for (int i = 0; i < mcur; ++i)
	    {
			malloctor.construct(ptem + i, mpvec[i]);
		}
		for (int i = 0; i < mcur; ++i)
		{
			malloctor.destroy(mpvec + i);
		}
		malloctor.deallocate(mpvec);
		mpvec = ptem;
		msize = size;
	}


	void push_back(const T &val) // 末尾添加元素
	{
		if (full()) resize();
		malloctor.construct(mpvec + mcur++, val);
	}

	void pop_back() // 末尾删除元素
	{
		if (empty()) return;
		malloctor.destroy(mpvec + --mcur);
	}

	bool empty()const // 判空
	{
		return 0 == mcur;
	}

	bool full()const // 判满
	{
		return msize == mcur;
	}

	void show()const // 打印vector容器的所有元素
	{
		for (int i = 0; i < mcur; ++i)
		{
			std::cout << mpvec[i] << " ";
		}
		std::cout << std::endl;
	}


	class iterator
	{
	public:
		iterator(T *p = nullptr) :_ptr(p) {}
		bool operator!=(const iterator &it)
		{
			return _ptr != it._ptr;
		}
		void operator++() { _ptr++; }
		void operator--() { _ptr--; }
		T& operator*() { return *_ptr; }
		T& operator[](int i) { return _ptr[i]; }
	private:
		T *_ptr;
	};
	iterator begin()
	{
		return iterator(mpvec);
	}
	iterator end()
	{
		return iterator(mpvec + mcur);
	}

	// 2.提供insert插入函数
	iterator insert(iterator &where, const T &val)
	{
		int pos = 0;
		Vector<T, _Alloc>::iterator it = begin();
		for (; it != where; ++it, ++pos);
		// 计算pos
		if (full()) resize();
		push_back(val);
		if (end() != where)
		{
			it = end();
			--it;
			Vector<T, _Alloc>::iterator item = it;
			--item;
			for (; it != where; --it, --item)
			{
				*it = *item;
			}
			*it = val;
		}
		mcur++;
		it = begin();
		for (int i = 0; i < pos; ++i, ++it);
		return it;
	}
	// 3.删除指定位置的元素
	iterator remove(iterator &where)
	{
		//if (!isItonLow(where))  throw out_of_range("...");
		Vector<T, _Alloc>::iterator it = where;
		++it;
		Vector<T, _Alloc>::iterator itemp = where;
		for (; it != end(); ++it, ++itemp)
		{
			*itemp = *it;
		}
		mcur--;
		return iterator(where);
	}
	// 4.提供operator    vec[2];
	T& operator[](iterator &where)
	{
		return *where;
	}
private:
	T *mpvec;
	int mcur;          // 元素个数
	int msize;
	_Alloc malloctor;  // 定义空间配置器对象 

	void resize() // vector容器底层默认2倍扩容
	{
		int size = 0;
		if (0 == mcur)
		{
			size = 1;
		}
		else
		{
			size = msize * 2;
		}
		reserve(size);
	}
	bool isItonLow(iterator &where)
	{
		return true;
	}
};

