#pragma once
#include "Point3D.hpp"
#include "segment.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
namespace Lina{
	class AABB{
		public:
			Point3D min;
			Point3D max;
		public:
			AABB() = default;
			/**
			 * @brief      Creates an AABB with a minimum and maximum points
			 *
			 * @param[in]  min   minimum point
			 * @param[in]  max   maximum point
			 */
			AABB(const Point3D& min, const Point3D& max);
			/**
			 * @brief      Creates an AABB with a minimum point and maximum
			 *             point with coordinates (xmin, ymin, zmin) and
			 *              (xmax, ymax, zmax) respectively
			 *
			 * @param[in]  xmin  x component of minimum point
			 * @param[in]  ymin  y component of minimum point
			 * @param[in]  zmin  z component of minimum point
			 * @param[in]  xmax  x component of maximum point
			 * @param[in]  ymax  y component of maximum point
			 * @param[in]  zmax  z component of maximum point
			 */
			AABB(float xmin, float ymin, float zmin, float xmax,
				 float ymax, float zmax);

			/**
			 * @brief      Calculates the squared distance from the box to a point
			 *
			 * @param[in]  p     A reference to the point
			 *
			 * @return     the squared distance
			 */
			float squaredDistance(const Point3D& p);
			/**
			 * @brief      Creates and AABB from a center point with a given width
			 *
			 * @param[in]  center  The center
			 * @param[in]  width   The width
			 */
			AABB(const Point3D& center, float width);
			/**
			 * @brief      calculated the squared distance to a point
			 *
			 * @param[in]  p     The point
			 * 
			 * @return     a float number equal to the distance
			 */
			float squaredDistance(const Point3D& p) const;
			/**
			 * @brief      Checks if a segment passess throught the box
			 *
			 * @param[in]  s     A const reference to the segment
			 *
			 * @return     True if they intersect, False otherwise
			 */
			bool intersects(const Segment& s) const;
			/**
			 * @brief      Checks if a plane passess throught the box
			 *
			 * @param[in]  s     A const reference to the plane
			 *
			 * @return     True if they intersect, False otherwise
			 */
			bool intersects(const Plane& p) const;
			/**
			 * @brief      Checks if a sphere passess throught the box
			 *
			 * @param[in]  s     A const reference to the sphere
			 *
			 * @return     True if they intersect, False otherwise
			 */
			bool intersects(const Sphere& S) const;
			/**
			 * @brief      Checks if a sphere passess throught the box
			 *
			 * @param[in]  s     A const reference to the sphere
			 *
			 * @return     True if they intersect, False otherwise
			 */
			bool intersects(const AABB& b) const;

	};
}