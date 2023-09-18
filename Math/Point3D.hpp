#pragma once
#include "Vector3D.hpp"
namespace Lina{
	class Point3D : public Vector3D{
	public:
		Point3D() = default;
		Point3D(float a, float b, float c): Vector3D(a, b, c) {}
		friend inline Point3D operator+(const Point3D& a, const Point3D& b);
		friend inline Vector3D operator-(const Point3D& a, const Point3D& b);
		friend inline Point3D operator-(const Point3D& a, const Vector3D& b);
		float distance(const Point3D& p);
		float distanceSquared(const Point3D& p);
	};
	Point3D operator+(const Point3D& a, const Point3D& b){
		return Point3D(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	Vector3D operator-(const Point3D& a, const Point3D& b){
		return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
	};
	Point3D operator-(const Point3D& a, const Vector3D& b){
		return Point3D(a.x - b.x, a.y - b.y, a.z - b.z);
	}
}