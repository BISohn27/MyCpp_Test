#include <iostream> //preprocessor

class Employee
{
protected:
	std::string m_name;
	int m_age;

	std::string m_position;
	int m_rank;

public:
	Employee(std::string name_in, int age_in, std::string position_in, int rank_in)
		:m_name{name_in}, m_age{age_in}, m_position{position_in}, m_rank{rank_in}{}

	Employee(const Employee &e)
	{
		m_name = e.m_name;
		m_age = e.m_age;
		m_position = e.m_position;
		m_rank = e.m_rank;
	}

	virtual void printInfo() const
	{
		std::cout << m_name << " (" << m_position <<","<<m_age<< ") " << "-> " << calculatePay() << "만원" << std::endl;
	}

	virtual int calculatePay() const { return 200 + m_rank * 50; }
};

class Manager : public Employee
{
private:
	int m_service_year;

public:
	Manager(std::string name_in, int age_in, std::string position_in, int rank_in, int service_year_in)
		:Employee(name_in, age_in, position_in, rank_in), m_service_year{ service_year_in }{}

	Manager(const Manager &m) :Employee{ m.m_name,m.m_age,m.m_position,m.m_rank }
	{
		m_service_year = m.m_service_year;
	}

	virtual int calculatePay() const override { return 200 + m_rank * 50 + 5 * m_service_year; }
	virtual void printInfo() const override
	{
		std::cout << m_name << " (" << m_position << "," << m_age << ") " << "-> " << calculatePay() << "만원" << std::endl;
	}
};

class Employeelist
{
private:
	int alloc_employee;
	int current_employee;

	Employee **employee_list;

public:
	Employeelist(int alloc_employee_in) : alloc_employee{ alloc_employee_in }
	{
		employee_list = new Employee * [alloc_employee];
		current_employee = 0;
	}

	void addEmployee(Employee *e)
	{
		if(current_employee == alloc_employee)
		{
			Employee **temp = new Employee *[alloc_employee + 10];

			for (int i = 0; i < current_employee; i++)
				temp[i] = employee_list[i];

			delete[] employee_list;

			employee_list = temp;
			temp = nullptr;

			alloc_employee += 10;
		}

		employee_list[current_employee] = e;
		current_employee++;
	}

	int currentEmployeeNumber() { return current_employee; }

	void printEmployeeInfo()
	{
		int total_pay = 0;

		for (int i = 0; i < current_employee; i++)
		{
			employee_list[i]->printInfo();
			total_pay += employee_list[i]->calculatePay();
		}

		std::cout << "Total payment is " << total_pay << "만원." << std::endl;
	}

	~Employeelist()
	{
		for (int i = 0; i < current_employee; i++)
			delete employee_list[i];

		delete[] employee_list;
	}
};

int main()
{
	Employeelist emp{ 10 };

	emp.addEmployee(new Employee("노홍철", 34, "평사원", 1));
	emp.addEmployee(new Employee("하하", 34, "평사원", 1));
	emp.addEmployee(new Manager("유재석", 41, "부장", 7, 12));
	emp.addEmployee(new Manager("정준하", 43, "과장", 4, 15));
	emp.addEmployee(new Manager("박명수", 43, "차장", 5, 13));
	emp.addEmployee(new Employee("정형돈", 36, "대리", 2));
	emp.addEmployee(new Employee("길", 36, "인턴", -2));

	emp.printEmployeeInfo();
}