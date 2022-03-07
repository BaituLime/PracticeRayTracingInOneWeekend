//
// Created by bunny on 3/4/22.
//

#ifndef RAYTRACINGINONEWEEKEND_RAY_H
#define RAYTRACINGINONEWEEKEND_RAY_H

#include <cmath>
#include "Vector3.h"
#include "Color.h"
#include "Sphere.h"

// P(t)=A+tb
class Ray
{
private:
	Vector3 Origin;
	Vector3 Direction;

public:
	Ray() = default;

	Ray(Vector3 origin, Vector3 direction) : Origin(origin), Direction(direction)
	{
	}

	Ray(Vector3& origin, Vector3& direction) : Origin(origin), Direction(direction)
	{
	}

	Vector3 GetOrigin() const;
	Vector3 GetDirection() const;
	Vector3 At(double t) const;

	Color GetColor();

	double HitSpherePoint(Sphere& sphere);
};


#endif //RAYTRACINGINONEWEEKEND_RAY_H
