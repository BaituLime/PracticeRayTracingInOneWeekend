//
// Created by bunny on 3/7/22.
//

#ifndef RAYTRACINGINONEWEEKEND_SPHERE_H
#define RAYTRACINGINONEWEEKEND_SPHERE_H

#include <utility>

#include "Hitable.hpp"

class Sphere : public Hitable
{
private:
	Vector3 Center;
	double Radius = 0;
	std::shared_ptr<Material> MainMaterial;
public:
	Sphere() = default;

	explicit Sphere(const double x, const double y, const double z, const double radius,
			std::shared_ptr<Material> material) : Center{ x, y, z }, Radius(radius), MainMaterial(std::move(material))
	{
	}

	explicit Sphere(const Vector3 center,
			std::shared_ptr<Material> material, double radius = 0) : Center(center), Radius(radius),MainMaterial(std::move(material))
	{
	}

	virtual bool IsHit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
};


#endif //RAYTRACINGINONEWEEKEND_SPHERE_H
