//
// Created by bunny on 3/7/22.
//

#ifndef RAYTRACINGINONEWEEKEND_SPHERE_H
#define RAYTRACINGINONEWEEKEND_SPHERE_H

#include "Hitable.hpp"

class Sphere : public Hitable
{
private:
	Vector3 Center;
	double Radius = 0;
public:
	Sphere() = default;

	explicit Sphere(const double x, const double y, const double z, const double radius) : Center{ x, y, z }, Radius(radius)
	{
	}

	explicit Sphere(const Vector3 center, double radius = 0) : Center(center), Radius(radius)
	{
	}

	virtual bool IsHit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
};


#endif //RAYTRACINGINONEWEEKEND_SPHERE_H
