//
// Created by bunny on 3/3/22.
//

#ifndef RAYTRACINGINONEWEEKEND_COLOR_H
#define RAYTRACINGINONEWEEKEND_COLOR_H

#include "Vector3.h"

class Color
{
private:
	Vector3 Data;

public:
	Color() : Data(0.0)
	{
	}

	explicit Color(double element) : Data(element)
	{
	}

	explicit Color(double elements[3]) : Data(elements)
	{
	}

	explicit Color(Vector3 data) : Data(data)
	{
	}

	Color(double x, double y, double z) : Data(x, y, z)
	{
	}

	Vector3& GetData();
	Color& operator=(const Color& other);
	friend std::ostream& operator<<(std::ostream& out, Color& color);
};

std::ostream& operator<<(std::ostream& out, const Color& color);

#endif //RAYTRACINGINONEWEEKEND_COLOR_H
