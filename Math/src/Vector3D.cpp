#include "../Vector3D.h"
#include "../Quatrenion.h"
#include "../Matrix3D.h"
#include "../Utilities.h"
#include "../Transform4D.h"
#include <cmath>
#include <tuple>
#include <iostream>
namespace Lina{ namespace Math{
	Vector3D::Vector3D(float x, float y, float z): x(x), y(y), z(z) {}

	Vector3D& Vector3D::operator *=(float s){
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	Vector3D& Vector3D::operator /=(float s){
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	Vector3D& Vector3D::operator +=(const Vector3D& v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3D& Vector3D::operator -=(const Vector3D& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	std::ostream& operator<<(std::ostream& os, const Vector3D& v){
		os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}
	Vector3D Vector3D::operator*(const Matrix3D& m){
		return Vector3D(this->dot(m[0]), this->dot(m[1]), this->dot(m[2]));
	}
	Vector3D Vector3D::rotate(float theta, const Vector3D& axis){
		return *this * Util::rotationMatrix(theta, axis);
	}
	Vector3D Vector3D::reflect(const Vector3D& axis){
		return *this * Util::reflectionMatrix(axis);
	}
	Vector3D Vector3D::involute(const Vector3D& axis){
		return *this * Util::involutionMatrix(axis);
	}
	Vector3D Vector3D::scale(float s, const Vector3D& axis){
		return *this * Util::scaleMatrix(s, axis);
	}
	Vector3D Vector3D::skew(float theta, const Vector3D& vector0, const Vector3D& vector1){
		return *this * Util::skewMatrix(theta, vector0, vector1);
	}
	Vector3D Vector3D::rotateQuatrenion(const Quatrenion& quat){
		const Quatrenion q = quat.normalise();
		const Vector3D& b = q.getVector();
		float b2 = b.x * b.x + b.y * b.y + b.z * b.z;
		return *this * (q.w * q.w - b2) + b * (this->dot(b) * 2)
		+ b.cross(*this) * (q.w * 2);
	}
	Vector3D operator*(const Vector3D& n, const Transform4D& h){
		return Vector3D(
			n.x * h(0, 0) + n.y * h(1, 0) + n.z * h(2, 0),
			n.x * h(0, 1) + n.y * h(1, 1) + n.z * h(2, 1),
			n.x * h(0, 2) + n.y * h(1, 2) + n.z * h(2, 2)
			);
	}
	const Point3D Vector3D::toPoint() const{
		return Point3D(x, y, z);
	}
	std::tuple<Vector3D, Vector3D, Vector3D>
	Vector3D::constructOrthonormal(const Vector3D& v1){
		Vector3D v = this->normalise();
		if (v.cross(v1).magnitude() == 0) throw std::invalid_argument
			("Vector is parallel with first argument");
		Vector3D v_ = v.cross(v1).normalise();
		return {v, v_, v_.cross(v)};
	}

	bool Vector3D::isParallel(const Vector3D& v) const{
		return this->dot(v) * this->dot(v)
		== this->squaredMagnitude() * v.squaredMagnitude();
	}
	bool Vector3D::isAntiParallel(const Vector3D& v) const{
		return this->dot(v) == - this->magnitude() * v.magnitude();
	}
	bool Vector3D::isPerpendicular(const Vector3D& v) const{
		return this->dot(v) == 0;
	}
	bool Vector3D::sameDirection(const Vector3D& v) const{
		return this->dot(v) > 0;
	}
	bool Vector3D::oppositeDirection(const Vector3D& v) const{
		return this->dot(v) < 0;
	}




}}
