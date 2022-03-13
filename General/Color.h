//
// Created by bunny on 3/3/22.
//

#ifndef RAYTRACINGINONEWEEKEND_COLOR_H
#define RAYTRACINGINONEWEEKEND_COLOR_H

#include "Vector3.h"

class Color
{
private:
	Vector3* Data = nullptr;

public:
	Color();
	explicit Color(double element);
	explicit Color(double elements[3]);
	explicit Color(Vector3 data);
	Color(const Color& other);
	Color(double x, double y, double z);
	~Color();

	Vector3& GetData();

	Color& operator=(const Color& other);

	friend std::ostream& operator<<(std::ostream& out, const Color& color);
};

std::ostream& operator<<(std::ostream& out, const Color& color);

#endif //RAYTRACINGINONEWEEKEND_COLOR_H
