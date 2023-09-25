#pragma once
#include "Point3D.h"
#include "Vector4D.h"
#include "Ray.h"
namespace Lina{ namespace Math{
	class Sphere{
		public:
			Point3D centre;
			float radius;
		public:
			Sphere() = default;
			/**
			 * @brief      Creates a sphere with a given radius and centre
			 *
			 * @param  centre  The centre
			 * @param  radius  The radius
			 */
			Sphere(const Point3D& centre, float radius);
			/**
			 * @brief      Sets the centre.
			 *
			 * @param  centre  The centre
			 */
			void setCentre(const Point3D& centre);
			/**
			 * @brief      Sets the radius.
			 *
			 * @param  radius  The radius
			 */
			void setRadius(float radius);
			/**
			 * @brief      Creates a 4D vector represention of the circle
			 *             (Cx, Cy, Cz, r)
			 *
			 * @return     A 4D vector reprsenting the circle
			 */
			Vector4D vectorRep() const;
			/**
			 * @brief      Determines if the current sphere intersects with
			 *             parameter sphere
			 *
			 * @param  S    parameter sphere
			 *
			 * @return     True if they intersect, False otherwise
			 */
			bool intersects(const Sphere& S) const;
			/**
			 * @brief      Determines if the current sphere intersects with
			 *             a ray or not
			 *
			 * @param  r    the ray
			 *
			 * @return     True if they intersect, False otherwise
			 */
			bool intersects(const Ray& r) const;
	};
}}
