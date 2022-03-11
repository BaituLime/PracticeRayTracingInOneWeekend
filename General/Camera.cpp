//
// Created by bunny on 3/9/22.
//

#include "Camera.h"

Camera::Camera(const Vector3& origin, double aspectRatio, double viewportHeight, double focalLength)
{
	Origin = origin;
	HorizontalUnit = { viewportHeight * aspectRatio, 0, 0 };
	VerticalUnit = { 0, viewportHeight, 0 };
	LowerLeftCorner = Origin - HorizontalUnit / 2 - VerticalUnit / 2 - Vector3{ 0, 0, focalLength };
}

Ray Camera::GetRayByCoordinate(double u, double v) const
{
	return {Origin, LowerLeftCorner + u * HorizontalUnit + v * VerticalUnit - Origin};
}
