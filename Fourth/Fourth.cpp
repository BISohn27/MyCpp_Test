#include <iostream>

class Points
{
private:
	double m_x;
	double m_y;
	double m_z;

public:
	Points(double x = 0.0, double y = 0.0, double z= 0.0)
		:m_x{x},m_y{y},m_z{z}
	{}

	double getX() { return m_x; }
	double getY() { return m_y; }
	double getZ() { return m_z; }

	friend std::ostream& operator<< (std::ostream &out, const Points &point);
	friend std::istream &operator>> (std::istream &in, Points &point);
};

std::ostream& operator<< (std::ostream &out, const Points &point)
{
	out << "Point( " << point.m_x << " , " << point.m_y << 
		" , " << point.m_z << " )"<< std::endl;
	return out;
}

std::istream &operator>> (std::istream &in, Points &point)
{
	in >> point.m_x;
	in >> point.m_y;
	in >> point.m_z;

	return in;
}

int main()
{
	Points point{ 0.0, 3.0, 4.9 };
	Points point2{ 1.1, 3.3, 4.4 };
	Points point3{};

	std::cout << point << point2;

	std::cin >> point3;

	std::cout << point3;
}
