#pragma once
#include "object.h"
#include "point3.h"
#include "vector3.h"

class Plane : public Object
{
public:
	Point3 origin;
	Vector3 v1;
	Vector3 v2;

	Plane(Point3 origin, Vector3 v1, Vector3 v2, const Material& material);

	std::unique_ptr<const Object> get_unique_ptr() const override;
	bool hit(const Ray& ray, Interval t_interval, Hit& hit_payload) const override;
};