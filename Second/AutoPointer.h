#pragma once
#include <iostream>

template<typename T>
class Auto_ptr
{
private:
	T *m_ptr;

public:
	Auto_ptr(T *ptr = nullptr)
		:m_ptr{ ptr } {}
	
	~Auto_ptr()
	{
		delete m_ptr;
	}

	Auto_ptr(const Auto_ptr &a)
	{
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
	}

	Auto_ptr &operator= (const Auto_ptr &a)
	{
		if (&a == this)
			return *this;

		delete m_ptr;

		m_ptr = new T;
		*m_ptr = *a.m_ptr;

		return *this;
	}

	/*Auto_ptr(Auto_ptr &a)
	{
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
	}

	Auto_ptr &operator=(Auto_ptr &a)
	{
		if (&a == this)
			return *this;

		delete m_ptr;

		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
		
		return *this;
	}*/


	T &operator*() const { return *m_ptr; }
	T* &operator->() const { return m_ptr; }
};