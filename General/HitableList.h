//
// Created by bunny on 3/9/22.
//

#ifndef RAYTRACINGINONEWEEKEND_HITABLELIST_H
#define RAYTRACINGINONEWEEKEND_HITABLELIST_H

#include <memory>
#include <vector>

#include "Hitable.hpp"

class HitableList : public Hitable
{
private:
	std::vector<std::shared_ptr<Hitable>> Hitables;
public:
	HitableList() = default;
	HitableList(std::shared_ptr<Hitable> object);

	void Clear();
	void Append(const std::shared_ptr<Hitable>& object);
	bool IsHit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
};


#endif //RAYTRACINGINONEWEEKEND_HITABLELIST_H
