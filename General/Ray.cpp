//
// Created by bunny on 3/4/22.
//

#include "CommonHeader.hpp"
#include "Color.h"
#include "Hitable.hpp"
#include "Material.hpp"

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
		Ray scatteredResult;
		Color attenuation;
		if (hitRecord.TheMaterial->Scatter(*this, hitRecord, attenuation, scatteredResult))
		{
			Color result(scatteredResult.GetColor(world, depth - 1));
			result.GetData() *= attenuation.GetData();
			return result;
		}
		return {};
	}

	// Gradient Background.
	Vector3 unitDirection = Direction.Normalized();
	double t = .5 * (unitDirection[1] + 1.0);
	return Color((1 - t) * Vector3(1.0) + t * Vector3(.5, .7, 1.0));
}