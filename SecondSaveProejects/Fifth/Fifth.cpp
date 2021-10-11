#include <iostream>
#include <cstring>

class Mystring
{
private:
	char *m_str;
	int   m_len;
	int	  m_capacity;

public:
	Mystring(char c, int num=1)
	{
		m_len = num;
		m_capacity = num;
		m_str = new char[m_len];

		for (int i = 0; i < m_len; i++)
			m_str[i] = c;
	}

	Mystring(const char *s)
	{
		m_len = static_cast<int>(strlen(s));
		m_capacity = static_cast<int>(strlen(s));

		m_str = new char[m_len];

		for (int i = 0; i < m_len; i++)
			m_str[i] = s[i];
	}

	Mystring(const Mystring &s)
	{
		m_len = s.m_len;
		m_capacity = s.m_len;

		m_str = new char[m_len];

		for (int i = 0; i < m_len; i++)
			m_str[i] = s.m_str[i];
	}

	~Mystring()
	{
		delete[] m_str;
	}

	friend std::ostream &operator<<(std::ostream &out, const Mystring &s);
	Mystring &operator=(const char *s);
	Mystring &operator=(const Mystring &s);
	char operator[](int index) const;
	int getStrlength() const { return m_len; }
	bool strcompare(const Mystring &s) const;
	void add(const Mystring &s);
	int getLength(char *&s);
	int compare(const Mystring &s) const;
	int find(const char *s) const;
	void reserve(int size);
	Mystring &erase(int index, int num);
	Mystring &insert(int index, const Mystring &s);
	Mystring &insert(int index, const char *s);
	Mystring &insert(int index, const char c);
};
int main()
{
	Mystring a{ "eiiieHeloooHell" };

	std::cout << a.find("Hello");
}

std::ostream& operator<<(std::ostream &out, const Mystring &s)
{
	for (int i = 0; i < s.m_len; i++)
		out << s.m_str[i];

	out << std::endl;

	return out;
}
Mystring& Mystring::operator=(const char *s)
{
	if (m_capacity < strlen(s))
	{
		delete[] m_str;

		m_len = static_cast<int>(strlen(s));
		m_capacity = static_cast<int>(strlen(s));
		m_str = new char[m_len];
	}

	else
		m_len = static_cast<int>(strlen(s));


	for (int i = 0; i < m_len; i++)
		m_str[i] = s[i];

	return *this;
}

char Mystring::operator[](int index) const
{
	if (index < 0 || index >= m_len)
	{
		std::cout << "Invalid index." << std::endl;
		return NULL;
	}

	return m_str[index];
}

Mystring &Mystring::operator=(const Mystring &s)
{
	if (strcompare(s))
		return *this;

	if (m_capacity < s.m_len)
	{
		delete[] m_str;

		m_len = s.m_len;
		m_capacity = s.m_len;

		m_str = new char[m_len];
	}

	else
		m_len = s.m_len;

	for (int i = 0; i < m_len; i++)
		m_str[i] = s.m_str[i];

	return *this;
}

int Mystring::getLength(char *&s)
{
	int length = 0;

	while (s[length] != '\0')
		length++;

	return length - 1;
}

void Mystring::add(const Mystring &s)
{
	char *temp = m_str;

	if (m_capacity < m_len + s.m_len)
	{
		m_len = m_len + s.m_len;
		m_capacity = m_len;

		m_str = new char[m_len];
	}

	else
		m_len = m_len + s.m_len;

	for (int i = 0; i < m_len - s.m_len; i++)
		m_str[i] = temp[i];

	for (int j = m_len - s.m_len; j < m_len; j++)
		m_str[j] = s.m_str[j - m_len + s.m_len];

	delete[] temp;
}

int Mystring::compare(const Mystring &s) const
{
	int min_length = (m_len < s.m_len) ? m_len : s.m_len;

	for (int i = 0; i < min_length; i++)
	{
		if (m_str[i] < s.m_str[i])
			return 1;
		else
			return -1;
	}

	if (s.m_len == m_len)
		return 0;

	else if (min_length == m_len)
		return 1;

	else
		return -1;
}

int Mystring::find(const char *s) const
{
	int  length = static_cast<int>(strlen(s));
	bool match_flag = false;

	if (m_len == 0)
		return -1;

	for (int i = 0; i < m_len; i++)
	{
		if (m_str[i] == s[0])
		{
			for (int j = i + 1; j < i + length; j++)
			{
				if (m_str[j] != s[j - i])
				{
					match_flag = false;
					break;
				}

				match_flag = true;
			}

			if (match_flag == true)
				return i;
		}
	}

	return -1;
}

bool Mystring::strcompare(const Mystring &s) const
{
	if (m_len != s.m_len)
		return false;

	for (int i = 0; i < m_len; i++)
	{
		if (m_str[i] != s.m_str[i])
			return false;
	}

	return true;
}

Mystring &Mystring::erase(int index, int num)
{
	if (index + num > m_len - 1 || index <0 || index > m_len)
	{
		std::cout << "Invalid index and number." << std::endl;
		return *this;
	}

	for (int i = index + num; i < m_len; i++)
		m_str[i - num] = m_str[i];

	m_len -= - num;

	return *this;
}

void Mystring::reserve(int size)
{
	if (m_capacity >= size)
		return;

	char *temp = m_str;

	m_str = new char[size];
	m_capacity = size;

	for (int i = 0; i < m_len; i++)
		m_str[i] = temp[i];

	delete[] temp;
}
Mystring &Mystring::insert(int index, const Mystring &s)
{
	if (index > m_len || index < 0)
	{
		std::cout << "Invalid index." << std::endl;
		return *this;
	}

	int total_str_len = m_len + s.m_len;
	char *temp = m_str;

	if (m_capacity < total_str_len)
	{
		m_str = new char[total_str_len];
		m_capacity = total_str_len;
	}

	for (int i = 0; i < index; i++)
		m_str[i] = temp[i];

	for (int i = index; i < s.m_len; i++)
		m_str[i] = s.m_str[i - index];

	for (int i = index + s.m_len; i < total_str_len; i++)
		m_str[i] = temp[i - s.m_len];

	m_len = total_str_len;

	delete[] temp;

	return *this;
}

Mystring &Mystring::insert(int index, const char *s)
{
	if (index > m_len || index <0)
	{
		std::cout << "Invalid index." << std::endl;
		return *this;
	}

	int total_str_len = m_len + static_cast<int>(strlen(s));
	char *temp = m_str;

	if (m_capacity < total_str_len)
	{
		m_str = new char[total_str_len];
		m_capacity = total_str_len;
	}

	for (int i = 0; i < index; i++)
		m_str[i] = temp[i];

	for (int i = index; i < static_cast<int>(strlen(s)); i++)
		m_str[i] = s[i - index];

	for (int i = index + static_cast<int>(strlen(s)); i < total_str_len; i++)
		m_str[i] = temp[i - static_cast<int>(strlen(s))];

	m_len = total_str_len;

	delete[] temp;

	return *this;
}

Mystring &Mystring::insert(int index, const char c)
{
	if (index > m_len || index < 0)
	{
		std::cout << "Invalid index." << std::endl;
		return *this;
	}

	int total_str_len = m_len + 1;
	char *temp = m_str;

	if (m_capacity < total_str_len)
	{
		m_str = new char[total_str_len];
		m_capacity = total_str_len;
	}

	for (int i = 0; i < index; i++)
		m_str[i] = temp[i];
	
	m_str[index] = c;

	for (int i = index + 1; i < total_str_len; i++)
		m_str[i] = temp[i - 1];

	m_len = total_str_len;

	delete[] temp;

	return *this;
}