//
// Created by bunny on 3/7/22.
//

#include "Sphere.h"

bool Sphere::IsHit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
{
	// Calculate discriminant.
	// not b^2 - 4ac, as b^2/4 -ac.
	Vector3 aSubC = ray.GetOrigin() - Center;
	double a = ray.GetDirection().LengthSquared();
	//double b = 2.0 * Direction.Dot(aSubC);
	double halfB = ray.GetDirection().Dot(aSubC);
	double c = aSubC.LengthSquared() - Radius * Radius;
	double discriminant = halfB * halfB - a * c;

	if (discriminant < 0)
		return false;

	// Find the nearest root that lies in the acceptable range.
	double sqrtDiscriminant = std::sqrt(discriminant);
	double resultT = (-halfB - sqrtDiscriminant) / a;
	if (resultT <= tMin || tMax <= resultT)
	{
		resultT = (-halfB + sqrtDiscriminant) / a;
		if (resultT <= tMin || tMax <= resultT)
			return false;
	}

	Vector3 resultPoint = ray.At(resultT);
	Vector3 resultOutwardNormal = (resultPoint - Center) / Radius;
	record = { resultT, resultPoint };
	record.SetNormalAgainstRay(ray, resultOutwardNormal);
	return true;
}
