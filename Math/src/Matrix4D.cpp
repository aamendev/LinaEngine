#include "../Matrix4D.h"
#include <iostream>
#include <iomanip>
#include <ios>
#include <cmath>
namespace Lina{ namespace Math{
	Matrix4D::Matrix4D(float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23,
		float n30, float n31, float n32, float n33){
		n[0][0] = n00; n[0][1] = n01; n[0][2] = n02; n[0][3] = n03;
		n[1][0] = n10; n[1][1] = n11; n[1][2] = n12; n[1][3] = n13;
		n[2][0] = n20; n[2][1] = n21; n[2][2] = n22; n[2][3] = n23;
		n[3][0] = n30; n[3][1] = n31; n[3][2] = n32; n[3][3] = n33;
	}

	Matrix4D::Matrix4D(const Vector4D& v0, const Vector4D& v1, const Vector4D& v2, const Vector4D& v3){
		n[0][0] = v0.x; n[0][1] = v0.y; n[0][2] = v0.z; n[0][3] = v0.w;
		n[1][0] = v1.x; n[1][1] = v1.y; n[1][2] = v1.z; n[1][3] = v1.w;
		n[2][0] = v2.x; n[2][1] = v2.y; n[2][2] = v2.z; n[2][3] = v2.w;
		n[3][0] = v3.x; n[3][1] = v3.y; n[3][2] = v3.z; n[3][3] = v3.w;
	}
	float& Matrix4D::operator()(int i, int j){

		return n.at(j).at(i);
	}
	float Matrix4D::atPos(int i, int j){
		return n.at(j).at(i);
	}
	const float Matrix4D::atPos(int i, int j) const{
		return n.at(j).at(i);
	}
	const float& Matrix4D::operator()(int i, int j) const{
		return n.at(j).at(i);
	}
	Vector4D& Matrix4D::operator[](int j){
		return *reinterpret_cast<Vector4D *> (&n.at(j));
	}
	const Vector4D& Matrix4D::operator[](int j) const{
		return *reinterpret_cast<const Vector4D *> (&n.at(j));
	}
	Matrix4D operator*(const Matrix4D& m0, const Matrix4D& m1){
		return (Matrix4D(
			m0(0, 0) * m1(0 , 0) + m0(0, 1) * m1(1 , 0) + m0(0, 2) * m1(2 , 0) + m0(0,3) * m1(3, 0),
			m0(0, 0) * m1(0 , 1) + m0(0, 1) * m1(1 , 1) + m0(0, 2) * m1(2 , 1) + m0(0,3) * m1(3, 1),
			m0(0, 0) * m1(0 , 2) + m0(0, 1) * m1(1 , 2) + m0(0, 2) * m1(2 , 2) + m0(0,3) * m1(3, 2),
			m0(0, 0) * m1(0 , 3) + m0(0, 1) * m1(1 , 3) + m0(0, 2) * m1(2 , 3) + m0(0,3) * m1(3, 3),
			m0(1, 0) * m1(0 , 0) + m0(1, 1) * m1(1 , 0) + m0(1, 2) * m1(2 , 0) + m0(1,3) * m1(3, 0),
			m0(1, 0) * m1(0 , 1) + m0(1, 1) * m1(1 , 1) + m0(1, 2) * m1(2 , 1) + m0(1,3) * m1(3, 1),
			m0(1, 0) * m1(0 , 2) + m0(1, 1) * m1(1 , 2) + m0(1, 2) * m1(2 , 2) + m0(1,3) * m1(3, 2),
			m0(1, 0) * m1(0 , 3) + m0(1, 1) * m1(1 , 3) + m0(1, 2) * m1(2 , 3) + m0(1,3) * m1(3, 3),
			m0(2, 0) * m1(0 , 0) + m0(2, 1) * m1(1 , 0) + m0(2, 2) * m1(2 , 0) + m0(2,3) * m1(3, 0),
			m0(2, 0) * m1(0 , 1) + m0(2, 1) * m1(1 , 1) + m0(2, 2) * m1(2 , 1) + m0(2,3) * m1(3, 1),
			m0(2, 0) * m1(0 , 2) + m0(2, 1) * m1(1 , 2) + m0(2, 2) * m1(2 , 2) + m0(2,3) * m1(3, 2),
			m0(2, 0) * m1(0 , 3) + m0(2, 1) * m1(1 , 3) + m0(2, 2) * m1(2 , 3) + m0(2,3) * m1(3, 3),
			m0(3, 0) * m1(0 , 0) + m0(3, 1) * m1(1 , 0) + m0(3, 2) * m1(2 , 0) + m0(3,3) * m1(3, 0),
			m0(3, 0) * m1(0 , 1) + m0(3, 1) * m1(1 , 1) + m0(3, 2) * m1(2 , 1) + m0(3,3) * m1(3, 1),
			m0(3, 0) * m1(0 , 2) + m0(3, 1) * m1(1 , 2) + m0(3, 2) * m1(2 , 2) + m0(3,3) * m1(3, 2),
			m0(3, 0) * m1(0 , 3) + m0(3, 1) * m1(1 , 3) + m0(3, 2) * m1(2 , 3) + m0(3,3) * m1(3, 3)
			)
		);
	}
	std::ostream& operator<<(std::ostream& os, const Matrix4D& m){
		os << std::setprecision(4)<<std::fixed<<"[" << m[0].x<< ", "<< m[0].y << ", "<< m[0].z << "\n "
		<< m[1].x<< ", "<< m[1].y << ", "<< m[1].z << "\n "
		<< m[2].x<< ", "<< m[2].y << ", "<< m[2].z << "\n "
		<< m[3].x<< ", "<< m[3].y << ", "<< m[3].z << "]";

		return os;
	}
}}
