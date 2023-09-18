#pragma once
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Matrix4D.hpp"
#include <array>
namespace Lina{
	class Transform4D : public Matrix4D{
	public:
		Transform4D() = default;
		Transform4D(float n00, float n01, float n02, float n03,
			float n10, float n11, float n12, float n13,
			float n20, float n21, float n22, float n23);
		Transform4D(const Vector3D& v0, const Vector3D& v1,
			const Vector3D& v2, const Point3D& p);
		Vector3D& operator[](int j);
		const Vector3D& operator[](int j) const;
		const Point3D& getTranslation() const;
		void setTranslation(const Point3D& p);
		Transform4D inverse();
		friend Transform4D operator *(const Transform4D& A, const Transform4D& B);
		friend Vector3D operator* (const Transform4D& H, const Vector3D& v);
		friend Point3D operator* (const Transform4D& H, const Point3D& p);
	};
}