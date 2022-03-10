//
// Created by bunny on 3/8/22.
//

#ifndef RAYTRACINGINONEWEEKEND_HITABLE_HPP
#define RAYTRACINGINONEWEEKEND_HITABLE_HPP

#include "CommonHeader.hpp"
#include "Color.h"

struct HitRecord
{
public:
	double T;
	Vector3 IntersectionPoint;
	Vector3 Normal;

public:
	void SetNormalAgainstRay(const Ray& ray, const Vector3& outwardNormal)
	{
		Normal = ray.GetDirection().Dot(outwardNormal) < 0 ? outwardNormal : -outwardNormal;
	}
};

class Hitable
{
public:
	virtual bool IsHit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};


#endif //RAYTRACINGINONEWEEKEND_HITABLE_HPP
