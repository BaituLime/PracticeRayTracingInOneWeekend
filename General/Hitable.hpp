//
// Created by bunny on 3/8/22.
//

#ifndef RAYTRACINGINONEWEEKEND_HITABLE_HPP
#define RAYTRACINGINONEWEEKEND_HITABLE_HPP

#include "CommonHeader.hpp"
#include "Color.h"

class Material;

struct HitRecord
{
public:
	double T;
	Vector3 IntersectionPoint;
	std::shared_ptr<Material> TheMaterial;
	Vector3 Normal;
	bool IsEnteringRayFrontOfFace;

public:
	void SetNormalAgainstRay(const Ray& ray, const Vector3& outwardNormal)
	{
		IsEnteringRayFrontOfFace = ray.GetDirection().Dot(outwardNormal) < 0;
		Normal = IsEnteringRayFrontOfFace ? outwardNormal : -outwardNormal;
	}
};

// This is an abstract class.
class Hitable
{
public:
	virtual bool IsHit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};


#endif //RAYTRACINGINONEWEEKEND_HITABLE_HPP
