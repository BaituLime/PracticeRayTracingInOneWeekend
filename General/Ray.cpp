//
// Created by bunny on 3/4/22.
//

#include "Ray.h"
#include "Color.h"
#include "Hitable.hpp"

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

Color Ray::GetColor(Hitable& world, int depth)
{
	if (depth <= 0)
		return {};

	HitRecord hitRecord;
	if (world.IsHit(*this, 0.001, Infinity, hitRecord))
	{
		Vector3 target = hitRecord.IntersectionPoint + hitRecord.Normal + Vector3::RandomPointInUnitSphere().Normalized();
		Ray fromIntersectionToTarget(hitRecord.IntersectionPoint, target - hitRecord.IntersectionPoint);
		Color theColor = fromIntersectionToTarget.GetColor(world, depth - 1);
		theColor.GetData() *= .5;
		return theColor;
	}

	// Gradient Background.
	Vector3 unitDirection = Direction.Normalized();
	double t = .5 * (unitDirection[1] + 1.0);
	return Color((1 - t) * Vector3(1.0) + t * Vector3(.5, .7, 1.0));
}