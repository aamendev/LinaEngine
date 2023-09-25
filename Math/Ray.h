#pragma once
#include "Point3D.h"
#include "Vector3D.h"
#include "Line.h"
namespace Lina{ namespace Math{
	class Ray{
		public:
			Point3D base;
			Vector3D direction;
		public:
			Ray() = default;
			/**
			 * @brief      Constructs a ray with base point p pointing in direction
			 *             of v
			 *
			 * @param[in]  point      base point
			 * @param[in]  direction  vector indicating direction
			 */
			Ray(const Point3D& p, const Vector3D& v);
			/**
			 * @brief      finds minimum distance to a point
			 *
			 * @param[in]  p     the point
			 *
			 * @return     The perpendicular distance of the line if p is
			 *               in front of the base point, the base point otherwise
			 */
			float distance(const Point3D& p) const;
	};
}}
