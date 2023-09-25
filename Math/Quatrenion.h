#pragma once
#include "Vector3D.h"
#include "Matrix3D.h"
#include <iostream>
namespace Lina{ namespace Math{
    struct EulerAngles
    {
        float x, y, z;
    };
	class Quatrenion{
	public:
		float x, y, z, w;
	public:
		Quatrenion() = default;
		Quatrenion(float x, float y, float z, float w);
		Quatrenion(const Vector3D& v, float w);
		const Vector3D& getVector() const;
		friend Quatrenion operator*(const Quatrenion& q0,
			const Quatrenion& q1);
		friend inline Quatrenion operator+(const Quatrenion& q0, const Quatrenion& q1);
		float magnitude() const;
		float squaredMagnitude() const;
		Quatrenion normalise() const;
		friend inline Quatrenion operator*(const Quatrenion& q0, float s);
		friend inline Quatrenion operator/(const Quatrenion& q0, float s);
		Matrix3D getRotationMatrix() const;
		void setRotationMatrix(const Matrix3D& m) = delete;
		Quatrenion conjugate() const;
		Quatrenion inverse() const;
		friend std::ostream& operator<<(std::ostream& os, const Quatrenion& q);
		float theta(const Quatrenion& q) const;
		float dot(const Quatrenion& q) const;
        EulerAngles toAngles() const;
        friend Quatrenion angleToQuat(EulerAngles euler);
	};
	inline Quatrenion operator*(const Quatrenion& q0, float s){
		return Quatrenion(q0.x * s, q0.y * s, q0.z * s, q0.w * s);
	}
	inline Quatrenion operator/(const Quatrenion& q0, float s){
		return Quatrenion(q0.x / s, q0.y / s, q0.z / s, q0.w / s);
	}
	inline Quatrenion operator+(const Quatrenion& q0, const Quatrenion& q1){
		return Quatrenion(q0.getVector() + q1.getVector(), q0.w + q1.w);
	}
}}
