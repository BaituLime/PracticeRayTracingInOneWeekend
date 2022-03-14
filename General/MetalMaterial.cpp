//
// Created by bunny on 3/13/22.
//

#include "MetalMaterial.h"
#include "Hitable.hpp"

bool MetalMaterial::Scatter(const Ray& in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
	Vector3 scatterDirection = in.GetDirection().Normalized().Reflect(record.Normal);
	scattered = Ray(record.IntersectionPoint, scatterDirection + Fuzziness * Vector3::RandomPointInUnitSphere());
	attenuation = Albedo;
	return scatterDirection.Dot(record.Normal) > 0;
}
