#include "../Ray.hpp"
namespace Lina{
	Ray::Ray(const Point3D& p, const Vector3D& v): base(p), direction(v){}
	float Ray::distance(const Point3D& p) const{
		if ((p - base).dot(direction) < 0)
			return (p - base).magnitude();
		return (p - base).reject(direction).magnitude();
	}
}