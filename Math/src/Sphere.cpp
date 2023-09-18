#include "../Sphere.hpp"
namespace Lina{
	Sphere::Sphere(const Point3D& c, float r): centre(c), radius(r) {}
	void Sphere::setCentre(const Point3D& c){
		centre = c;
	}
	void Sphere::setRadius(float r){
		radius = r;
	}
	Vector4D Sphere::vectorRep() const{
		return Vector4D(centre.x, centre.y, centre.z, radius);
	}
	bool Sphere::intersects(const Sphere& S) const{
		return (centre - S.centre).dot(centre - S.centre) <= radius + S.radius;
	}
	bool Sphere::intersects(const Ray& r) const{
		if ((centre - r.base).dot(r.direction) < 0 &&
		 (centre -r.base).dot(centre - r.base) > radius * radius)
			return false;
		return (centre - r.base).reject(r.direction).magnitude() <= radius;
	}
}