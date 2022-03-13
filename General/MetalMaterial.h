//
// Created by bunny on 3/13/22.
//

#ifndef RAYTRACINGINONEWEEKEND_METALMATERIAL_H
#define RAYTRACINGINONEWEEKEND_METALMATERIAL_H

#include "CommonHeader.hpp"
#include "Material.hpp"
#include "Color.h"

class MetalMaterial : public Material
{
private:
	Color Albedo;
public:
	MetalMaterial() = delete;

	MetalMaterial(const Color& color) : Albedo(color)
	{
	}

	bool Scatter(const Ray& in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;
};


#endif //RAYTRACINGINONEWEEKEND_METALMATERIAL_H
