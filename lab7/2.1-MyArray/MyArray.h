#pragma once
#include "stdafx.h"
#include "MyIterator.h"

template <typename T>
class CMyArray
{
private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;

	/* ����� ��������� ������ ��� ���?
	 * 
	typedef CMyIterator<T> iterator;
	typedef CMyIterator<const T> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;
	*/

public:
	//friend iterator;
	//friend const_iterator;
	CMyArray() = default; // ����� ����� ��������� �����������? �������� � ����
	
	CMyArray(const CMyArray& arr)//���������� �����������
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);//������ ��������� �� ������ ���������� "�����" ������
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_begin + arr.GetCapacity();
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	CMyArray(CMyArray&& arr)//������� ������ � ������������ ��������� - ������������ �����������
		: m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	/*����������� � �������� ����������� ������������ ������������ � ������ ���������:
	����������� ����������� ����������� � ������, ��� ���������� ��������� � ������������ (��������������) rvalue-������� 
	�� ��������� ����� �� ������, ���� ����������� direct initialization � ������������ ������/���������
	(���� �� ����������� ���������� � ������� lvalue-������, �� ��������� ����������� �����������)
	�������� ����������� ����������� � ������, ��� ��������� ������ ��� ��� ����� ��������� � � ���� ����������� operator =, 
	������� � �������� ��������� ��������� rvalue-������ �� ��������� ����� �� ������ (���� �� �������� ��������� lvalue-������ , 
	�� ��������� �������� ������������)*/
	/*
	� C++11 ������ �����, ������ ������������ �� ���������, ����� ��������� 5 ��������� ��������: 
	����������� ����������� (copy constructor)
	�������� ������������ (copy assignment)
	����������� ����������� (move constructor)
	�������� ����������� (move assignment)
	���������� (destructor)
	��� ����������� ����� �� ���� 5-�� �������� ������������� ���� ������� (���� ����������, ���� �������� � ������� default ��� delete) ��� ���������, 
	�.�. ��� ��� 5 �������� ����� �������. ��� ����� �������������� ������� ��������� ��������� ������ ��� ������ ����. 
	���� ���� ���������� ���� �� ���������� 5-�� �������� (� ��� ����� � �������������� default ��� delete), ��: 
	����������� �������� ����������� ����� ���������� ������������� � ���������� �� ���������
	����������� �������� ����������� ���������� �� �����.
	��� ������� ��������� ��� ��������� �������.
	 */

 	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = GetCapacity() > 0 ? GetCapacity() * 2 : size_t(1);

			auto newBegin = RawAlloc(newCapacity);// ������� ������ �� ����� ���� ������
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);// �������� �������� � ����� ����� (���� ��� ����)
				// ������������ ����� value � ����� ������ �����
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// ������������� �� ������������� ������ ��������� ���������
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	void Resize(size_t size)
	{
		if (size != GetSize())
		{
			CMyArray copy; // �������� �����
			size_t min = std::min(size, GetSize());// ��� �� �?

			//TODO ����� ��������� ��������� ������� �� �������� ������ �������, 
			// ���� ������ ���������� � ������� �������. ����� ������ �������� �����
			
			copy.m_begin = copy.RawAlloc(size); // �������� ������ ���������� ������ ������ ������ �����
			copy.m_end = copy.m_begin; // �������� ������ �����
			copy.m_endOfCapacity = copy.m_begin + size;// ������ �������� ����� �������

			copy.CopyItems(m_begin, m_begin + min, copy.m_begin, copy.m_end);

			// ���� � ������� ������� - ��������� ������ �������� � �����
			for (size_t i = min; i < size ; ++i)
			{
				copy.Append(T());
			}
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
	/*
	T & GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}
	*/
	//TODO ����� �������� ����� �����������?
	const T& operator[](size_t index) const // �����. ����������� ������ (������ �������� ������)
	{
		if (m_begin + index >= m_end || m_begin + index < m_begin)// ���� �� ������������ GetBack() - ����� ���������
			throw std::out_of_range("Error! Out of range");

		return *(m_begin + index);
	}

	T& operator[](size_t index) // �����. ����������� ������ ����� ����� 2 ���������� [] ??? ��������
	{
		if (m_begin + index >= m_end || m_begin + index < m_begin)// ���� �� ������������ GetBack() - ����� ���������
			throw std::out_of_range("Error! Out of range");

		return *(m_begin + index);
	}



	//TODO ����� ����� 2 ������, ��������� �������� ������, � �� ���������?
	CMyArray& operator=(CMyArray const& arr)//���������� ��������� ����������� (arr �� ���������)
	{
		if (std::addressof(arr) != this)
		{
			CMyArray copyArr(arr);
			std::swap(m_begin, copyArr.m_begin);
			std::swap(m_end, copyArr.m_end);
			std::swap(m_endOfCapacity, copyArr.m_endOfCapacity);
		}
		return *this;
	}
	// � ���� ����������� �������������� �������?
	CMyArray& operator=(CMyArray && arr)// ���������� ��������� ����������� (arr ���������)
	{
		if (&arr != this)
		{
			//Clear();
			DeleteItems(m_begin, m_end); // � ���� ����� �������� �������� ��������? �� �� �������, � ���������� � ����?
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
	/*
	iterator begin()
	{
		return iterator(m_begin);
	}

	iterator end()
	{
		return iterator(m_end);
	}

	const_iterator begin() const
	{
#if _DEBUG
		return const_iterator(m_begin, this);
#endif
		return const_iterator(m_begin);
	}

	const_iterator end() const
	{
		return const_iterator(m_end);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(m_end);
	}
	reverse_iterator rend()
	{
		return reverse_iterator(m_begin);
	}

	reverse_const_iterator rbegin() const
	{
		return reverse_const_iterator(m_end);
	}
	reverse_const_iterator rend() const
	{
		return reverse_const_iterator(m_begin);
	}
	*/
	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}
private:
	static void DeleteItems(T *begin, T *end)
	{
		// ��������� ������ ��������
		DestroyItems(begin, end);
		// ����������� ������� ������ ��� �� ��������
		RawDealloc(begin);
	}
	
	// �������� �������� �� �������� ������� � to, ���������� newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T *const dstBegin, T *&dstEnd)// � �����, ����� ��� ������
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)//
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			// ��������� �T� �� �dstEnd� ��� ����� �* begin�
			new (dstEnd)T(*srcBegin); //TODO ������ ��� ����������� �����������, � �������� �� ������������.  ����� �� ����� �����������?
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// dst - ����� ������, ��� ��������������� �������� ���� ��������� ����������
		// to - ������ ������������������ ������
		while (to != from) // ������ ����������� �� ������ � �����?
		{
			--to;
			// ���� �������� ���������� ��� ���������� ���� T
			to->~T();
		}
	}
	

	/*
	����������� ����� ����� �������� �� ������������ ����������� ������ � � ��������� ������. 
	�� ����� ��������� �����-�� �������� ����� ��� ���� �������� ������� ������ ��� ��� ����������� ������ ��������, 
	��������� ����� ����������, ���-�� ����� ������ ������ � �.�.

	���������� ������ ������ �� ����������� ����� static.
	�������� � ����������� ����������� ������ ����� �� �������� ����������� �����, ��� ����� �������� ���������� �� ������������� �������� ������. 
	��� ������ ������� �������, ������ ��� � �� ��������� � ������� ���������.
	������������� ������������ ������ ����� �� ���������� �� ���, ��� ����� ��������� ������ ������.
	 */
	static T *RawAlloc(size_t n)//�������� ������
	{
		size_t memSize = n * sizeof(T);//������ ������
		T *p = static_cast<T*>(malloc(memSize));// malloc �������� ���� ������, �������� sizemem ����, � ���������� ��������� �� ������ �����
		// Instantiate CMyArray < string >: The 'malloc' function is used to allocate 
		// memory for an array of objects which are classes containing constructors and destructors.
		// char * buffer = (char*) malloc(len + 1); 
		if (!p)
			throw std::bad_alloc();
		return p;
	}
	
	static void RawDealloc(T *p)
	{
		free(p);
	}
};

/*
 // ��������� ������ ������� 5 � ��������������.
int marks[5] = { 19, 10, 8, 17, 9 };

// ��������� ������ ��� �������� �������,
//  ������ ����� �������� �� ������ ��������������.
int marks[] = { 19, 10, 8, 17, 9 };

// ��������� ������ ������� 10 � ��������� ������.
int ages[10] = { 0 };
 */
/*
 ����� ������� ��������� ��� ������ �����, ������ ��� �������� ������������ ������ �� ��� ������ ����� � ��������� ������ �������
(���� ����� �� ��� ���������� ����� ������). 
������� ��� ���������, ������ � ��������� �� �������� ����� ����� ������������� ����� ������ ��������� �������!
 */