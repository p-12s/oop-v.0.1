#pragma once
#include <new>
#include <algorithm>
#include "MyIterator.h"


template <typename T>
class CMyArray
{
public:

	typedef CMyIterator<T> iterator;
	typedef CMyIterator<const T> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;

	friend iterator;
	friend const_iterator;
	friend reverse_iterator;
	friend reverse_const_iterator;

	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		CopyArray(arr.m_begin, arr.m_end, arr.GetSize());
	}

	CMyArray(CMyArray && arr)
		: m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	CMyArray(std::initializer_list<T>const& initList)
	{
		CopyArray(initList.begin(), initList.end(), initList.size());
	}

	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity)
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	void Resize(int value)
	{
		if (value < 0)
			throw std::runtime_error("Error! The size can not be less than 0");

		auto size = size_t(value);
		if (size != GetSize())
		{
			CMyArray copy;
			size_t min = std::min(size, GetSize());

			copy.m_begin = copy.RawAlloc(size);
			copy.m_end = copy.m_begin;
			copy.m_endOfCapacity = copy.m_begin + size;

			copy.CopyItems(m_begin, m_begin + min, copy.m_begin, copy.m_end);

			for (size_t i = min; i < size; ++i)
				copy.Append(T());

			*this = std::move(copy);
		}
	}

	void Clear()
	{
		DeleteItems(m_begin, m_end);
		m_begin = nullptr;
		m_end = nullptr;
		m_endOfCapacity = nullptr;
	}

	const T& operator[](size_t index) const // arr1[i] == arr2[i]
	{
		if (m_begin + index >= m_end || m_begin + index < m_begin)
			throw std::out_of_range("Error! Out of range"); // не покрыт тестом

		return *(m_begin + index);
	}

	T& operator[](size_t index) // auto a = arr1[i]
	{
		if (m_begin + index >= m_end || m_begin + index < m_begin)
			throw std::out_of_range("Error! Out of range");

		return *(m_begin + index);
	}

	CMyArray& operator=(CMyArray const& arr) // floatArr = floatArr
	{
		if (std::addressof(arr) != this)
		{
			CMyArray copy(arr);
			std::swap(m_begin, copy.m_begin);
			std::swap(m_end, copy.m_end);
			std::swap(m_endOfCapacity, copy.m_endOfCapacity);
		}
		return *this;
	}

	CMyArray& operator=(CMyArray && arr) // = arr1 + arr2
	{
		if (&arr != this)
		{
			Clear();
			m_begin = arr.m_begin;
			m_end = arr.m_end;
			m_endOfCapacity = arr.m_endOfCapacity;

			arr.m_begin = nullptr;
			arr.m_end = nullptr;
			arr.m_endOfCapacity = nullptr;
		}
		return *this;
	}

	size_t GetSize() const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity() const
	{
		return m_endOfCapacity - m_begin;
	}

	iterator begin()
	{
#if _DEBUG
		return iterator(m_begin, this);
#else
		return iterator(m_begin);
#endif
	}

	iterator end()
	{
#if _DEBUG
		return iterator(m_end, this);
#else
		return iterator(m_end);
#endif
	}

	const_iterator begin() const
	{
#if _DEBUG
		return const_iterator(m_begin, this);
#else
		return const_iterator(m_begin);
#endif
	}
	
	const_iterator end() const
	{
#if _DEBUG
		return const_iterator(m_end, this);
#else
		return const_iterator(m_end);
#endif	
	}

	reverse_iterator rbegin()
	{
#if _DEBUG
		return reverse_iterator(iterator(m_end, this));
#else
		return reverse_iterator(iterator(m_end));
#endif
	}

	reverse_iterator rend()
	{
#if _DEBUG
		return reverse_iterator(iterator(m_begin, this));
#else
		return reverse_iterator(iterator(m_begin));
#endif	
	}

	reverse_const_iterator rbegin() const
	{
#if _DEBUG
		return reverse_const_iterator(const_iterator(m_end, this));
#else
		return reverse_const_iterator(const_iterator(m_end));
#endif
	}

	reverse_const_iterator rend() const
	{
#if _DEBUG
		return reverse_const_iterator(const_iterator(m_begin, this));
#else
		return reverse_const_iterator(const_iterator(m_begin));
#endif
	}

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

private:
	static void DeleteItems(T *begin, T *end)
	{
		DestroyItems(begin, end);
		RawDealloc(begin);
	}

	static void CopyItems(const T *srcBegin, const T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			new (dstEnd)T(*srcBegin);
		}
	}

	void CopyArray(const T* from, const T* to, size_t size)
	{
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(from, to, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		while (to != from)
		{
			--to;
			to->~T();
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};
