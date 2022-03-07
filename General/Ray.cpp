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

Color Ray::GetColor()
{
	Sphere s({ 0, 0, 2 }, 0.5);
	if (CanHitSphere(s))
		return { 1, 0, 0 };
	Vector3 unitDirection = Direction.Normalized();
	auto t = .5 * (unitDirection[1] + 1.0);
	Vector3 result = (1 - t) * Vector3(1.0) + t * Vector3(.5, .7, 1.0);
	return Color(result);
}

bool Ray::CanHitSphere(Sphere& sphere)
{
	return CalculateHitSphereDiscriminant(sphere) > 0;
}

double Ray::CalculateHitSphereDiscriminant(Sphere& sphere)
{
	Vector3 aSubC = Origin - sphere.Center;
	double a = Direction.Dot(Direction);
	double b = 2.0 * Direction.Dot(aSubC);
	double c = aSubC.Dot(aSubC) - sphere.Radius * sphere.Radius;
	return b * b - 4 * a * c;
}
