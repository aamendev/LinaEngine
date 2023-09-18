#include "../segment.hpp"
#include <cmath>
namespace Lina{
	Segment::Segment(const Point3D& p0, const Point3D& p1): p0(p0) , p1(p1) {}
	Segment::Segment(float length, const Point3D& p0, const Vector3D& direction){
		this->p0 = p0;
		p1 = p0 + (direction.normalise() * length).toPoint();
	}
	Segment::Segment(const Point3D& p0, const Vector3D& direction){
		this->p0 = p0;
		p1 = p0 + direction.toPoint();
	}
	float Segment::length() const{
		return (p1 - p0).magnitude();
	}
	float Segment::squaredLength() const{
		return (p1 - p0).squaredMagnitude();
	}
	Vector3D Segment::direction() const{
		return (p1 - p0).normalise();
	}
}