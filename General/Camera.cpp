//
// Created by bunny on 3/9/22.
//

#include "Camera.h"


Camera::Camera(Vector3 origin, Vector3 lookAt, Vector3 up, double verticalFieldOfView, double aspectRatio,
		double aperture, double focus_dist)
{
	Origin = origin;

	double theta = RabbitUtility::DegreeToRadian(verticalFieldOfView);
	double h = std::tan(theta / 2);
	double viewportHeight = 2.0 * h;

	ZAxis = (Origin - lookAt).Normalized();
	XAxis = up.Cross(ZAxis).Normalized();
	YAxis = ZAxis.Cross(XAxis);

	HorizontalUnit = focus_dist * viewportHeight * aspectRatio * XAxis;
	VerticalUnit = focus_dist * viewportHeight * YAxis;
	LowerLeftCorner = Origin - HorizontalUnit / 2 - VerticalUnit / 2 - focus_dist * ZAxis;

	lens_radius = aperture / 2;
}

Ray Camera::GetRayByCoordinate(double u, double v) const
{
	Vector3 rd = lens_radius * Vector3::random_in_unit_disk();
	Vector3 offset = XAxis * rd[0] + YAxis * rd[1];
	return { Origin + offset, LowerLeftCorner + u * HorizontalUnit + v * VerticalUnit - Origin - offset };
}
