#include "../Utilities.h"
#include "../Matrix.hpp"
#include "../Vector3D.hpp"
#include "../Point3D.hpp"
#include "../Transform4D.hpp"
#include "../Quatrenion.hpp"
#include <cmath>
#include <cfloat>
namespace Lina{
	namespace MathUtil{
		Matrix3D rotationMatrix(float theta,const Vector3D& axis){
			float c = cos(theta);
			float s = sin(theta);
			float d = 1 - c;
			Vector3D a = axis.normalise();
			return Matrix3D(
				c + d * a.x * a.x, d * a.x * a.y - s * a.z, d * a.x * a.z + s * a.y,
				d * a.x * a.y + s * a.z, c + d * a.y * a.y, d * a.y * a.z - s * a.x,
				d * a.x * a.z - s * a.y, d * a.y * a.z + s * a.x, c + d * a.z * a.z
				);
		}
		Matrix3D reflectionMatrix(const Vector3D& axis){
			Vector3D a = axis.normalise();
			return Matrix3D(1 - 2 * a.x * a.x, -2 * a.x * a.y, -2 * a.x * a.z,
				-2 * a.x * a.y, 1 - 2 * a.y * a.y, -2 * a.y * a.z,
				-2 * a.x * a.z, -2 * a.y * a.z, 1 - 2 * a.z * a.z		
				);
		}
		Matrix3D identityMatrix(){
			return Matrix3D(1, 0, 0,
				0, 1, 0,
				0, 0, 1
				);
		}
		Matrix3D involutionMatrix(const Vector3D& axis){
			Vector3D a = axis.normalise();
			return Matrix3D(
				2 * a.x * a.x - 1, 2 * a.y * a.y, 2 * a.x * a.z,
				2 * a.x * a.y, 2 * a.y * a.y - 1, 2 * a.y * a.z,
				2 * a.x * a.z, 2 * a.y * a.z, 2 * a.z * a.z - 1
				);
		}
		Matrix3D scaleMatrix(float s, const Vector3D& axis){
			Vector3D a = axis.normalise();
			s--;
			return Matrix3D(
				s * a.x * a.x + 1, s * a.x * a.y, s * a.x * a.z,
				s * a.x * a.y, s * a.y * a.y + 1, s * a.y * a.z,
				s * a.x * a.z, s * a.y * a.z, s * a.z * a.z + 1 
				);
		}
		Matrix3D skewMatrix(float theta, const Vector3D& vector0, const Vector3D& vector1){
			float t = tan(theta);
			Vector3D a = vector0.normalise();
			Vector3D b = vector1.normalise();
			return Matrix3D(
				a.x * b.x * t + 1, a.x * b.y * t, a.x * b.z * t,
				a.y * b.x * t, a.y * b.y * t + 1, a.y * b.z * t,
				a.z * b.x * t, a.z * b.y * t, a.z * b.z * t + 1
				);
		}
		Transform4D zUp(){
			return Transform4D(
				1, 0, 0, 0,
				0, 0, -1, 0,
				0, 1, 0, 0
			);
		}
		Transform4D yUp(){
			return Transform4D(
				1, 0, 0, 0,
				0, 0, 1, 0,
				0, -1, 0, 0
			);
		}
		Vector3D xAxis(){
			return Vector3D(1, 0, 0);
		}
		Vector3D yAxis(){
			return Vector3D(0, 1, 0);
		}
		Vector3D zAxis(){
			return Vector3D(0, 0, 1);
		}
		Vector3D lerp(const Vector3D& v0, const Vector3D& v1, float beta){
			return  v0 * (1 - beta) + v1 * beta;
		}
		Line connectOrigin(const Point3D& p){
			return Line(p, Vector3D(0,0,0));
		}
		Plane xyPlane(){
			return Plane(0, 0, 1, 0);
		}
		Plane xzPlane(){
			return Plane(0, 1, 0, 0);
		}
		Plane yzPlane(){
			return Plane(1, 0, 0, 0);
		}

		float distance(const Point3D& q, const Point3D& p, const Vector3D& v){
			Vector3D a = (q - p).cross(v);
			return sqrt(a.dot(a) / v.dot(v));
		}
		float distance(const Point3D& p0, const Vector3D v0,
			const Point3D& p1, const Vector3D v1){
			Vector3D dp = p1 - p0;
			float v02 = v0.dot(v0);
			float v12 = v1.dot(v1);
			float v0v1 = v0.dot(v1);

			float det = v0v1 * v0v1 - v02 * v12;

			if (fabs(det) > FLT_MIN){
				det = 1 / det;
				float dpv0 = dp.dot(v0);
				float dpv1 = dp.dot(v1);
				float t0 = (v0v1 * dpv1 - v12 * dpv0) * det;
				float t1 = (v02 * dpv1 - v0v1 * dpv0) * det;

				return (dp + v1 * t1 - v0 * t0).magnitude();
			}else{
				Vector3D a = dp.cross(v0);
				return sqrt(a.dot(a) / v02);
			}
		}

		Transform4D planeReflectionMatrix(const Plane& f){
			Plane p = f.normalise();
			return Transform4D(
				1 - 2 * p.x * p.x, -2 * p.x * p.y, -2 * p.x * p.z, -2 * p.x * p.w,
				-2 * p.x * p.y, 1 - 2 * p.y * p.y, -2 * p.y * p.z, -2 * p.y * p.w,
				-2 * p.x * p.z, -2 * p.y * p.z, 1 - 2 * p.z * p.z, -2 * p.z * p.w
				);
		}
		Transform4D translationMatrix(const Vector3D& v){
			return Transform4D(
				1, 0, 0,v.x,
				0, 1, 0,v.y,
				0, 0, 1,v.z
				);
		}
		Transform4D transMatrix(const Matrix3D& m,const Vector3D& t){
			return Transform4D(
				m(0, 0), m(0, 1), m(0, 2), t.x,
				m(1, 0), m(1, 1), m(1, 2), t.y,
				m(2, 0), m(2, 1), m(2, 2), t.z
				);
		}
		Transform4D scaleMatrix(const Vector3D& s){
			return Transform4D(
				s.x, 0, 0, 0,
				0, s.y, 0, 0,
				0, 0, s.z, 0
				);
		}
		Quatrenion lerp(const Quatrenion& q0, const Quatrenion& q1, float beta){
			return (q0 * (1 - beta) + q1 * beta) / (q0 * (1 - beta) + q1 * beta).magnitude();
		}
		Quatrenion slerp(const Quatrenion& q0, const Quatrenion& q1, float beta){
			return (q0 * sin((1 - beta) * q0.theta(q1))
				+ q1 *  sin(beta * q0.theta(q1))) * 1 / sin(q0.theta(q1));
		}
		std::pair<Quatrenion, Quatrenion> dualQuatrenion(const Quatrenion& q0, const Quatrenion& q1){
			return {q0, q1};
		}
	}
}