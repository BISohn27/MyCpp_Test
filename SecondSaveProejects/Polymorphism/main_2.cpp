#include <iostream>
#include <string>
#include<array>

class Animal
{
protected:
	std::string m_name;
	std::string m_speak;

	Animal(std::string name_in, std::string speak_in)
		:m_name{ name_in }, m_speak{ speak_in }{}
	Animal(const Animal &a) = delete;

	Animal &operator=(const Animal &a) = delete;

public:
	std::string getName() const { return m_name; }
	std::string speak() const { return m_speak; }
};

class Dog : public Animal
{
public:
	Dog(std::string name_in) : Animal{ name_in, "Woof" } {}

	std::string getSpeak() const { return "Woof"; }
};

class Cat : public Animal
{
public:
	Cat(std::string name_in) : Animal{name_in, "Meow"}{}

	std::string getSpeak() const { return "Meow"; }
};
int main()
{
    const Cat fred{ "Fred" };
    const Cat misty{ "Misty" };
    const Cat zeke{ "Zeke" };

    const Dog garbo{ "Garbo" };
    const Dog pooky{ "Pooky" };
    const Dog truffle{ "Truffle" };

    // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
    const auto animals{ std::array<const Animal *,6>({ &fred, &garbo, &misty, &pooky, &truffle, &zeke }) };

    // Before C++20, with the array size being explicitly specified
    // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };

    for (const auto animal : animals)
    {
        std::cout << animal->getName() << " says " << animal->speak() << '\n';
    }
	return 0;
}
