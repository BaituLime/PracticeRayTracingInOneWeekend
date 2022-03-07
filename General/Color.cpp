//
// Created by bunny on 3/5/22.
//

#include "Color.h"

Color::Color()
{
	Data = new Vector3(0.0);
}

Color::Color(double element)
{
	Data = new Vector3(element);
}

Color::Color(double* elements)
{
	Data = new Vector3(elements[3]);
}

Color::Color(Vector3& data)
{
	Data = new Vector3(data);
}

Color::Color(Color& other)
{
	Data = new Vector3(*other.Data);
}

Color::Color(double x, double y, double z)
{
	Data = new Vector3(x, y, z);
}

Color::~Color()
{
	delete Data;
}

Vector3& Color::GetData()
{
	return *Data;
}

std::ostream& operator<<(std::ostream& out, const Color& color)
{
	return out << int(256 * (*color.Data)[0]) << ' ' << int(256 * (*color.Data)[1]) << ' '
			   << int(256 * (*color.Data)[2]);
}