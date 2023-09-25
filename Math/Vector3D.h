#pragma once
#include <cmath>
#include <iostream>
#include <tuple>
namespace Lina{ namespace Math{
	class Matrix3D;
	class Quatrenion;
	class Transform4D;
	class Point3D;
	class Vector3D{
	public:
		float x;
		float y;
		float z;
	public:
		Vector3D() = default;
		/**
		 * @brief      constrcts a vector from 3 floats
		 *
		 * @param  x     first coordinate
		 * @param  y      second coordinate
		 * @param  z      third coordinate
		 */
		Vector3D(float x, float y, float z);

		/**
		 * @brief      Scales the Vector by factor of s
		 *
		 * @param  s     scaling factor: a float
		 *
		 * @return     The scaled vector
		 */
		Vector3D& operator *=(float s);
		/**
		 * @brief      scales the Vector by a factor of 1 / s
		 *
		 * @param  s     inverse of scaling factor
		 *
		 * @return     The scaled vector
		 */
		Vector3D& operator /=(float s);
		/**
		 * @brief      Negation operator
		 *
		 * @return     Same vector in opossite direction
		 */
		inline Vector3D operator -() const;
		/**
		 * @brief      Calculates the magnitude of the vector
		 *
		 * @return     returns the magnitude of vector as float
		 */
		inline float magnitude() const;

		/**
		 * @brief      Calculates the square of the magnitude of vector.
		 *             This function is provided for efficiency
		 *
		 * @return     a float represented the squared magnitude.
		 */
		inline float squaredMagnitude() const;

		/**
		 * @brief      Scales the vector so it has magnitude of 1
		 *
		 * @return     the normalised vector
		 */
		inline Vector3D normalise() const;
		friend inline Vector3D operator *(const Vector3D& v, float s);
		/**
		 * @brief      Multiplication version with 3D matrix
		 *
		 * @param  m     a const reference to the matrix
		 *
		 * @return     A 3D vector with components equal to dot product with each row in the matrix
		 */
		Vector3D operator *(const Matrix3D& m);
		friend Vector3D operator*(const Vector3D& n, const Transform4D& h );
		friend inline Vector3D operator /(const Vector3D& v, float s);
		/**
		 * @brief      Adds two vectors component wise
		 *
		 * @param  v     a const reference to the vector to add to current vector
		 *
		 * @return     a reference to the updated vector
		 */
		Vector3D& operator +=(const Vector3D& v);
		/**
		 * @brief      Subtracts two vectors component wise
		 *
		 * @param  v     a const reference to the vector to subtract
		 *
		 * @return     a reference to the updated vector
		 */
		Vector3D& operator -=(const Vector3D& v);
		friend inline Vector3D operator +(const Vector3D& v0, const Vector3D& v1);
		friend inline Vector3D operator -(const Vector3D& v0, const Vector3D& v1);
		/**
		 * @brief      computes the dot product of two vectors
		 *
		 * @param  v     a const referencethe vector to compute the dot product with
		 *
		 * @return     a float with value equal to the dot product of the two vectors
		 */
		inline float dot(const Vector3D& v) const;
		/**
		 * @brief      Finds the angle between two vectors
		 *
		 * @param  v     a const reference the vector to find the angle with
		 *
		 * @return     a float representing the angle in radians
		 */
		float theta(const Vector3D& v) const;
		/**
		 * @brief      calculates the cross product between two vectors
		 *
		 * @param  v     a const reference to the second vector
		 *
		 * @return     a 3D vector equivalent to the current vector crossed with the parameter vector
		 */
		inline Vector3D cross(const Vector3D& v) const;
		/**
		 * @brief      returns the projects of the current vector on the parameter vector
		 *
		 * @param  v     a const reference to the vector to be projected on
		 *
		 * @return     a 3d vector equal to the projection of the current vector on the parameter vector
		 */
		inline Vector3D project(const Vector3D& v);
		inline Vector3D reject(const Vector3D& v);
		friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
		/**
		 * @brief      Rotates a vector with a given amount around a given axis
		 *
		 * @param  theta  the angle to rotate with in radians
		 * @param  axis   The axis to rotate around
		 *
		 * @return     A new 3D vector equal to the rotation of the current around the parameter vector with angle theta
		 */
		Vector3D rotate(float theta, const Vector3D& axis);
		/**
		 * @brief      rotates a vector
		 *
		 * @param  q     a const reference quatrention to rotate based on
		 *
		 * @return     a new 3d Vector resulting from the rotation of the current vector with Quaterenion q
		 */
		Vector3D rotateQuatrenion(const Quatrenion& q);
		/**
		 * @brief      Reflects a vector aroud a given axis
		 *
		 * @param  axis  The axis to reflect on
		 *
		 * @return     a new 3d vector resulting from
		 *  the reflection of the current one on the parameter vector
		 */
		Vector3D reflect(const Vector3D& axis);
		/**
		 * @brief      Involutes a vector (a genaralization of
		 *  reflection)
		 *
		 * @param  axis  The axis to involute on
		 *
		 * @return     a new 3d vector resulting from
		 *  involuting the current vector about the parameter vector
		 */
		Vector3D involute(const Vector3D& axis);
		/**
		 * @brief      scales a vector with a factor in a given axis
		 *
		 * @param  s     the scaling factor
		 * @param  axis  the direction to scale parallel to
		 *
		 * @return     a new 3d vector resulting from the
		 *  scaling of the current vector by a factor of s in the axis direction
		 */
		Vector3D scale(float s, const Vector3D& axis);
		/**
		 * @brief      Skews a vector in a given direction with a given angle
		 *             to its perpendicular direction. The two vectors provided
		 *             should be Perpendicular to each other
		 *
		 * @param  theta    The angle with the normal parameter
		 * @param  vector0  const reference to a vector representing skew direction.
		 * @param  vector1  The normal to skew direction vector
		 *
		 * @return     Returns a 3d vector resulting from skewing the current
		 *                     vector in vector0 direction with angle theta with
		 *                     vector1
		 */
		Vector3D skew(float theta, const Vector3D& vector0, const Vector3D& vector1);
		/**
		 * @brief      Converts the Vector3d structure to Point structure
		 *
		 * @return     Point representation of the current vector.
		 */
		const Point3D toPoint() const;
		/**
		 * @brief      Constructs orthonormal basis from the current vector and
		 *             the parameter vector
		 *
		 * @param  v1    Second vector to construct the orthonormal triplet with
		 *
		 * @return     A tuple of 3 orthonormal normalised vectors
		 */
		std::tuple<Vector3D, Vector3D, Vector3D>
		constructOrthonormal(const Vector3D& v1);

