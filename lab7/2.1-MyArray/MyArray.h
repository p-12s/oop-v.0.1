#pragma once
#include <new>
#include <algorithm>
#include "MyIterator.h"


template <typename T>
class CMyArray
{
	
	typedef CMyIterator<T> iterator;
	typedef CMyIterator<const T> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;
	 

public:
	/*typedef CMyIterator<T> iterator; // в статье это в публичной части
	typedef CMyIterator<const T> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;*/

	friend iterator;
	friend const_iterator;
	CMyArray() = default;// зачем нужен дефолтный конструктор? спросить у Ильи

	CMyArray(const CMyArray& arr) // конструктор, принимающий константное значение (копирующий)
	{
		const auto size = arr.GetSize();//вернет указатель на начало выделенной "сырой" памяти
		if (size != 0)
		{
			m_begin = RawAlloc(size);
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

	CMyArray(CMyArray && arr) // конструктор, принимающий временное значение (перемещающий)
		: m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
		// TODO удалить предыдущий arr. после ок тестов
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
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

	/*T & GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}*/

	//TODO может заменить одной перегрузкой?
	const T& operator[](size_t index) const // возвр. константную ссылку (нельзя изменить объект)
	{
		if (m_begin + index >= m_end || m_begin + index < m_begin)// если не использовать GetBack() - можно упростить
			throw std::out_of_range("Error! Out of range");

		return *(m_begin + index);
	}

	T& operator[](size_t index) // возвр. константную ссылку ЗАЧЕМ НУЖНО 2 ПЕРЕГРУЗКИ [] ??? спросить
	{
		if (m_begin + index >= m_end || m_begin + index < m_begin)
			throw std::out_of_range("Error! Out of range");

		return *(m_begin + index);
	}

	CMyArray& operator=(CMyArray const& arr)//перегрузка оператора перемещения
	{
		if (std::addressof(arr) != this)//Получает фактический адрес объекта или функции arg, даже в случае перегрузкиoperator&
		{
			CMyArray copy(arr);
			std::swap(m_begin, copy.m_begin);
			std::swap(m_end, copy.m_end);
			std::swap(m_endOfCapacity, copy.m_endOfCapacity);
		}
		return *this;
	}

	CMyArray& operator=(CMyArray && arr)// перегрузка оператора перемещения, используется для временного объекта
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

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}

	/*
	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;
	*/


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

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}
private:
	static void DeleteItems(T *begin, T *end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
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

