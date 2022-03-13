//
// Created by bunny on 3/13/22.
//

#ifndef RAYTRACINGINONEWEEKEND_MATERIAL_HPP
#define RAYTRACINGINONEWEEKEND_MATERIAL_HPP

#include "CommonHeader.hpp"

struct HitRecord;

// This is an abstract class.
class Material
{
public:
	virtual bool Scatter(const Ray& in, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};


#endif //RAYTRACINGINONEWEEKEND_MATERIAL_HPP
