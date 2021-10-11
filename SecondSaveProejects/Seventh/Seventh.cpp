#include <iostream>
#include <cstring>

class String
{
private:
	char *m_str;
	int   m_len;

public:
	friend std::ostream &operator<< (std::ostream &out, const String &s);

	String(char c, int n);
	String(const char *s);
	String(const String &s);
	~String();

	void addString(const String &s);
	void copyString(const String &s);
	int strlen();
};

int main()
{
	String a{ "Hello" };
	String b{"Hell"};

	a.copyString(b);

	std::cout << a;

	return 0;
}

std::ostream &operator<<(std::ostream &out, const String &s)
{
	out << s.m_str << std::endl;

	return out;
}

String::String(char c, int n)
{
	m_len = n + 1;
	m_str = new char[m_len];

	for (int i = 0; i < n; i++)
		m_str[i] = c;

	m_str[m_len - 1] = '\n';
}

String::String(const char *s)
{
	m_len = static_cast<int>(std::strlen(s))+1;
	m_str = new char[m_len];

	for (int i = 0; i < m_len-1; i++)
		m_str[i] = s[i];

	m_str[m_len-1] ='\0';
}

String::String(const String &s)
{
	m_len = s.m_len;
	m_str = new char[m_len];

	for (int i = 0; i < m_len; i++)
		m_str[i] = s.m_str[i];
}

String::~String()
{
	delete[] m_str;
	m_len = 0;
}

void String::addString(const String &s)
{
	char *temp = m_str;
	int len_temp = m_len;

	m_len = m_len - 1 + s.m_len;
	m_str = new char[m_len];

	for (int i = 0; i < len_temp -1; i++)
		m_str[i] = temp[i];
	

	for (int i = len_temp - 1; i < m_len; i++)
	{
		m_str[i] = s.m_str[i - len_temp + 1];
	}

	delete[] temp;
}

void String::copyString(const String &s)
{
	delete[] m_str;

	m_len = s.m_len;
	m_str = new char[m_len];

	for (int i = 0; i < m_len; i++)
		m_str[i] = s.m_str[i];
}

int String::strlen() { return m_len; }