#include <iostream>
#include <string>
#include <functional>

using namespace std;

class Square
{
public:
	int operator()(int n) { return n * n; }
} square;

class MyFunc
{
public:
	int operator()(int n) { return n * (n - 15) / 2; }
} myfunc;

template<typename T>
int arrMin(const int arr[], int n, T&& f)
{
	int min = f(arr[0]);
	for (int i = 1; i < n; i++)
	{
		if (f(arr[i]) < min)
			min = f(arr[i]);
	}

	return min;
}

int main()
{
	int arr[7] = { 1,3,4,5,6,2,10 };

	cout << arrMin(arr, 7, [](int n)->int {return n * n; }) << endl;;
	cout << arrMin(arr, 7, myfunc) << endl;
}
