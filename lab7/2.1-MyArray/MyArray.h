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

	/* лучше перенести отсюда или нет?
	 * 
	typedef CMyIterator<T> iterator;
	typedef CMyIterator<const T> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;
	*/

public:
	//friend iterator;
	//friend const_iterator;
	CMyArray() = default; // зачем нужен дефолтный конструктор? спросить у Ильи
	
	CMyArray(const CMyArray& arr)//копирующий конструктор
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);//вернет указатель на начало выделенной "сырой" памяти
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

	CMyArray(CMyArray&& arr)//создает объект с уничтожением исходного - перемещающий конструктор
		: m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	/*Конструктор и оператор перемещения используются компилятором в разных ситуациях:
	конструктор перемещения применяется в местах, где объявление совпадает с определением (инициализацией) rvalue-ссылкой 
	на экземпляр этого же класса, либо посредством direct initialization в конструкторе класса/структуры
	(если же определение произойдет с помощью lvalue-ссылки, то вызовется конструктор копирования)
	оператор перемещения применяется в местах, где экземпляр класса уже был ранее определен и к нему применяется operator =, 
	который в качестве аргумента приминает rvalue-ссылку на экземпляр этого же класса (если же оператор принимает lvalue-ссылку , 
	то вызовется оператор присваивания)*/
	/*
	В C++11 каждый класс, помимо конструктора по умолчанию, имеет следующие 5 дефолтных операций: 
	Конструктор копирования (copy constructor)
	Оператор присваивания (copy assignment)
	Конструктор перемещения (move constructor)
	Оператор перемещения (move assignment)
	Деструктор (destructor)
	При определении одной из этих 5-ти операций рекомендуется явно указать (либо определить, либо объявить с помощью default или delete) все остальные, 
	т.к. все эти 5 операций тесно связаны. Это будет способствовать лучшему пониманию семантики класса при чтении кода. 
	Если явно определена одна из упомянутых 5-ти операций (в том числе с использованием default или delete), то: 
	недостающие операции копирования будут определены автоматически с поведением по умолчанию
	недостающие операции перемещения определены не будут.
	Это следует учитывать при написании классов.
	 */

 	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = GetCapacity() > 0 ? GetCapacity() * 2 : size_t(1);

			auto newBegin = RawAlloc(newCapacity);// получим ссылку на новый блок памяти
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);// копируем элементы в новое место (если они есть)
				// Конструируем копию value в конце нового блока
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

	void Resize(size_t size)
	{
		if (size != GetSize())
		{
			CMyArray copy; // создадим копию
			size_t min = std::min(size, GetSize());// что за н?

			//TODO можно уменьшить накладные расходы на создание нового объекта, 
			// если массив ресайзится в меньшую сторону. тогда просто обрубаем конец
			
			copy.m_begin = copy.RawAlloc(size); // присвоим начало выделенной памяти нашему началу копии
			copy.m_end = copy.m_begin; // присвоим начало концу
			copy.m_endOfCapacity = copy.m_begin + size;// размер капасити будет целевым

			copy.CopyItems(m_begin, m_begin + min, copy.m_begin, copy.m_end);

			// если в большую сторону - довставим пустые элементы в конец
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
	//TODO может заменить одной перегрузкой?
	const T& operator[](size_t index) const // возвр. константную ссылку (нельзя изменить объект)
	{
		if (m_begin + index >= m_end || m_begin + index < m_begin)// если не использовать GetBack() - можно упростить
			throw std::out_of_range("Error! Out of range");

		return *(m_begin + index);
	}

	T& operator[](size_t index) // возвр. константную ссылку ЗАЧЕМ НУЖНО 2 ПЕРЕГРУЗКИ [] ??? спросить
	{
		if (m_begin + index >= m_end || m_begin + index < m_begin)// если не использовать GetBack() - можно упростить
			throw std::out_of_range("Error! Out of range");

		return *(m_begin + index);
	}



	//TODO зачем нужны 2 версии, удаляющая исходный массив, и не удаляющая?
	CMyArray& operator=(CMyArray const& arr)//перегрузка оператора перемещения (arr не изменится)
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
	// а если присваивать разноразмерные массивы?
	CMyArray& operator=(CMyArray && arr)// перегрузка оператора перемещения (arr обнулится)
	{
		if (&arr != this)
		{
			//Clear();
			DeleteItems(m_begin, m_end); // а если после удаления возникла проблема? мб не удалять, а перекинуть в темп?
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
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}
	
	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T *const dstBegin, T *&dstEnd)// и снова, зачем тут статик
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)//
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			// Построить «T» на «dstEnd» как копию «* begin»
			new (dstEnd)T(*srcBegin); //TODO похоже тут конструктор копирования, и источник не уничтожается.  можно ли проще скопировать?
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from) // почему освобождаем от начала к концу?
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}
	

	/*
	Статический метод может работать со статическими переменными класса и с объектами класса. 
	Он может выполнять какие-то действия общие для всех объектов данного класса или для указываемой группы объектов, 
	изменение общих параметров, что-то вроде сборки мусора и т.д.

	Переменные внутри метода не обязательно будут static.
	Создание и уничтожение экземпляров класса никак не затронет статический метод, его можно вызывать независимо от существования объектов класса. 
	Это аналог обычной функции, только имя у неё необычное и область видимости.
	Существование статического метода никак не отражается на том, как будет храниться объект класса.
	 */
	static T *RawAlloc(size_t n)//выделить память
	{
		size_t memSize = n * sizeof(T);//нужный размер
		T *p = static_cast<T*>(malloc(memSize));// malloc выделяет блок памяти, размером sizemem байт, и возвращает указатель на начало блока
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
 // Объявляем массив размера 5 и инициализируем.
int marks[5] = { 19, 10, 8, 17, 9 };

// Объявляем массив без указания размера,
//  размер будет определён из списка инициализациии.
int marks[] = { 19, 10, 8, 17, 9 };

// Объявляем массив размера 10 и заполняем нулями.
int ages[10] = { 0 };
 */
/*
 Новая область находится уже другом месте, потому что менеджер динамической памяти не мог просто взять и расширить старую область
(ведь сразу за ней находилась чужая память). 
Поэтому все итераторы, ссылки и указатели на элементы могут стать некорректными после любого изменения массива!
 */