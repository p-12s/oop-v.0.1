#pragma once
#include <iterator>
#include <initializer_list>
#include "MyArray.h"
#include <assert.h>

template<typename T>
class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
	//friend class CMyArray;
private:
	template <typename> friend class CMyArray;
	CMyIterator(T* p);

public:
	CMyIterator();//  = delete по сергею
	CMyIterator(const CMyIterator &it);//копирующий конструктор //  = default по сергею

/*#if _DEBUG
	CMyIterator(T* p, CMyArray<T> *array)
		: m_pointer(p)
		, m_array(array)
	{
	}
#endif*/

	CMyIterator& operator=(const CMyIterator &it);

	bool operator!=(CMyIterator const& other) const;

	bool operator==(CMyIterator const& other) const;

	T* operator->() const;

	T& operator[](ptrdiff_t index) const;

	T& operator*() const; // typename OwnIterator::reference operator*() const;

	CMyIterator& operator++();

	CMyIterator const operator++(int);

	CMyIterator& operator--();

	CMyIterator const operator--(int);

	bool operator<(CMyIterator const& other);

	bool operator>(CMyIterator const& other);

	bool operator<=(CMyIterator const& other);

	bool operator>=(CMyIterator const& other);

	CMyIterator const operator+(ptrdiff_t n) const;

	CMyIterator const operator-(ptrdiff_t n) const; // it - 3

	ptrdiff_t const operator-(CMyIterator const& other) const;

private:
	/*
#if _DEBUG
	CMyArray<T> * m_array;//TODO для проверки
#endif*/

	T* m_pointer;
};


template<typename T> // ОК
CMyIterator<T>::CMyIterator(T *p)
	: m_pointer(p)
{
}

template<typename T>// ??????/ в статье нет 
inline CMyIterator<T>::CMyIterator()
	: m_pointer(nullptr)
{
}

template<typename T>//ОК
CMyIterator<T>::CMyIterator(const CMyIterator& it)
	: m_pointer(it.m_pointer)
{
}
/*
#if _DEBUG
template<typename T>                мб в конуструкторе нзначить?
void CMyIterator<T>::SetArray(CMyArray<T> const* array)
{
	m_array = array;
}
#endif*/

template<typename T>
CMyIterator<T> & CMyIterator<T>::operator=(const CMyIterator & it)
{
	m_pointer = it.m_pointer;
	return *this;
}

template<typename T>//ОК
bool CMyIterator<T>::operator!=(CMyIterator const& other) const
{
	return m_pointer != other.m_pointer;
}

template<typename T>//ОК
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
{/*
#if _DEBUG
	if (m_array)
	{
		assert(m_pointer + index <= m_array->m_end);
	}
#endif*/
	return *(m_pointer + index);
}

template<typename T>
T & CMyIterator<T>::operator*() const
{
	return *m_pointer;
}
/*
 template<typename ValueType>
typename OwnIterator<ValueType>::reference OwnIterator<ValueType>::operator*() const
{
    return *p;
}
 */

template<typename T>
CMyIterator<T> &CMyIterator<T>::operator++()//префиксный
{/*
#if _DEBUG
	assert(m_pointer + 1 <= m_array->m_end);//m_array не должен быть нулл
#endif*/
	++m_pointer;
	return *this;
}

template<typename T>
CMyIterator<T> const CMyIterator<T>::operator++(int)//постфксный
{/*
#if _DEBUG
	assert(m_pointer + 1 <= m_array->m_end);
#endif*/
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

template<typename T>
CMyIterator<T> const CMyIterator<T>::operator+(ptrdiff_t n) const
{
	return m_pointer + n;
}

// It is the signed integer type of the result of subtracting two pointers
template<typename T>
ptrdiff_t const CMyIterator<T>::operator-(CMyIterator<T> const & other) const
{
	return m_pointer - other.m_pointer;
}

template<typename T>
CMyIterator<T> const CMyIterator<T>::operator-(ptrdiff_t n) const
{
	return m_pointer - n;
}

template<typename T>
CMyIterator<T> const operator+(ptrdiff_t n, CMyIterator<T> const& iter)
{
	return iter + n;
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

