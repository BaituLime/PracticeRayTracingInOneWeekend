//
// Created by bunny on 3/13/22.
//

#include "LambertianMaterial.h"
#include "Hitable.hpp"

// Notice to remember to switch between them usually.
//#define LAZYHACK_LAMBERTIAN_REFLECTION
#define TRUE_LAMBERTIAN_REFLECTION
//#define HEMISPHERE_DIFFUSE_FORMULATION

bool LambertianMaterial::Scatter(const Ray& in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
#ifdef LAZYHACK_LAMBERTIAN_REFLECTION
	Vector3 scatterDirection = record.Normal + Vector3::RandomPointInUnitSphere();
#endif
#ifdef TRUE_LAMBERTIAN_REFLECTION
	Vector3 scatterDirection = record.Normal + Vector3::RandomPointOnUnitSphere();
#endif
#ifdef HEMISPHERE_DIFFUSE_FORMULATION
	Vector3 scatterDirection = record.Normal + Vector3::RandomPointInHemisphere(record.Normal);
#endif
	if (scatterDirection.IsNearZero())
		scatterDirection = record.Normal;
	scattered = Ray(record.IntersectionPoint, scatterDirection);
	attenuation = Albedo;
	return true;
}
