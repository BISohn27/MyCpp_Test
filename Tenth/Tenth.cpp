#include <iostream>

class Vector2
{
private:
	double x;
	double y;

public:
	Vector2(double x_in=0, double y_in=0)
		:x{ x_in }, y{ y_in } {}

	friend std::ostream &operator<<(std::ostream &out, const Vector2 &v);

	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}

	Vector2 &operator+=(Vector2 const &v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	template <typename T>
	Vector2 &operator=(T t)
	{
		x = t;
		y = t;

		return *this;
	}

};

std::ostream &operator<< (std::ostream &out, const Vector2 &v)
{
	out << v.x << " " << v.y;

	return out;
}

template <typename T>
T sumArray(T arr[], int n)
{
	T sum = T();
	for (int i = 0; i < n; i++)
		sum += arr[i];

	return sum;
}

int main()
{
	Vector2 arr[3] = { {1,2},{1.2,3},{3.3,4.4} };
	
	std::cout << sumArray<Vector2>(arr, 3) << std::endl;
}
