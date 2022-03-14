//
// Created by bunny on 3/14/22.
//

#ifndef RAYTRACINGINONEWEEKEND_DIELECTRICMATERIAL_H
#define RAYTRACINGINONEWEEKEND_DIELECTRICMATERIAL_H

#include "CommonHeader.hpp"
#include "Material.hpp"
#include "Color.h"

class DielectricMaterial:public Material
{
private:
	double RefractionIndex;
public:
	DielectricMaterial()=delete;
	explicit DielectricMaterial(double refractionIndex): RefractionIndex(refractionIndex){}

	bool Scatter(const Ray &in, const HitRecord &record, Color &attenuation, Ray &scattered) const override;
private:
	static double Reflectance(double cosine, double ref_idx);
};


#endif //RAYTRACINGINONEWEEKEND_DIELECTRICMATERIAL_H
