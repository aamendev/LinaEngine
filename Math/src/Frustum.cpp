#include "../Frustum.h"
namespace Lina{ namespace Math{
    Frustum::Frustum(Plane& near, Plane& far,
                Plane& top, Plane& bottom,
                Plane& right, Plane& left){
        mNear = near;
        mFar = far;
        mTop = top;
        mBottom = bottom;
        mRight = right;
        mLeft = left;
     }
     Plane Frustum::top() const{
        return mTop;
     }
    Plane Frustum::bottom() const{
        return mBottom;
    }
        Plane Frustum::right() const{
            return mRight;
        }
        Plane Frustum::left() const{
            return mLeft;
        }
        Plane Frustum::near() const{
            return mNear;
        }
        Plane Frustum::far() const{
            return mFar;
        }
        bool Frustum::isInside(Point3D& p) const{
           if (p.dot(mNear.getNormal()) - mNear.getDistanceFromOrigin() > 0
                   && p.dot(mFar.getNormal()) - mFar.getDistanceFromOrigin() > 0
                   && p.dot(mTop.getNormal()) - mTop.getDistanceFromOrigin() > 0
                   && p.dot(mBottom.getNormal()) - mBottom.getDistanceFromOrigin() > 0
                   && p.dot(mRight.getNormal()) - mRight.getDistanceFromOrigin() > 0
                   && p.dot(mLeft.getNormal()) - mLeft.getDistanceFromOrigin() > 0)
               return true;
           return false;
        }


}}
