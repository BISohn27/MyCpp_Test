#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ofstream ost{ "Sample.dat" };

	if (!ost)
	{
		std::cerr << "Uh oh, Sample.dat could not be opened for writing!\n";
		return 1;
	}

	ost << "This is line 3" << '\n';
	ost << "This in line 4" << '\n';
	ost << "This is line 1" << '\n';
	ost << "this is line 2" << '\n';

	return 0;
}
