#pragma once
#include <cmath>
#include <iostream>
namespace Lina{ namespace Math{
	class Matrix4D;
	class Vector4D{
	public:
		float x;
		float y;
		float z;
		float w;
	public:
		Vector4D() = default;
		Vector4D(float x, float y, float z, float w);
		Vector4D& operator *=(float s);
		Vector4D& operator /=(float s);
		inline Vector4D operator -();
		inline float Magnitude() const;
		inline Vector4D Normalise() const;
		friend inline Vector4D operator *(const Vector4D& v, float s);
		friend inline Vector4D operator /(const Vector4D& v, float s);
		Vector4D& operator +=(const Vector4D& v);
		Vector4D& operator -=(const Vector4D& v);
		friend inline Vector4D operator +(const Vector4D& v0, const Vector4D& v1);
		friend inline Vector4D operator -(const Vector4D& v0, const Vector4D& v1);
		inline float Dot(const Vector4D& v) const;
		float Theta(const Vector4D& v) const;
		inline Vector4D Project(const Vector4D& v);
		inline Vector4D Reject(const Vector4D& v);
		friend std::ostream& operator<<(std::ostream& os, const Vector4D& v);
		Vector4D operator*(const Matrix4D& m);
		// Vector4D Rotate(float theta, const Vector4D& axis);
		// Vector4D Reflect(const Vector4D& axis);
		// Vector4D Involute(const Vector4D& axis);
		// Vector4D Scale(float s, const Vector4D& axis);
		// Vector4D Skew(float theta, const Vector4D& vector0, const Vector4D& vector1);
	};

	inline Vector4D operator *(const Vector4D& v, float s){
		return Vector4D(v.x * s, v.y * s, v.z *s, v.w * s);
	}
	inline Vector4D operator /(const Vector4D& v, float s){
		return Vector4D(v.x / s, v.y / s, v.z /s, v.w / s);
	}
	inline Vector4D Vector4D::operator -(){
		return Vector4D(-x, -y, -z, -w);
	}

	inline Vector4D Vector4D::Normalise() const{
		return *this / this->Magnitude();
	}
	inline float Vector4D::Magnitude() const{
		return sqrt(x * x + y * y + z * z + w * w);
	}
	inline Vector4D operator +(const Vector4D& v0, const Vector4D& v1){
		return Vector4D(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
	}
	inline Vector4D operator -(const Vector4D& v0, const Vector4D& v1){
		return Vector4D(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
	}
	inline float Vector4D::Dot(const Vector4D& v) const{
		return (x * v.x + y * v.y + z * v.z, w * v.w);
	}
	inline float Vector4D::Theta(const Vector4D& v) const{
		return acos(this->Dot(v) / (this->Magnitude() * v.Magnitude()));
	}
	inline Vector4D Vector4D::Project(const Vector4D& v){
		return v * (this->Dot(v) / v.Dot(v));
	}
	inline Vector4D Vector4D::Reject(const Vector4D& v){
		return (*this - v * (this->Dot(v) / v.Dot(v)));
	}
}}
