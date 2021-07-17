#pragma once

#include <string>
#include "Position2D.h"

class Monster
{
private:
	std::string m_name;
	Position2D  m_location;

public:
	Monster(const std::string name_in, const Position2D &pos_in)
		:m_name{name_in}, m_location{pos_in}
	{}

	void moveTo(const Position2D &pos_target)
	{
		m_location.setPosition(pos_target);
	}

	friend std::ostream &operator<< (std::ostream &out, const Monster &m)
	{
		out << m.m_name << " " << m.m_location;

		return out;
	}
};