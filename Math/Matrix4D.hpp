#pragma once
#include <array>
#include "Vector4D.hpp"
#include <iostream>
namespace Lina{
	class Matrix4D{
	protected:
		std::array<std::array<float, 4>, 4 > n;
		// float n[3][3];
	public:
		Matrix4D() = default;
		Matrix4D(float n00, float n01, float n02, float n03,
			float n10, float n11, float n12, float n13,
			float n20, float n21, float n22, float n23,
			float n30, float n31, float n32, float n33);
		Matrix4D (const Vector4D& v0, const Vector4D& v1, const Vector4D& v2, const Vector4D& v3);
		float& operator ()(int i, int j);
		const float& operator ()(int i, int j) const;
		Vector4D& operator [](int j);
		const Vector4D& operator[](int j) const;
		friend Matrix4D operator *(const Matrix4D& m0, const Matrix4D& m1);
		friend std::ostream& operator<<(std::ostream& os, const Matrix4D& m);
		// float Determinant() const;
		float atPos(int i, int j);
		const float atPos(int i, int j) const;
		// const Matrix3D Inverse() const;
	};
}