		 /**
		  * @brief      checks if the current and parameter vectors are parallel
		  *
		  * @param  v     const reference to parameter vector
		  *
		  * @return     True if the specified v is parallel to current vector,
		  *                  False otherwise.
		  */
		bool isParallel(const Vector3D& v) const;
		 /**
		  * @brief      Determines whether the specified v is anti parallel with
		  *             the current vector
		  *
		  * @param[in]  v     parameter vector
		  *
		  * @return     True if the specified v is anti parallel to current vector
		  *                  , False otherwise.
		  */
		bool isAntiParallel(const Vector3D& v) const;
		 /**
		  * @brief      Determines whether the specified v is perpendicular to the
		  *             current vector
		  *
		  * @param  v     parameter vector
		  *
		  * @return     True if the parameter vector and the current vector
		  *                  are perpendicular, False otherwise.
		  */
		bool isPerpendicular(const Vector3D& v) const;
		 /**
		  * @brief      checks if the angle between the current Vector
		  *             and the parameter vector is acute
		  *
		  * @param  v     parameter vector
		  *
		  * @return     True if the angle is less than 90, False otherwise
		  */
		bool sameDirection(const Vector3D& v) const;
		 /**
		  * @brief      checks if the angle between the current Vector
		  *             and the parameter vector is obtuse
		  *
		  * @param[in]  v     parameter vector
		  *
		  * @return     True if the angle is greater than 90, False otherwise
		  */
		bool oppositeDirection(const Vector3D& v) const;
	};

/**
 * @brief      version of multiplication between vector and scalar
 *
 * @param  v     vector; must be lefthand operand
 * @param  s     scalar; must be righthand operand
 *
 * @return     A new Vector with components (s * x, s * y, s * z)
 */
	inline Vector3D operator *(const Vector3D& v, float s){
		return Vector3D(v.x * s, v.y * s, v.z *s);
	}
/**
 * @brief      version of division between vector and scalar
 *
 * @param  v     vector; must be lefthand operand
 * @param  s     scalar; must be righthand operand
 *
 * @return     A new Vector with components (x / s, y / s, z / s)
 */
	inline Vector3D operator /(const Vector3D& v, float s){
		return Vector3D(v.x / s, v.y / s, v.z /s);
	}
	inline Vector3D Vector3D::operator -() const{
		return Vector3D(-x, -y, -z);
	}

	inline Vector3D Vector3D::normalise() const{
		return *this / this->magnitude();
	}
	inline float Vector3D::magnitude() const{
		return sqrt(x * x + y * y + z * z);
	}
	inline float Vector3D::squaredMagnitude() const{
		return (x * x + y * y + z *z);
	}

	inline Vector3D operator +(const Vector3D& v0, const Vector3D& v1){
		return Vector3D(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
	}
	inline Vector3D operator -(const Vector3D& v0, const Vector3D& v1){
		return Vector3D(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
	}
	inline float Vector3D::dot(const Vector3D& v) const{
		return (x * v.x + y * v.y + z * v.z);
	}
	inline float Vector3D::theta(const Vector3D& v) const{
		return acos(this->dot(v) / (this->magnitude() * v.magnitude()));
	}
	inline Vector3D Vector3D::cross(const Vector3D& v) const {
		return Vector3D(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
			);
	}
	inline Vector3D Vector3D::project(const Vector3D& v){
		return v * (this->dot(v) / v.dot(v));
	}
	inline Vector3D Vector3D::reject(const Vector3D& v){
		return (*this - v * (this->dot(v) / v.dot(v)));
	}
}}
