#include <iostream>

class Cents
{
private:
    int m_cents;

public:
    Cents(int cents=0)
        : m_cents{ cents }
    {}

    Cents operator-() const;
    bool operator!() const;

    friend std::ostream &operator<< (std::ostream &out, const Cents &c);
    friend Cents operator+(const Cents &c1, const Cents &c2);
    friend Cents operator+(int value, const Cents &c1);
    friend Cents operator+(const Cents &c1,int value);
    
    int getCents() { return m_cents; }

};

Cents operator+ (const Cents &c1, const Cents &c2) 
{
    return Cents{ c1.m_cents + c2.m_cents };
}

Cents operator+(int value, const Cents &c1) 
{
    return value + c1.m_cents;
}

Cents operator+(const Cents &c1,int value)
{
    return value + c1.m_cents;
}

Cents Cents::operator-() const
{
    return Cents{ -m_cents };
}

bool Cents::operator!() const
{
    if (m_cents == 0)
        return true;
    else
        return false;
}

std::ostream &operator<< (std::ostream &out, const Cents &c)
{
    out << c.m_cents << std::endl;

    return out;
}

int main()
{
    Cents c1{ 2 };
    Cents c2{ c1 + 2};

    //c1 + 2 = (member function operator+)c1.operator+(2) -> c1.operator+(&c1(this pointer),2)

    std::cout << c2;

    std::cout << -c2;

}