#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

class Complex
{
private:
	double m_real;
	double m_img;

	double getNumber(const char *str, int from, int to);

public:
	Complex(double r=0.0, double i=0.0): m_real{r}, m_img{i} {}
	Complex(const char *c);

	friend Complex operator+(const Complex &c1, const Complex &c2);
	friend Complex operator-(const Complex &c1, const Complex &c2);
	friend Complex operator*(const Complex &c1, const Complex &c2);
	friend Complex operator/(const Complex &c1, const Complex &c2);

	friend std::ostream &operator<<(std::ostream &out, const Complex &c);

	Complex &operator=(const Complex &c);
	Complex &operator-=(const Complex &c);
	Complex &operator+=(const Complex &c);
	Complex &operator*=(const Complex &c);
	Complex &operator/=(const Complex &c);
	
	Complex &operator++();
	Complex operator++(int x);
	Complex &operator--();
	Complex operator--(int x);
	
};

Complex::Complex(const char *c)
{
	int  char_length = static_cast<int>(strlen(c));
	int  img_index = 0;
	int  operator_index = 0;
	int  real_point_index = 0;
	int  img_point_index = 0;
	bool real_minus_flag = false;
	bool img_minus_flag = false;


	m_real = 0;
	m_img = 0;

	//find imagine figure
	for (int i = 0; i < char_length; ++i)
		if (c[i] == 'i')
		{
			img_index = i;
			break;
		}

	//find operator - or + to seperate real number from img number
	for (int i=0; i<img_index; ++i)
	{
		if (c[i] == '+' || c[i] == '-')           //find operator
		{
			//if (i == 0)							  //check if it is minus operator for real number
			//{
			//	if (c[i] == '-')        
			//		real_minus_flag = true;
			//}

			//else
			if(i != 0)
			{
				operator_index = i;

				if (c[i] == '-')                        //check if it is minus operator for img number
					img_minus_flag = true;

				break;
			}
		}
	}
	
	m_real = getNumber(c, 0, operator_index);
	m_img = getNumber(c, operator_index, img_index);
	/*if(real_minus_flag)
		m_real = -getNumber(c, 1, operator_index);
	
	else
		m_real = getNumber(c, 0, operator_index);

	if(img_minus_flag)
		m_img = -getNumber(c, operator_index + 1, img_index);

	else
		m_img = getNumber(c, operator_index + 1, img_index);
	*/

	/*for (int i=0; i<operator_index; ++i)
		if (c[i] >= 48 && c[i] <= 57)
		{
			m_real += static_cast<double>(c[i] - 48) * pow(operator_index - i - 1, 10);
		}

	for (int i=operator_index+1; i<img_index; ++i)
		if (c[i] >= 48 && c[i] <= 57)
		{
			m_img += static_cast<double>(c[i] - 48) * pow(img_index - i, 10);
		}*/

}

Complex operator+(const Complex &c1, const Complex &c2)
{
	return Complex(c1.m_real + c2.m_real, c1.m_img + c2.m_img);
}

Complex operator-(const Complex &c1, const Complex &c2)
{
	return Complex(c1.m_real - c2.m_real, c1.m_img - c2.m_img);
}

Complex operator*(const Complex &c1, const Complex &c2)
{
	return Complex(c1.m_real * c2.m_real - c1.m_img * c2.m_img, c1.m_real * c2.m_img + c1.m_img * c2.m_real);
}

Complex operator/(const Complex &c1, const Complex &c2)
{
	return Complex(
		(c1.m_real * c2.m_real + c1.m_img * c2.m_img) / (c2.m_real * c2.m_real + c2.m_img * c2.m_img),
		(c1.m_img * c2.m_real - c1.m_real * c2.m_img) / (c2.m_real * c2.m_real + c2.m_img * c2.m_img));
}

std::ostream &operator<<(std::ostream &out, const Complex &c)
{
	out << c.m_real << std::showpos << c.m_img << "i" << std::endl;

	std::cout.unsetf(std::ios::showpos);

	return out;
}

Complex &Complex::operator=(const Complex &c)
{
	m_real = c.m_real;
	m_img = c.m_img;

	return *this;
}

Complex &Complex::operator+=(const Complex &c)
{
	(*this) = (*this) + c;

	return *this;
}

Complex &Complex::operator-=(const Complex &c)
{
	(*this) = (*this) - c;

	return *this;
}

Complex &Complex::operator*=(const Complex &c)
{
	(*this) = (*this) * c;

	return *this;
}
Complex &Complex::operator/=(const Complex &c)
{
	(*this) = (*this) / c;

	return *this;
}

Complex &Complex::operator++()
{
	m_real++;
	m_img++;

	return *this;
}

Complex Complex::operator++(int x)
{
	Complex temp(*this);

	m_real++;
	m_img++;

	return temp;
}

Complex &Complex::operator--()
{
	m_real--;
	m_img--;

	return *this;
}

Complex Complex::operator--(int x)
{
	Complex temp(*this);

	m_real--;
	m_img--;

	return temp;
}

double Complex::getNumber(const char *str, int from, int to)
{
	double result = 0;
	double decimal = 1.0;
	int point_index = 0;
	bool minus_flag = false;

	if (str[from] == '-') minus_flag = true;
	if (str[from] == '-' || str[from] == '+') from++;

	for (int i = from; i < to; ++i)
		if (str[i] == '.')
		{
			point_index = i;
			break;
		}
	
	if(point_index)
	{
		for (int i = from; i < point_index; ++i)
		{
			if (isdigit(str[i]))
			{
				result *= 10;
				result += str[i] - 48;
				//result += (str[i] - 48) * pow(10, point_index - i - 1);
			}
		}

		for (int i = point_index + 1; i < to; ++i)
		{
			if (isdigit(str[i]))
			{
				decimal /= 10;
				result += (str[i] - 48) * decimal;
				//result += (str[i]-48) * pow(10, -(i - point_index));
			}
				
		}
	}

	else
		for (int i = from; i < point_index; ++i)
		{
			if (isdigit(str[i]))
			{
				result *= 10;
				result += str[i] - 48;
				//result += (str[i] - 48) * pow(10, point_index - i - 1);
			}
		}

	if (minus_flag)
		result *= -1.0;
	
	return result;
}

int main() 
{
	std::cout << Complex{ "-2.3-3.3i" };
}
