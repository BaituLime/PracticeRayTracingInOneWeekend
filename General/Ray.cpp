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
	// Normal Visualization.
	Sphere s({ 0, 0, -1 }, 0.5);
	double t = HitSpherePoint(s);
	if (t > 0.0)
	{
		Vector3 normal = (At(t) - Vector3{ 0, 0, -1 }).Normalized();
		normal[0]++;
		normal[1]++;
		normal[2]++;
		normal *= .5;
		return Color(normal);
	}

	// Gradient Background.
	Vector3 unitDirection = Direction.Normalized();
	t = .5 * (unitDirection[1] + 1.0);
	Vector3 result = (1 - t) * Vector3(1.0) + t * Vector3(.5, .7, 1.0);
	return Color(result);
}

double Ray::HitSpherePoint(Sphere& sphere)
{
	// Calculate discriminant.
	Vector3 aSubC = Origin - sphere.Center;
	double a = Direction.Dot(Direction);
	double b = 2.0 * Direction.Dot(aSubC);
	double c = aSubC.Dot(aSubC) - sphere.Radius * sphere.Radius;
	double discriminant = b * b - 4 * a * c;

	// Give back the "t".
	if (discriminant < 0)
		return -1.0;
	else
		return (-b - std::sqrt(discriminant)) / (2.0 * a);
}
