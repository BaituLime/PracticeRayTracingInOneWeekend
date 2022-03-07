//
// Created by bunny on 3/7/22.
//

#ifndef RAYTRACINGINONEWEEKEND_SPHERE_H
#define RAYTRACINGINONEWEEKEND_SPHERE_H

#include "Vector3.h"

class Sphere
{
private:
	Vector3 Center;
	double Radius = 0;
public:
	Sphere() = default;
	explicit Sphere(const Vector3 center, double radius = 0) : Center(center), Radius(radius)
	{
	}

	friend class Ray;
};


#endif //RAYTRACINGINONEWEEKEND_SPHERE_H
