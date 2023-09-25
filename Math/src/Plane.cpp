#include "../Plane.h"
#include <cfloat>
#include <cmath>
#include <stdexcept>
namespace Lina{ namespace Math{
	Plane::Plane(float nx, float ny, float nz, float d):
	x(nx), y(ny), z(nz), w(d){}
	Plane::Plane(const Vector3D& v, float d):
	x(v.x), y(v.y), z(v.z), w(d){}
	const Vector3D& Plane::getNormal() const{
		return reinterpret_cast<const Vector3D&>(x);
	}
	float Plane::dot(const Vector3D& v){
		return x * v.x + y * v.y + z * v.z;
	}
	float Plane::dot(const Point3D& p){
		return x * p.x + y * p.y + z * p.z + w;
	}
	Plane Plane::normalise() const{
		Vector3D v = getNormal();
		float f = w / v.magnitude();
		return Plane(v.normalise(), f);
	}
	Point3D Plane::intersect(const Point3D& p, const Vector3D& v){
		float fv = this->dot(v);
		if (fabs(fv) > FLT_MIN){
			return p - v * (this->dot(p) / fv);
		}else{
			throw std::invalid_argument("Line does not intersect this plane");
		}
	}
    float Plane::getDistanceFromOrigin() const{
        return w;
    }
	Point3D Plane::intersect(const Plane& p1, const Plane& p2) const{
		const Vector3D& n1 = this->getNormal();
		const Vector3D& n2 = p1.getNormal();
		const Vector3D& n3 = p2.getNormal();
		Vector3D n1xn2 = n1.cross(n2);
		float det = n1xn2.dot(n3);
		det = 1 / det;
		if (fabs(det) > FLT_MIN){
			return ((n3.cross(n2) * w + n1.cross(n3)
				* p1.w - n1xn2 * p2.w) * det).toPoint();
		}else{
			throw std::invalid_argument("Planes do not intersect");
		}
	}

	std::pair<Point3D, Vector3D> Plane::intersect(const Plane& p1){
		const Vector3D& n1 = this->getNormal();
		const Vector3D& n2 = p1.getNormal();
		Vector3D v = n1.cross(n2);
		float det = v.dot(v);
		if (fabs(det) > FLT_MIN){
			Point3D p = ((v.cross(n2) * w + n1.cross(v) * p1.w) / det).toPoint();
			return std::make_pair(p, v);
		}else{
			throw std::invalid_argument("Planes do not intersect");
		}
	}
	Plane operator *(const Plane& f, const Transform4D& h){
		return Plane(
			f.x * h(0, 0) + f.y * h(1, 0) + f.z * h(2, 0),
			f.x * h(0, 1) + f.y * h(1, 1) + f.z * h(2, 1),
			f.x * h(0, 2) + f.y * h(1, 2) + f.z * h(2, 2),
			f.x * h(0, 3) + f.y * h(1, 3) + f.z * h(2, 3) + f.w
			);
	}
}}
