#pragma once

/*
������ �������� ������� � ��� ���������, ��� ��� ���������� ������������ �� ����������� �����������,
�� ��� ���������� �� ��������� �����: input_iterator_tag, output_iterator_tag, forward_iterator_tag,
bidirectional_iterator_tag, random_access_iterator_tag.
������ �������� ��� �������� ������� �������� � ������������ ����������� * � ->,
������� �������� � ��� ������� ����� ��������� ��������� ����� �����������,
�������� ��������� �������� � ��� ��������� �� ��������, ����� � ��� ������ �� ��������.
������������� �������� ������ ��� ���������.
*/
// std::bidirectional_iterator_tag - ����� ���������� �������� ����������� ��������� ��� ������ � ��������������� ����������
template<typename T>
class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
	
public:
	CMyIterator(); // TODO ����� �� ? � ������ ��� ��� https://habr.com/post/265491/
	CMyIterator(const CMyIterator &it); // & ��������

	/*
	#if _DEBUG
	CMyIterator(T* p, CMyArray<T> *array)
		: m_pointer(p)
		, m_array(array)
	{

	}
	#endif
	 */
	CMyIterator& operator=(const CMyIterator &it);
	bool operator!=(CMyIterator const& other) const;
	bool operator==(CMyIterator const& other) const; // need for BOOST_FOREACH
	T* operator->() const;
	T& operator[](size_t index) const;//������ size_t ��� ptrdiff_t
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
	size_t const operator-(CMyIterator const& other) const;

private:
	template<typename> friend class CMyArray;
	CMyIterator(T* p);
	/*
	#if _DEBUG
		CMyArray<T> * m_array;
	#endif
	 */
	T* m_pointer;
};

template<typename T>
CMyIterator<T>::CMyIterator(T *p) 
	: m_pointer(p)
{
}

template<typename T>
CMyIterator<T>::CMyIterator()
	: m_pointer(nullptr)
{
}

template<typename T>
CMyIterator<T>::CMyIterator(const CMyIterator& it) :
	m_pointer(it.m_pointer)
{
}

/*
����������� ��������. ��������� ��������, ������� �� ����������, - ����������� (constant iterator).
�� ���������� ����� ����������� ��������� ���������. ����������� �������� �� ��������� ��������� ������, 
�� ������� �� ���������. ����� ������� ����������� �������� ���������� �� ���������. 
����� �������� ����������� ��������, ����� ��������������� ����� const_iterator, 
���������������� � ��������� �����������. � �������, ��� ����� ������� ���������� ���� ����������� �������� �� ������:
list<int>::const_iterator c_itr;
 */



/*
����� ������ �������� � ��� InputIterator (input_iterator_tag), �� ������ ������������ ���������� ����� ����������, 
�������� !=, ��������* � �������� -> . 
������ ����� ����������� ����������� � ����������� �����������. 
� ������� �� �������������� �������� ��������� �����, ��� �������� begin � end ������ ����������,
������� ����������� ��������� ����� ���������, � ����� ���������� �������� ��� �������������. 
� ������� �������� ==, ��-������ ������� �������� ��������� ��������� != � == ������, 
� ��-������ ��� ����� �� ����� �������� BOOST_FOREACH.
 */