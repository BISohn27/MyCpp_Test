#include <iostream>
#include <memory> // for std::shared_ptr
#include <string>
#include <cassert>

bool returnLeapYearflag(const int& year);

class Date
{
private:
	int m_year=0;
	int m_month=0;
	int m_day=0;
	int m_arr1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int m_arr2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };

public:
	Date(int year = 0, int month = 0, int day = 0)
		:m_year{ year }, m_month{ month }, m_day{ day }{}

	friend std::ostream &operator<< (std::ostream &out, const Date &d);

	void setDate(int year, int month, int day)
	{
		assert(((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			&& (day <= 31 && day > 0)) || ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 0 && day <= 30))
			|| (month == 2 && (day > 0 && day <= 28)));
	
			m_year = year;
			m_month = month;
			m_day = day;
	
	}

	void addYear(int inc)
	{
		m_year += inc;
	}
	
	void addMonth(int inc)
	{
		m_year += inc / 12;
		inc %= 12;

		if ((m_month += inc) > 12)
		{
			m_month -= 12;
			m_year++;
		}
	}

	void addDay(int inc)
	{
		int add_month         = 0;
		int i                 = 0;
		bool month_over_check = false;
		int *month_list       = nullptr;

		//if inc is more than 1 year, calculate how much it is, and increase year. 
		m_year += inc / 365;
		inc %= 365;

		if(returnLeapYearflag(m_year))
		{
			month_list = m_arr2;
		// find how many months add
			for (i = m_month - 1; i < 12; i++)
			{
				if ((inc - month_list[i]) <= 0) // if month is smaller than the number of the month, break
				{
					month_over_check = true;
					break;
				}

				inc -= month_list[i]; // calculate add
				add_month++;	  // calculate months we have to add
			}

			if (!month_over_check) // if inc is more than December after the above calculation, calculate again.
				for (i = 0; i < 12; i++)
				{
					month_list = m_arr1;

					if ((inc - month_list[i]) <= 0) // if month is smaller than the number of the month, break
						break;

					inc -= month_list[i]; // calculate add
					add_month++;
				}

			addMonth(add_month);

			if (m_month != 12)
			{
				if ((m_day += inc) > month_list[m_month - 1])
				{
					m_day -= month_list[m_month - 1];
					m_month++;
				}
			}

			else
				if ((m_day += inc) > month_list[11])
				{
					m_day -= month_list[11];
					m_month = 1;
					m_year++;
				}
		}

		else if (returnLeapYearflag(m_year+1))
		{
			month_list = m_arr1;
			// find how many months add
			for (i = m_month - 1; i < 12; i++)
			{
				if ((inc - month_list[i]) <= 0) // if month is smaller than the number of the month, break
				{
					month_over_check = true;
					break;
				}

				inc -= month_list[i]; // calculate add
				add_month++;	  // calculate months we have to add
			}

			if (!month_over_check) // if inc is more than December after the above calculation, calculate again.
				for (i = 0; i < 12; i++)
				{
					month_list = m_arr2;

					if ((inc - month_list[i]) <= 0) // if month is smaller than the number of the month, break
						break;

					inc -= month_list[i]; // calculate add
					add_month++;
				}

			addMonth(add_month);

			if (m_month != 12)
			{
				if ((m_day += inc) > month_list[m_month - 1])
				{
					m_day -= month_list[m_month - 1];
					m_month++;
				}
			}

			else
				if ((m_day += inc) > month_list[11])
				{
					m_day -= month_list[11];
					m_month = 1;
					m_year++;
				}
		}

		else
		{
			month_list = m_arr1;
			// find how many months add
			for (i = m_month - 1; i < 12; i++)
			{
				if ((inc - month_list[i]) <= 0) // if month is smaller than the number of the month, break
				{
					month_over_check = true;
					break;
				}

				inc -= month_list[i]; // calculate add
				add_month++;	  // calculate months we have to add
			}

			if (!month_over_check) // if inc is more than December after the above calculation, calculate again.
				for (i = 0; i < 12; i++)
				{
					if ((inc - month_list[i]) <= 0) // if month is smaller than the number of the month, break
						break;

					inc -= month_list[i]; // calculate add
					add_month++;
				}

			addMonth(add_month);

			if (m_month != 12)
			{
				if ((m_day += inc) > month_list[m_month - 1])
				{
					m_day -= month_list[m_month - 1];
					m_month++;
				}
			}

			else
				if ((m_day += inc) > month_list[11])
				{
					m_day -= month_list[11];
					m_month = 1;
					m_year++;
				}
		}

	}
};

std::ostream &operator<<(std::ostream &out, const Date &d)
{
	out << d.m_year << "/" << d.m_month << "/" << d.m_day << std::endl;

	return out;
}

bool returnLeapYearflag(const int& year)
{
	bool flag = false;

	if ((year % 4 == 0) && !((year % 100 == 0) && !(year % 400 == 0)))
	{
		flag = true;
		return flag;
	}

	return flag;
}

int main()
{
	Date date;

	date.setDate(2400, 2, 22);

	std::cout << date;

	date.addDay(7);

	std::cout << date;

	return 0;
}