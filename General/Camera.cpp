//
// Created by bunny on 3/9/22.
//

#include "Camera.h"

Camera::Camera(Vector3 origin, Vector3 lookAt, Vector3 up, double verticalFieldOfView, double aspectRatio)
{
	double theta = RabbitUtility::DegreeToRadian(verticalFieldOfView);
	double h = std::tan(theta / 2);
	double viewportHeight = 2.0 * h;

	Origin = origin;
	Vector3 w = (Origin - lookAt).Normalized();
	Vector3 u = up.Normalized().Cross(w).Normalized();
	Vector3 v = w.Normalized().Cross(u).Normalized();

	
	HorizontalUnit = viewportHeight * aspectRatio * u;
	VerticalUnit = viewportHeight * v;
	LowerLeftCorner = Origin - HorizontalUnit / 2 - VerticalUnit / 2 - w;
}

Ray Camera::GetRayByCoordinate(double u, double v) const
{
	return Ray{ Origin, LowerLeftCorner + u * HorizontalUnit + v * VerticalUnit - Origin };
}
