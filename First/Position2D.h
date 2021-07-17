#pragma once

#include <iostream>

class Position2D
{
private:
	int m_x;
	int m_y;

public:
	Position2D(const int x_in, const int y_in)
		:m_x{ x_in }, m_y{ y_in }
	{}

	void setPosition(const Position2D &pos_target)
	{
		setPosition(pos_target.m_x, pos_target.m_y);
	}

	void setPosition(const int x_target, const int y_target)
	{
		m_x = x_target;
		m_y = y_target;
	}

	friend std::ostream &operator<< (std::ostream &out, const Position2D &pos2d)
	{
		out << pos2d.m_x << " " << pos2d.m_y;

		return out;
	}
};