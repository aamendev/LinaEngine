#include "../Transform4D.hpp"
namespace Lina{
	Transform4D::Transform4D(float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23){
		n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = 0;
		n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = 0;
		n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = 0;
		n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = 1;
	}
	Transform4D::Transform4D(const Vector3D& v0,
		const Vector3D& v1, const Vector3D& v2, const Point3D& p){
		n[0][0] = v0.x; n[0][1] = v0.y; n[0][2] = v0.z; n[0][3] = 0;
		n[1][0] = v1.x; n[1][1] = v1.y; n[1][2] = v1.z; n[1][3] = 0;
		n[2][0] = v2.x; n[2][1] = v2.y; n[2][2] = v2.z; n[2][3] = 0;
		n[2][0] = p.x; n[2][1] = p.y; n[2][2] = p.z; n[3][3] = 1;
	}
	Vector3D& Transform4D::operator[](int j){
		return *reinterpret_cast<Vector3D *> (&n[j]);
	}
	const Vector3D& Transform4D::operator[](int j) const{
		return *reinterpret_cast<const Vector3D *> (&n[j]);
	}
	const Point3D& Transform4D::getTranslation() const{
		return	*reinterpret_cast<const Point3D *>(&n[3]);
	}
	void Transform4D::setTranslation(const Point3D& p){
		n[3][0] = p.x;
		n[3][1] = p.y;
		n[3][2] = p.z;
	}

	Transform4D Transform4D::inverse(){
		const Vector3D& v0 = *reinterpret_cast<const Vector3D *> (&n.at(0));
		const Vector3D& v1 = *reinterpret_cast<const Vector3D *> (&n.at(1));
		const Vector3D& v2 = *reinterpret_cast<const Vector3D *> (&n.at(2));
		const Vector3D& v3 = *reinterpret_cast<const Vector3D *> (&n.at(3));
		Vector3D acrossb = v0.cross(v1);
		Vector3D ccrossd = v2.cross(v3);
		float invDet = 1 / acrossb.dot(ccrossd);
		acrossb *= invDet;
		ccrossd *= invDet;
		Vector3D v =  v2 * invDet;
		Vector3D r0 = v1.cross(v);
		Vector3D r1 = v.cross(v0);

		return Transform4D (
			r0.x, r0.y, r0.z, - v1.dot(ccrossd),
			r1.x, r1.y, r1.z,  v2.dot(ccrossd),
			acrossb.x, acrossb.y, acrossb.z, - v3.dot(acrossb)
			) ;
	}
	Transform4D operator *(const Transform4D& A, const Transform4D& B){
		return Transform4D(
			A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0),
			A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1),
			A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2),
			A(0, 0) * B(0, 3) + A(0, 1) * B(1, 3) + A(0, 2) * B(2, 3) + A(0, 3),
			A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0),
			A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1),
			A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2),
			A(1, 0) * B(0, 3) + A(1, 1) * B(1, 3) + A(1, 2) * B(2, 3) + A(1, 3),
			A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0),
			A(2, 0) * B(0 ,1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1),
			A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2),
			A(2, 0) * B(0, 3) + A(2, 1) * B(1, 3) + A(2, 2) * B(2, 3) + A(2, 3)
			);
	}
	Vector3D operator*(const Transform4D& H, const Vector3D& v){
		return Vector3D(
			H(0, 0) * v.x + H(0, 1) * v.y + H(0, 2) * v.z,
			H(1, 0) * v.x + H(1, 1) * v.y + H(1, 2) * v.z,
			H(2, 0) * v.x + H(2, 1) * v.y + H(2, 2) * v.z
			);
	}
	Point3D operator*(const Transform4D& H, const Point3D& p){
		return Point3D(
			H(0, 0) * p.x + H(0, 1) * p.y + H(0, 2) * p.z + H(0,3),
			H(1, 0) * p.x + H(1, 1) * p.y + H(1, 2) * p.z + H(1,3),
			H(2, 0) * p.x + H(2, 1) * p.y + H(2, 2) * p.z + H(2,3)
			);
	}
}