#pragma once
#include "Matrix.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Plane.hpp"
#include "Transform4D.hpp"
#include "Line.hpp"
#include "Quatrenion.hpp"
#include <utility>
#include <iostream>	
namespace Lina{
	namespace MathUtil{

	/**
	 * @brief      creates a rotation Matrix to rotate theta radians around axis
	 *
	 * @param  theta  the angle of rotation
	 * @param  axis   The rotation axis
	 *
	 * @return     A 3D Matrix representaion of the Rotation
	 */
		Matrix3D rotationMatrix(float theta, const Vector3D& axis);
	/**
	 * @brief      Creates a 3D Matrix to reflect about axis
	 *
	 * @param  axis  The reflection axis
	 *
	 * @return     A 3D Matrix representing the Reflection
	 */
		Matrix3D reflectionMatrix(const Vector3D& axis);
	/**
	 * @brief      Constructs the identity matrix
	 *
	 * @return     A 3D identity Matrix
	 */
		Matrix3D identityMatrix();
	/**
	 * @brief      Creates a Matrix for involution about a given axis
	 *
	 * @param  axis  The involution axis
	 *
	 * @return     A 3D Involution Matrix
	 */
		Matrix3D involutionMatrix(const Vector3D& axis);
	/**
	 * @brief      Creates a Sclaing matrix representing a scaling by a factor
	 *             of s in a given direction
	 *
	 * @param  s     the scaling factor
	 * @param  axis  The scaling direction
	 *
	 * @return     A 3D Matrix representing the Scaling
	 */
		Matrix3D scaleMatrix(float s, const Vector3D& axis);
		Matrix3D skewMatrix(float theta, const Vector3D& v0, 
			const Vector3D& v1);
		Transform4D zUp();
		Transform4D yUp();
	/**
	 * @brief      Creates the x-axis
	 *
	 * @return     A unit vector pointing in the x-axis direction
	 */
		Vector3D xAxis();
	/**
	 * @brief      Creates the y-axis
	 *
	 * @return     A unit vector pointing in the y-axis direction
	 */
		Vector3D yAxis();
	/**
	 * @brief      Creates the z-axis
	 *
	 * @return     A unit vector pointing in the z-axis
	 */
		Vector3D zAxis();
		Vector3D lerp(const Vector3D& v0, const Vector3D& v1, float beta);

		Plane xyPlane();
		Plane xzPlane();
		Plane yzPlane();

		Transform4D planeReflectionMatrix(const Plane& f);
	/**
	 * @brief      Creates a translation Matrix
	 *
	 * @param  v     Translation vector
	 *
	 * @return     A 4x4 Matrix that translates a point by V on multiplication
	 */
		Transform4D translationMatrix(const Vector3D& translate);
	/**
	 * @brief      Creates a matrix that scales a vector on multiplication
	 *
	 * @param  scale  scaling vector
	 *
	 * @return     A 4D Matrix that scales a Point/Vector on multiplication
	 */
		Transform4D scaleMatrix(const Vector3D& scale);
		Transform4D transMatrix(const Matrix3D& transform,const Vector3D& translate);


		Line connectOrigin(const Point3D& p);

		Quatrenion lerp(const Quatrenion& q1, const Quatrenion& q2, float beta);
		Quatrenion slerp(const Quatrenion& q1, const Quatrenion& q2, float beta);

		std::pair<Quatrenion, Quatrenion> dualQuatrenion(const Quatrenion& q0, const Quatrenion& q1); 

		float distance(const Point3D& q, const Point3D& p, const Vector3D& v);
		float distance(const Point3D& p0, const Vector3D& v0,
			const Point3D& p1, const Vector3D& v1);
	}
}