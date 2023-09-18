#include "../Line.hpp"
#include <cmath>
namespace Lina{
	Line::Line(float vx, float vy, float vz, float mx, float my, float mz):
	direction(vx, vy, vz), moment(mx, my, mz) {}
	Line::Line(const Vector3D& v, const Vector3D& m): direction(v), moment(m) {}
	Line::Line(const Point3D& p, const Vector3D& v) : 
	direction(v), moment(p.cross(v)) {}
	Line::Line(const Point3D& p): direction(p), moment(Vector3D(0, 0, 0)) {}

	float Line::distance(const Line& l){
		return fabs(direction.dot(l.moment) + moment.dot(l.direction)) / direction.cross(l.direction).magnitude();
	}
	float Line::distance(const Point3D& p){
		return (direction.cross(p) + moment).magnitude() / direction.magnitude();
	}
}