#include <iostream>

class Weapon
{
protected:
    int power;

public:
    Weapon(int power_in)
        :power{ power_in }
    {
        std::cout << "Power(int)" << std::endl;
    }

    virtual void use()
    {
        std::cout << "Weapon::use()" << std::endl;
    }
};

class Sword : public Weapon
{
public:
    Sword(int power_in)
        :Weapon{ power_in }
    {
        std::cout << "Sword(int)" << std::endl;
    }

    void use()
    {
        std::cout << "Sword::use()" << std::endl;
        swing();
    }

private:
    void swing()
    {
        std::cout << "Swing sword" << std::endl;
    }
};

class Magic : public Weapon
{
private:
    int manacost;

public:
    Magic(int manacost_in, int power_in)
        :Weapon{ power_in }, manacost{ manacost_in }
    {
        std::cout << "Magic(int, int)" << std::endl;
    }

    void use()
    {
        std::cout << "Magic::use()" << std::endl;
        cast();
    }

    void cast()
    {
        std::cout << "Cast magic" << std::endl;
    }
    
};

int main()
{
    Sword my_sword(10);
    Magic my_magic(15, 7);

    my_sword.use();
    my_magic.use();

    Weapon *current_weapon;

    current_weapon = &my_sword;

    current_weapon->use();

    return 0;
}