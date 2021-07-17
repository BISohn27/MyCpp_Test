#include <iostream> //preprocessor
#include <string>
#include "Monster.h"

int main()
{
	Monster mon1{ "Shannen",Position2D{ 0,0 } };

	std::cout << mon1 << std::endl;

	/*while (1)*/
	{
		//event
		mon1.moveTo(Position2D{ 1,1 });

		std::cout << mon1 << std::endl;
	}
}