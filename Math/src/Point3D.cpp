#include "../Point3D.h"
#include <cmath>
namespace Lina{ namespace Math{
	float Point3D::distanceSquared(const Point3D& p){
		return (p.x - x) * (p.x - x) + (p.z - z) * (p.z - z) + (p.y - y) * (p.y - y);
	}
	float Point3D::distance(const Point3D& p){
		return sqrt((p.x - x) * (p.x - x) + (p.z - z) * (p.z - z) + (p.y - y) * (p.y - y));
	}
}}
