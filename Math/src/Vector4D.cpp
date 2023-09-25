#include "../Vector4D.h"
#include "../Matrix4D.h"
#include "../Utilities.h"
#include <cmath>
#include <iostream>
namespace Lina{ namespace Math{
	Vector4D::Vector4D(float x, float y, float z, float w): x(x), y(y), z(z),w(w) {}

	Vector4D& Vector4D::operator *=(float s){
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	Vector4D& Vector4D::operator /=(float s){
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}
	Vector4D& Vector4D::operator +=(const Vector4D& v){
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	Vector4D& Vector4D::operator -=(const Vector4D& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	std::ostream& operator<<(std::ostream& os, const Vector4D& v){
		os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w<< ")";
		return os;
	}
	Vector4D Vector4D::operator*(const Matrix4D& m){
		return Vector4D(this->Dot(m[0]), this->Dot(m[1]),
			this->Dot(m[2]), this->Dot(m[3]));
	}
// Vector4D Vector4D::Rotate(float theta, const Vector4D& axis){
// 	return *this * MathUtil::rotationMatrix(theta, axis);
// }
// Vector4D Vector4D::Reflect(const Vector4D& axis){
// 	return *this * MathUtil::reflectionMatrix(axis);
// }
// Vector4D Vector4D::Involute(const Vector4D& axis){
// 	return *this * MathUtil::involutionMatrix(axis);
// }
// Vector4D Vector4D::Scale(float s, const Vector4D& axis){
// 	return *this * MathUtil::scaleMatrix(s, axis);
// }
// Vector4D Vector4D::Skew(float theta, const Vector4D& vector0, const Vector4D& vector1){
// 	return *this * MathUtil::skewMatrix(theta, vector0, vector1);
// }
}}
