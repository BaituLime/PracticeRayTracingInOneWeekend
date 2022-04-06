//
// Created by bunny on 3/14/22.
//

#include "DielectricMaterial.h"
#include "Hitable.hpp"

bool DielectricMaterial::Scatter(const Ray& in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0);
	double refractionRatio = record.IsEnteringRayFrontOfFace ? (1.0 / RefractionIndex) : RefractionIndex;

	Vector3 inDirection = in.GetDirection().Normalized();
	double cosTheta = std::fmin((-inDirection).Dot(record.Normal), 1.0);
	double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

	bool cantRefract = refractionRatio * sinTheta > 1.0;
	scattered = Ray(record.IntersectionPoint,
			(cantRefract || Reflectance(cosTheta, refractionRatio) > RabbitUtility::Random()) ?
			inDirection.Reflect(record.Normal) :
			inDirection.Refract(record.Normal, refractionRatio));
	return true;
}

double DielectricMaterial::Reflectance(double cosine, double ref_idx)
{
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}