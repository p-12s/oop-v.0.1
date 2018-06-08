#pragma once
#include <iterator>
#include <initializer_list>
#include "MyArray.h"
#include <assert.h>

template<typename T>
class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
	template <typename> friend class CMyArray;
	CMyIterator(T* p);

#if _DEBUG
	CMyIterator(T* p, CMyArray<T> *array)
		: m_pointer(p)
		, m_array(array)
	{
	}
#endif

public:
	CMyIterator();

	CMyIterator& operator=(const CMyIterator &it);

	bool operator!=(CMyIterator const& other) const;

	bool operator==(CMyIterator const& other) const;

	T* operator->() const;

	T& operator[](ptrdiff_t index) const;

	T& operator*() const;

	CMyIterator& operator++();

	CMyIterator const operator++(int);

	CMyIterator& operator--();

	CMyIterator const operator--(int);

	bool operator<(CMyIterator const& other);

	bool operator>(CMyIterator const& other);

	bool operator<=(CMyIterator const& other);

	bool operator>=(CMyIterator const& other);

	CMyIterator const operator+(ptrdiff_t n) const;

	CMyIterator const operator-(ptrdiff_t n) const;

	ptrdiff_t const operator-(CMyIterator const& other) const;

private:
	T* m_pointer;
#if _DEBUG
	CMyArray<T> * m_array;
#endif
};

template<typename T>
CMyIterator<T>::CMyIterator()
	: m_pointer(nullptr)
{
}

template<typename T>
CMyIterator<T>::CMyIterator(T *p)
	: m_pointer(p)
{
}

template<typename T>
CMyIterator<T>& CMyIterator<T>::operator=(const CMyIterator& other)
{
	m_pointer = other.m_pointer;
#if _DEBUG
	m_array = other.m_array;
#endif
	return *this;
}

template<typename T>
bool CMyIterator<T>::operator!=(CMyIterator const& other) const
{
	return m_pointer != other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator==(CMyIterator const& other) const
{
	return m_pointer == other.m_pointer;
}

template<typename T>
T* CMyIterator<T>::operator->() const
{
	return std::addressof(operator*());
}

template<typename T>
T& CMyIterator<T>::operator[](ptrdiff_t index) const
{
#if _DEBUG
	if (m_array)
	{
		assert(m_pointer + index <= m_array->m_end);
	}
#endif
	return *(m_pointer + index);
}

template<typename T>
T & CMyIterator<T>::operator*() const
{
	return *m_pointer;
}

template<typename T>
CMyIterator<T> &CMyIterator<T>::operator++()
{
#if _DEBUG
	assert(m_pointer + 1 <= m_array->m_end);
#endif
	++m_pointer;
	return *this;
}

template<typename T>
CMyIterator<T> const CMyIterator<T>::operator++(int)
{
#if _DEBUG
	assert(m_pointer + 1 <= m_array->m_end);
#endif
	CMyIterator<T> tmpCopy(*this);

	++*this;
	return tmpCopy;
}

template<typename T>
CMyIterator<T> &CMyIterator<T>::operator--()
{
	--m_pointer;
	return *this;
}

template<typename T>
CMyIterator<T> const CMyIterator<T>::operator--(int)
{
	CMyIterator<T> tmpCopy(*this);
	--*this;
	return tmpCopy;
}

// странно - вычитать из указателья число
template<typename T>//TODO нужно ли реализоавывать?
CMyIterator<T> const CMyIterator<T>::operator+(ptrdiff_t n) const
{
	return m_pointer + n;
}

template<typename T>
ptrdiff_t const CMyIterator<T>::operator-(CMyIterator<T> const& other) const
{
	return m_pointer - other.m_pointer;
}

template<typename T>//TODO нужно ли реализоавывать? кому понадобится вычитать из итератора целое число?
CMyIterator<T> const CMyIterator<T>::operator-(ptrdiff_t n) const
{
	return m_pointer - n;
}

template<typename T>
CMyIterator<T> const operator+(ptrdiff_t n, CMyIterator<T> const& it)
{
	return it + n;
}

template<typename T>
bool CMyIterator<T>::operator<(CMyIterator const& other)
{
	return m_pointer < other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator>(CMyIterator const& other)
{
	return m_pointer > other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator<=(CMyIterator const& other)
{
	return m_pointer <= other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator>=(CMyIterator const& other)
{
	return m_pointer >= other.m_pointer;
}

