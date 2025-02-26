#include "plane.h"
#include "ray.h"
#include "hit.h"

Plane::Plane(Point3 origin, Vector3 v1, Vector3 v2, const Material& material)
	: Object(&material), origin(origin), v1(v1), v2(v2) {}

std::unique_ptr<const Object> Plane::get_unique_ptr() const {
	return std::make_unique<const Plane>(*this);
}

bool Plane::hit(const Ray& ray, Interval t_interval, Hit& hit_payload) const {
	Vector3 normal = cross(v1, v2).make_unit();

	double a = normal.x;
	double b = normal.y;
	double c = normal.z;
	double d = -(a * origin.x + b * origin.y + c * origin.z);

	Vector3 ray_direction = ray.get_direction();

	if (a * ray_direction.x + b * ray_direction.y + c * ray_direction.z == 0) {
		return false;
	}

	double t = -(a * ray.get_origin().x + b * ray.get_origin().y + c * ray.get_origin().z + d)
		/ (a * ray_direction.x + b * ray_direction.y + c * ray_direction.z);

	if (!t_interval.contains(t))
		return false;

	hit_payload.t = t;
	hit_payload.point = ray.at(t);
	Vector3 outward_normal = normal;
	hit_payload.set_face_normal(ray, outward_normal);
	hit_payload.material = material;

	return true;
}