#pragma once
#include <array>
#include "Plane.h"
namespace Lina{ namespace Math{

    class Frustum{
    public:
        Frustum(Plane& near, Plane& far,
                Plane& top, Plane& bottom,
                Plane& right, Plane& left
                );
        Plane top() const;
        Plane bottom() const;
        Plane right() const;
        Plane left() const;
        Plane near() const;
        Plane far() const;
        bool isInside(Point3D& p) const;
    private:
        Plane mNear;
        Plane mFar;
        Plane mRight;
        Plane mLeft;
        Plane mTop;
        Plane mBottom;
    };
}}
