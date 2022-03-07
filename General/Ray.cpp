//
// Created by bunny on 3/4/22.
//

#include "Ray.h"

Vector3 Ray::GetOrigin() const
{
	return Origin;
}

Vector3 Ray::GetDirection() const
{
	return Direction;
}

Vector3 Ray::At(double t) const
{
	return Origin + t * Direction;
}

Color Ray::GetColor() const
{
	Vector3 unitDirection = Direction.Normalized();
	auto t = .5 * (unitDirection[1] + 1.0);
	Vector3 result = (1 - t) * Vector3(1.0) + t * Vector3(.5, .7, 1.0);
	return Color(result);
}
