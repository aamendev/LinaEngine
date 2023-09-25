#include "../Matrix3D.h"
#include <iostream>
#include <iomanip>
#include <ios>
#include <cmath>
namespace Lina{ namespace Math{
	Matrix3D::Matrix3D(float n00, float n01, float n02,
		float n10, float n11, float n12,
		float n20, float n21, float n22){
		n[0][0] = n00; n[0][1] = n01; n[0][2] = n02;
		n[1][0] = n10; n[1][1] = n11; n[1][2] = n12;
		n[2][0] = n20; n[2][1] = n21; n[2][2] = n22;
	}

	Matrix3D::Matrix3D(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2){
		n[0][0] = v0.x; n[0][1] = v0.y; n[0][2] = v0.z;
		n[1][0] = v1.x; n[1][1] = v1.y; n[1][2] = v1.z;
		n[2][0] = v2.x; n[2][1] = v2.y; n[2][2] = v2.z;
	}
	float& Matrix3D::operator()(int i, int j){

		return n.at(j).at(i);
	}
	float Matrix3D::atPos(int i, int j){
		return n.at(j).at(i);
	}
	const float Matrix3D::atPos(int i, int j) const{
		return n.at(j).at(i);
	}
	const float& Matrix3D::operator()(int i, int j) const{
		return n.at(j).at(i);
	}
	Vector3D& Matrix3D::operator[](int j){
		return *reinterpret_cast<Vector3D *> (&n.at(j));
	}
	const Vector3D& Matrix3D::operator[](int j) const{
		return *reinterpret_cast<const Vector3D *> (&n.at(j));
	}
	Matrix3D operator*(const Matrix3D& m0, const Matrix3D& m1){
		return (Matrix3D(
			m0(0, 0) * m1(0 , 0) + m0(0, 1) * m1(1 , 0) + m0(0, 2) * m1(2 , 0),
			m0(0, 0) * m1(0 , 1) + m0(0, 1) * m1(1 , 1) + m0(0, 2) * m1(2 , 1),
			m0(0, 0) * m1(0 , 2) + m0(0, 1) * m1(1 , 2) + m0(0, 2) * m1(2 , 2),
			m0(1, 0) * m1(0 , 0) + m0(1, 1) * m1(1 , 0) + m0(1, 2) * m1(2 , 0),
			m0(1, 0) * m1(0 , 1) + m0(1, 1) * m1(1 , 1) + m0(1, 2) * m1(2 , 1),
			m0(1, 0) * m1(0 , 2) + m0(1, 1) * m1(1 , 2) + m0(1, 2) * m1(2 , 2),
			m0(2, 0) * m1(0 , 0) + m0(2, 1) * m1(1 , 0) + m0(2, 2) * m1(2 , 0),
			m0(2, 0) * m1(0 , 1) + m0(2, 1) * m1(1 , 1) + m0(2, 2) * m1(2 , 1),
			m0(2, 0) * m1(0 , 2) + m0(2, 1) * m1(1 , 2) + m0(2, 2) * m1(2 , 2)
			)
		);
	}
	Vector3D operator *(const Matrix3D& m, const Vector3D& v){
		return (Vector3D(
			m(0 , 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
			m(1 , 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
			m(2 , 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z
			)
		);
	}
	Matrix3D operator*(const Matrix3D& m, float s){
		return Matrix3D(
			m[0] * s, m[1] * s, m[2] * s
			);
	}
	std::ostream& operator<<(std::ostream& os, const Matrix3D& m){
		os << std::setprecision(4)<<std::fixed<<"[" << m[0].x<< ", "<< m[0].y << ", "<< m[0].z << "\n "
		<< m[1].x<< ", "<< m[1].y << ", "<< m[1].z << "\n "
		<< m[2].x<< ", "<< m[2].y << ", "<< m[2].z << "]";

		return os;
	}
	float Matrix3D::determinant() const{
		return atPos(0,0) * (atPos(1,1) * atPos(2,2) - atPos(1,2) * atPos(2,1))
		+ atPos(0, 1) * (atPos(1,2) * atPos(2,0) - atPos(1,0) * atPos(2,2))
		+ atPos(0, 2) * (atPos(1,0) * atPos(2,1) - atPos(1,1) * atPos(2,0));
	}

	const Matrix3D Matrix3D::inverse() const{
		const Vector3D& v0 = *reinterpret_cast<const Vector3D *>(&n.at(0));
		const Vector3D& v1 = *reinterpret_cast<const Vector3D *>(&n.at(1));
		const Vector3D& v2 = *reinterpret_cast<const Vector3D *>(&n.at(2));
		Vector3D r0 = v1.cross(v2);
		Vector3D r1 = v2.cross(v0);
		Vector3D r2 = v0.cross(v1);
		float invDet = 1 / r2.dot(v2);
		return Matrix3D(
			r0.x *invDet, r1.x * invDet, r2.x * invDet,
			r0.y *invDet, r1.y * invDet, r2.y * invDet,
			r0.z *invDet, r1.z * invDet, r2.z * invDet
			);
	}
	const Matrix3D Matrix3D::adjugate() const{
		return this->inverse() * this->determinant();
	}
}}
