#include "../Quatrenion.h"
#include <cmath>
#include <iostream>
#include <ios>
namespace Lina{ namespace Math{
	Quatrenion::Quatrenion(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
	Quatrenion::Quatrenion(const Vector3D& v, float w)
	:x(v.x), y(v.y), z(v.z), w(w) {}
	const Vector3D& Quatrenion::getVector() const{
		return reinterpret_cast<const Vector3D&> (x);
	}
	Quatrenion operator*(const Quatrenion& q0, const Quatrenion& q1){
		return Quatrenion(
			q0.x * q1.w + q0.y * q1.z - q0.z * q1.y + q0.w * q1.x,
			q0.y * q1.w + q0.z * q1.x + q0.w * q1.y - q0.x * q1.z,
			q0.z * q1.w + q0.w * q1.z + q0.x * q1.y - q0.y * q1.x,
			q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z
			);
	}
	float Quatrenion::magnitude() const{
		return sqrt(x * x + y * y + z * z + w * w);
	}
	float Quatrenion::squaredMagnitude() const{
		return x * x + y * y + z * z + w * w;
	}
	Quatrenion Quatrenion::normalise() const{
		return *this / this->magnitude();
	}

	Matrix3D Quatrenion::getRotationMatrix() const{
		Quatrenion q = this->normalise();
		float x2 = q.x*q.x;
		float xy = q.x*q.y;
		float xz = q.x*q.z;
		float xw = q.x*q.w;
		float y2 = q.y*q.y;
		float yz = q.y*q.z;
		float yw = q.y*q.w;
		float z2 = q.z*q.z;
		float zw = q.z*q.w;

		return Matrix3D(
			1 - 2 * y2 - 2 * z2, 2 * (xy - zw), 2 * (xz + yw),
			2 * (xy + zw), 1 - 2 * x2 - 2 * z2, 2 * (yz - xw),
			2 * (xz - yw), 2 * (yz + xw), 1 - 2 * x2 - 2 * y2
			);
	}
	Quatrenion Quatrenion::conjugate() const{
		return Quatrenion(-this->getVector(), this->w);
	}
	Quatrenion Quatrenion::inverse() const{
		return this->conjugate() / this->squaredMagnitude();
	}
	float Quatrenion::dot(const Quatrenion& q) const{
		return x * q.x+ y * q.y+ z * q.z+ w * q.w;
	}
	float Quatrenion::theta(const Quatrenion& q) const{
		return acos(this->normalise().dot(q.normalise()));
	}

    Quatrenion angleToQuat(EulerAngles euler)
    {
        double cr = cos(euler.x * 0.5);
        double sr = sin(euler.x * 0.5);
        double cp = cos(euler.y * 0.5);
        double sp = sin(euler.y * 0.5);
        double cy = cos(euler.z * 0.5);
        double sy = sin(euler.z * 0.5);

        Quatrenion q;
        q.w = cr * cp * cy + sr * sp * sy;
        q.x = sr * cp * cy - cr * sp * sy;
        q.y = cr * sp * cy + sr * cp * sy;
        q.z = cr * cp * sy - sr * sp * cy;

        return q;
    }
    EulerAngles Quatrenion::toAngles() const
    {
        float PI = 3.141592653f;
        Quatrenion q = normalise();
        EulerAngles euler;
        euler.x = std::atan2(2 * (q.w * q.x + q.y * q.z), 1 - 2 * (q.x * q.x + q.y * q.y));
        double temp  = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
        double temp2 = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
        euler.y = std::atan2(temp, temp2);
        euler.z = std::atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z));
        return euler;
    }
	std::ostream& operator<<(std::ostream& os, const Quatrenion& q){
		os << std::fixed<<"(" << q.x<< ", " << q.y<< ", "<< q.z<< ", "<< q.w<< ")";
		return os;
	}
}}
