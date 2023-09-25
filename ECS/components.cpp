#include "include/components.h"
namespace Lina{ namespace ECS{ namespace Component{
    Transform::Transform(Math::Transform4D& transform): mTransform(transform)
    {
        mPosition = transform.getTranslation();
        mRotation = transform.getRotationMatrix();
        mType = Type::Transform;
    }
    void Transform::setTransform(Math::Transform4D& transform)
    {
        mPosition = transform.getTranslation();
        mRotation = transform.getRotationMatrix();
        mTransform = transform;
    }
    void Transform::updateRotation(float theta, const Math::Vector3D& axis)
    {
        Lina::Math::Matrix3D rotMat = Lina::Math::Util::rotationMatrix(theta, axis.normalise())
            * Lina::Math::Util::rotationMatrix(3.14159, Lina::Math::Util::zAxis());
        Lina::Math::Transform4D fullRotMat = Lina::Math::Util::transMatrix(rotMat, Lina::Math::Vector3D(0,0,0));
        mTransform = fullRotMat;
    }
    Transform::Transform(Math::Point3D& p, Math::Matrix3D& rot)
        :mPosition(p), mRotation(rot) {mType = Type::Transform;}
}}}
