#pragma once

/*
первый параметр шаблона — тип итератора, так как собираемся использовать со стандартной библиотекой,
то тип выбирается из следующих типов: input_iterator_tag, output_iterator_tag, forward_iterator_tag,
bidirectional_iterator_tag, random_access_iterator_tag.
Второй параметр тип значения которое хранится и возвращается операторами * и ->,
теретий параметр — тип который может описывать растояние между итераторами,
четвртый шаблонный параметр — тип указателя на значение, пятый — тип ссылки на значения.
Обязательными являются первые два параметра.
*/
// std::bidirectional_iterator_tag - чтобы выбирались наиболее эффективные алгоритмы для работы с двунаправленным итератором
template<typename T>
class CMyIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
	
public:
	CMyIterator(); // TODO нужен ли ? в статье его нет https://habr.com/post/265491/
	CMyIterator(const CMyIterator &it); // & сместить

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
	T& operator[](size_t index) const;//вместо size_t был ptrdiff_t
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
Константный итератор. Последний итератор, который мы рассмотрим, - константный (constant iterator).
Он образуется путем модификации основного итератора. Константный итератор не допускает изменения данных, 
на которые он ссылается. Можно считать константный итератор указателем на константу. 
Чтобы получить константный итератор, можно воспользоваться типом const_iterator, 
предопределенным в различных контейнерах. К примеру, так можно описать переменную типа константный итератор на список:
list<int>::const_iterator c_itr;
 */



/*
Самый просто итератор — это InputIterator (input_iterator_tag), он должен поддерживать префиксную форму инкремента, 
оператор !=, оператор* и оператор -> . 
Помимо этого понадобится конструктор и конструктор копирования. 
В примере не предполагается создание итератора кроме, как методами begin и end класса контейнера,
поэтому конструктор итератора будет приватным, а класс контейнера объявлен как дружественный. 
И добавим оператор ==, во-первых хорошая практика добавлять поддержку != и == вместе, 
а во-вторых без этого не будет работать BOOST_FOREACH.
 */