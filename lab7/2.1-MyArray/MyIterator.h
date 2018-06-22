#pragma once
#include <assert.h>

template <typename T>
class CMyIterator
{
private:
	template <typename T> friend class CMyArray;

#if _DEBUG
	CMyIterator(T* p, CMyArray<T> *array) noexcept
		: m_pointer(p)
		, m_array(array)
	{
	}
#else
	CMyIterator(T* p) noexcept
		: m_pointer(p)
	{
	}
#endif

public:
	using self_type = CMyIterator;
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = ptrdiff_t;

	CMyIterator() noexcept;

	bool operator!=(CMyIterator const& other) const noexcept;

	bool operator==(CMyIterator const& other) const noexcept;

	T* operator->() const noexcept;

	T& operator[](size_t index) const noexcept;

	T& operator*() const noexcept;

	CMyIterator& operator++() noexcept;

	CMyIterator const operator++(int);

	CMyIterator& operator--();

	CMyIterator const operator--(int);

	bool operator<(CMyIterator const& other) noexcept;

	bool operator>(CMyIterator const& other) noexcept;

	bool operator<=(CMyIterator const& other) noexcept;

	bool operator>=(CMyIterator const& other) noexcept;

	CMyIterator const operator+(size_t n) const;

	CMyIterator const operator-(size_t n) const;

	size_t const operator-(CMyIterator const& other) const noexcept;


private:
	T* m_pointer;
#if _DEBUG
	CMyArray<T> * m_array;
#endif
};

template<typename T>
CMyIterator<T>::CMyIterator() noexcept
	: m_pointer(nullptr)
{
}

template<typename T>
bool CMyIterator<T>::operator!=(CMyIterator const& other) const noexcept
{
	return m_pointer != other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator==(CMyIterator const& other) const noexcept
{
	return m_pointer == other.m_pointer;
}

template<typename T>
T* CMyIterator<T>::operator->() const noexcept
{
	return std::addressof(operator*());
}

template<typename T>
T& CMyIterator<T>::operator[](size_t index) const noexcept
{
#if _DEBUG
	if (m_array)
	{
		assert(index < static_cast<size_t>(m_array->m_end - m_pointer));
	}
#endif
	return *(m_pointer + index);
}

template<typename T>
T& CMyIterator<T>::operator*() const noexcept
{
	return *m_pointer;
}

template<typename T>
CMyIterator<T> &CMyIterator<T>::operator++() noexcept
{
#if _DEBUG
	assert(m_pointer != m_array->m_end);
#endif
	++m_pointer;
	return *this;
}

template<typename T>
CMyIterator<T> const CMyIterator<T>::operator++(int)
{
#if _DEBUG
	assert(m_pointer != m_array->m_end);
#endif
	CMyIterator<T> tmpCopy(*this);

	++*this;
	return tmpCopy;
}

template<typename T>
CMyIterator<T> &CMyIterator<T>::operator--()
{
#if _DEBUG
	assert(m_pointer != m_array->m_begin);
#endif
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
CMyIterator<T> const CMyIterator<T>::operator+(size_t n) const
{
#if _DEBUG
	assert(n < static_cast<size_t>(m_array->m_end - m_pointer));
#endif
	CMyIterator<T> tmpCopy(*this);
	tmpCopy.m_pointer = m_pointer + n;
	return tmpCopy;
}

template<typename T>
CMyIterator<T> const operator+(size_t n, CMyIterator<T> const& it) noexcept
{
	return it + n;
}

template<typename T>
CMyIterator<T> const CMyIterator<T>::operator-(size_t n) const
{
#if _DEBUG
	assert(n < static_cast<size_t>(m_pointer - m_array->m_begin));
#endif
	CMyIterator<T> tmpCopy(*this);
	tmpCopy.m_pointer = m_pointer - n;
	return tmpCopy;
}

template<typename T>
size_t const CMyIterator<T>::operator-(CMyIterator<T> const& other) const noexcept
{
#if _DEBUG
	assert(m_array->m_begin == other.m_array->m_begin);
#endif
	return m_pointer - other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator<(CMyIterator const& other) noexcept
{
#if _DEBUG
	assert(m_array->m_begin == other.m_array->m_begin);
#endif
	return m_pointer < other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator>(CMyIterator const& other) noexcept
{
#if _DEBUG
	assert(m_array->m_begin == other.m_array->m_begin);
#endif
	return m_pointer > other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator<=(CMyIterator const& other) noexcept
{
#if _DEBUG
	assert(m_array->m_begin == other.m_array->m_begin);
#endif
	return m_pointer <= other.m_pointer;
}

template<typename T>
bool CMyIterator<T>::operator>=(CMyIterator const& other) noexcept
{
#if _DEBUG
	assert(m_array->m_begin == other.m_array->m_begin);
#endif
	return m_pointer >= other.m_pointer;
}
