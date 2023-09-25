#pragma once
#include <array>
#include "Vector3D.h"
#include <iostream>
namespace Lina{ namespace Math{
	class Matrix3D{
	private:
		std::array<std::array<float, 3>, 3 > n;
		// float n[3][3];
	public:
		Matrix3D() = default;
		Matrix3D(float n00, float n01, float n02,
			float n10, float n11, float n12,
			float n20, float n21, float n22);
		Matrix3D (const Vector3D& v0, const Vector3D& v1, const Vector3D& v2);
		float& operator ()(int i, int j);
		const float& operator ()(int i, int j) const;
		Vector3D& operator [](int j);
		const Vector3D& operator[](int j) const;
		friend Matrix3D operator *(const Matrix3D& m0, const Matrix3D& m1);
		friend Vector3D operator *(const Matrix3D& m, const Vector3D& v);
		friend Matrix3D operator *(const Matrix3D& m, float s);
		friend std::ostream& operator<<(std::ostream& os, const Matrix3D& m);
		float determinant() const;
		float atPos(int i, int j);
		const float atPos(int i, int j) const;
		const Matrix3D inverse() const;
		const Matrix3D adjugate() const;
	};
}}
