#pragma once
#include "Vector3D.h"
#include "Point3D.h"
#include "Transform4D.h"
#include <utility>
namespace Lina{ namespace Math{
	class Plane{
	public:
		float x, y, z , w;
	public:
		Plane() = default;
		Plane(float nx, float ny, float nz, float d);
		Plane(const Vector3D& n, float d);
		const Vector3D& getNormal() const;
		float dot(const Vector3D& v);
		float dot(const Point3D& p);
		Plane normalise() const;
		Point3D intersect(const Point3D& p, const Vector3D& v);
		Point3D intersect(const Plane& p1, const Plane& p2) const;
		std::pair<Point3D, Vector3D> intersect(const Plane& p1);
		friend Plane operator *(const Plane& f, const Transform4D& h);
        float getDistanceFromOrigin() const;
	};
}}
