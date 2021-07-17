#include <iostream>
#include <cassert>
#include <initializer_list>

class IntArray
{
private:
	int m_length = 0;
	int *m_data = nullptr;

public:
	IntArray(int length=0)
		:m_length{ length }
	{
		if(length>0)
			m_data = new int[length];
	}

	IntArray(const std::initializer_list<int> &list)
		:IntArray(static_cast<int>(list.size()))
	{
		int count{ 0 };
		for (auto &element : list)
		{
			m_data[count] = element;
			++count;
		}
	}

	~IntArray() { delete[] m_data; }

	IntArray &operator=(const IntArray &arr)
	{
		if (this == &arr)return *this;

		delete[] this->m_data;
		this->m_length = arr.m_length;

		if (arr.m_data != nullptr)
		{
			this->m_data = new int[this->m_length];

			for (int i = 0; i < arr.m_length; i++)
				this->m_data[i] = arr.m_data[i];
		}

		else
			m_data = nullptr;

		return *this;
	}

	IntArray & operator= (std::initializer_list<int>& list)
	{
		int length{ static_cast<int>(list.size()) };

		if (length != m_length)
		{
			delete[] m_data;
			m_length = length;
			m_data = new int[length] {};
		}

		int count{0};

		for (auto &element : list)
		{
			m_data[count] = element;
			count++;
		}

		return *this;
	}

	void erase()
	{
		delete[] m_data;

		m_data = nullptr;
		m_length = 0;
	}

	int &operator[](int index)
	{
		assert(index >= 0 && index < m_length);

		return m_data[index];
	}

	int size() const { return m_length; }

	void reallocate(int newLength)
	{
		erase();

		if (newLength <= 0)
			return;

		m_length = newLength;
		m_data = new int[newLength];
	}

	void resize(int newLength)
	{
		if (newLength == m_length)
			return;

		else if (newLength <= 0)
		{
			erase();
			return;
		}
		
		int *data = new int[newLength];

		if (m_length > 0)
		{
			int elementsTocopy{ (newLength > m_length) ? m_length : newLength };

			for (int i = 0; i < elementsTocopy; i++)
				data[i] = m_data[i];
		}

		delete[] m_data;

		m_data = data;
		m_length = newLength;
	}

	void insertBefore(int value, int index)
	{
		if (index >= 0 && index <= m_length)
		{

			int *data = new int[m_length+1];

			for (int i = 0; i < index; i++)
				data[i] = m_data[i];

			data[index] = value;

			for (int i = index; i < m_length; i++)
				data[i + 1] = m_data[i];
				
			delete[] m_data;

			m_data = data;
			m_length++;
		}

		else
		{
			std::cout << "The index " << index << " isn't a valid number." << std::endl;
			return;
		}
			
	}

	void remove(int index)
	{

		if (m_length == 1)
		{
			erase();
			return;
		}

		else if (index >= 0 && index < m_length)
		{
			int *data = new int[m_length-1];

			for (int i = 0; i < index; i++)
				data[i] = m_data[i];

			for (int i = index+1; i < m_length; i++)
				data[i-1] = m_data[i];

			delete[] m_data;

			m_data = data;

			m_length--;
		}

		else
		{
			std::cout << "The index " << index << " isn't a valid number." << std::endl;
		}
	}

	void insertAtBeginning(int value) { insertBefore(value, 0); }

	void push_back(int value) { insertBefore(value, m_length); }

	friend std::ostream &operator<< (std::ostream &out, IntArray &arr)
	{
		for (int i = 0; i < arr.m_length; i++)
			out << arr.m_data[i] << " ";
		out << std::endl;

		return out;
	}
};

int main()
{
	IntArray arr{ 1,2,3,4 };

	IntArray arr1;

	arr1 = arr;

	std::cout << arr1;


	return 0;
}