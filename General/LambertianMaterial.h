//
// Created by bunny on 3/13/22.
//

#ifndef RAYTRACINGINONEWEEKEND_LAMBERTIANMATERIAL_H
#define RAYTRACINGINONEWEEKEND_LAMBERTIANMATERIAL_H

#include "CommonHeader.hpp"
#include "Material.hpp"
#include "Color.h"

class LambertianMaterial : public Material
{
private:
	Color Albedo;
public:
	LambertianMaterial() = delete;

	LambertianMaterial(const Color& color) : Albedo(color)
	{
	}

	bool Scatter(const Ray& in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

};

#endif //RAYTRACINGINONEWEEKEND_LAMBERTIANMATERIAL_H
