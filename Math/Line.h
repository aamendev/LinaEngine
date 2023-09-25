#pragma once
#include "Vector3D.h"
#include "Point3D.h"
namespace Lina{ namespace Math{
	class Line{
		public:
			/**
			 * @brief      direction vector
			 */
			Vector3D direction;
			/**
			 * @brief      moment vector
			 */
			Vector3D moment;
		public:
			/**
			 * @brief      line default constructor
			 */
			Line() = default;
			/**
			 * @brief      constructor with 6 floats, the first three for direction
			 *             vector, the other three for moment vector
			 *
			 * @param  vx    direction vector x component
			 * @param  vy    direction vector y component
			 * @param  vz    direction vector z component
			 * @param  mx    moment vector x component
			 * @param  my    moment vector y component
			 * @param  mz    moment vector z component
			 */
			Line(float vx, float vy, float vz, float mx, float my, float mz);
			/**
			 * @brief      constructor with two vectors, direction vector
			 *             and moment vector
			 *
			 * @param  v     direction vector
			 * @param  m     moment vector
			 */
			Line(const Vector3D& v, const Vector3D& m);
			/**
			 * @brief      constructor with a point and direction vector. The
			 *             moment vector is the cross product of p and v
			 *
			 * @param  p     base point
			 * @param  v     direction vector
			 */
			Line(const Point3D& p, const Vector3D& v);
			/**
			 * @brief      constructor treating p as a vector for direction. Moment is
			 *             a 0 vector
			 *
			 * @param  p     base point as-vector
			 */
			Line(const Point3D& p);
			/**
			 * @brief      find the minimum distance between the current line and a
			 *             reference line.
			 *
			 * @param  l     reference line
			 *
			 * @return     a float distance
			 */
			float distance(const Line& l);
			/**
			 * @brief      find the minimum distance between the current line and
			 *             a reference point
			 *
			 * @param  p     reference point
			 *
			 * @return     a float distance
			 */
			float distance(const Point3D& p);
	};
}}
