#include <iostream>
#include <string>

//association unidirectional relationship
class Car
{
private:
	std::string m_name;
	int m_id;

public:
	Car(const std::string &name, int id)
		:m_name{ name }, m_id{ id }{}

	const std::string &getName() const { return m_name; };
	int getId() const { return m_id; }
	
};

class Carlot
{
private:
	static Car s_carlot[4];

public:
	Carlot() = delete;

	static Car *getCar(int id)
	{
		for (int i = 0; i < 4; i++)
		{
			if (s_carlot[i].getId() == id)
				return &(s_carlot[i]);
		}

		return nullptr;
	}
};

Car Carlot::s_carlot[4]{ {"Prius", 17},{"Accord", 50},{"Boxter", 18}, {"Sonata", 90} };

class Driver
{
private:
	std::string m_name;
	int m_id;

public:
	Driver(const std::string name, int id)
		:m_name{ name }, m_id{ id } {}

	int getId() const { return m_id; }
	const std::string &getName() const { return m_name; }
};

int main()
{
	Driver d{ "Sohn", 18 };

	Car *car{ Carlot::getCar(d.getId()) };
}

//class Car
//{
//private:
//	std::string m_name;
//	int m_id;
// 
//public:
//	Car(const std::string& name, int id)
//		: m_name{ name }, m_id{ id }
//	{
//	}
// 
//	const std::string& getName() const { return m_name; }
//	int getId() const { return m_id;  }
//};
// 
//// Our CarLot is essentially just a static array of Cars and a lookup function to retrieve them.
//// Because it's static, we don't need to allocate an object of type CarLot to use it
//class CarLot
//{
//private:
//	static Car s_carLot[4];
// 
//public:
//	CarLot() = delete; // Ensure we don't try to create a CarLot
// 
//	static Car* getCar(int id)
//	{
//		for (int count{ 0 }; count < 4; ++count)
//		{
//			if (s_carLot[count].getId() == id)
//			{
//				return &(s_carLot[count]);
//			}
//		}
//		
//		return nullptr;
//	}
//};
// 
//Car CarLot::s_carLot[4]{ { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 } };
// 
//class Driver
//{
//private:
//	std::string m_name;
//	int m_carId; // we're associated with the Car by ID rather than pointer
// 
//public:
//	Driver(const std::string& name, int carId)
//		: m_name{ name }, m_carId{ carId }
//	{
//	}
// 
//	const std::string& getName() const { return m_name; }
//	int getCarId() const { return m_carId; }
//};
// 
//int main()
//{
//	Driver d{ "Franz", 17 }; // Franz is driving the car with ID 17
// 
//	Car *car{ CarLot::getCar(d.getCarId()) }; // Get that car from the car lot
//	
//	if (car)
//		std::cout << d.getName() << " is driving a " << car->getName() << '\n';
//	else
//		std::cout << d.getName() << " couldn't find his car\n";
// 
//	return 0;
//}