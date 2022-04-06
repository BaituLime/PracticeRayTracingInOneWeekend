//
// Created by bunny on 3/9/22.
//

#ifndef RAYTRACINGINONEWEEKEND_CAMERA_H
#define RAYTRACINGINONEWEEKEND_CAMERA_H

#include "CommonHeader.hpp"

class Camera
{
private:
	Vector3 Origin;
	Vector3 LowerLeftCorner;
	Vector3 HorizontalUnit;
	Vector3 VerticalUnit;

	Vector3 XAxis;
	Vector3 YAxis;
	Vector3 ZAxis;

	double lens_radius;
public:
	Camera() = delete;
	explicit Camera(Vector3 origin, Vector3 lookAt, Vector3 up, double verticalFieldOfView,
			double aspectRatio = 16.0 / 9.0, double aperture = .1, double focus_dist = 10.0);

	Ray GetRayByCoordinate(double u, double v) const;
};

#endif //RAYTRACINGINONEWEEKEND_CAMERA_H
