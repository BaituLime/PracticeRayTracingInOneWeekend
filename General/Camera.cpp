//
// Created by bunny on 3/9/22.
//

#include "Camera.h"

Camera::Camera(Vector3 origin, Vector3 lookAt, Vector3 up, double verticalFieldOfView, double aspectRatio)
{
	double theta = RabbitUtility::DegreeToRadian(verticalFieldOfView);
	double h = std::tan(theta / 2);
	double viewportHeight = 2.0 * h;

	Vector3 zAxis = (Origin - lookAt).Normalized();
	Vector3 yAxis = up.Normalized();
	Vector3 xAxis = yAxis.Cross(zAxis).Normalized();

	Origin = origin;
	HorizontalUnit = viewportHeight * aspectRatio * xAxis;
	VerticalUnit = viewportHeight * yAxis;
	LowerLeftCorner = Origin - HorizontalUnit / 2 - VerticalUnit / 2 - zAxis;
}

Ray Camera::GetRayByCoordinate(double u, double v) const
{
	return { Origin, LowerLeftCorner + u * HorizontalUnit + v * VerticalUnit - Origin };
}
