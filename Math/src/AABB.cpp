#include "../AABB.h"
namespace Lina{ namespace Math{
	AABB::AABB(const Point3D& p0, const Point3D& p1): min(p0), max(p1) {}

	AABB::AABB(float x0, float y0, float z0, float x1,
	 float y1, float z1): min(Point3D(x0,y0,z0)), max(Point3D(x1,y1,z1)){}

	bool AABB::intersects(const AABB& b) const{
		return !(max.x < b.min.x || min.x > b.max.x)
		&& !((max.y < b.min.y || min.y > b.max.y))
		&& !((max.z < b.min.z || min.z > b.max.z));
	}
	float AABB::squaredDistance(const Point3D& p){
		return(
			(p.x < min.x) * (min.x - p.x) * (min.x - p.x) +
			(p.x > max.x) * (max.x - p.x) * (max.x - p.x) +
			(p.y < min.y) * (min.y - p.y) * (min.x - p.y) +
			(p.y > max.y) * (max.y - p.y) * (max.x - p.y) +
			(p.z < min.z) * (min.z - p.z) * (min.z - p.z) +
			(p.z > max.z) * (max.z - p.z) * (max.z - p.z)
		);
	}
	float AABB::squaredDistance(const Point3D& p) const{
		return sqrt(this->squaredDistance(p));
	}
	bool AABB::intersects(const Sphere& s) const{
		return squaredDistance(s.centre) <= s.radius * s.radius;
	}

}}
