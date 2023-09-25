#pragma once
#include "Vector3D.h"
#include "Point3D.h"
namespace Lina{namespace Math{
	class Segment{
		public:
			Point3D p0;
			Point3D p1;
		public:
			Segment() = default;
			Segment(const Point3D& p0, const Point3D& p1);
			Segment(float length, const Point3D& startPoint, const Vector3D& direction);
			Segment(const Point3D& startPoint, const Vector3D& direction);
			float length() const;
			float squaredLength() const;
			Vector3D direction() const;
	};
}}
