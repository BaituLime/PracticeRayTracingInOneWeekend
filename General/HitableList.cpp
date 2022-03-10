//
// Created by bunny on 3/9/22.
//

#include "HitableList.h"

HitableList::HitableList(std::shared_ptr<Hitable> object)
{
	Append(object);
}

void HitableList::Clear()
{
	Hitables.clear();
}

void HitableList::Append(const std::shared_ptr<Hitable>& object)
{
	Hitables.push_back(object);
}

bool HitableList::IsHit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
{
	HitRecord tempHitRecord;
	bool hitAnything = false;
	double closestT = tMax;

	for (auto& hitable: Hitables)
		if (hitable->IsHit(ray, tMin, closestT, tempHitRecord))
		{
			hitAnything = true;
			closestT = tempHitRecord.T;
		}
	if (hitAnything)
		record = tempHitRecord;

	return hitAnything;
}
