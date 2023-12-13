#include "include/components.h"
namespace Lina{ namespace ECS{ namespace Component{
    Transform::Transform(Math::Transform4D& transform)
    {
        mType = Type::Transform;
        setTransform(transform);
    }
    void Transform::setTransform(Math::Transform4D& transform)
    {   mType = Type::Transform;
        mPosition = transform.getTranslation();
        mRotation = transform.getRotationMatrix();
        mTransform = transform;
    }
    void Transform::updateRotation(float theta, const Math::Vector3D& axis)
    {
        Math::Matrix3D rotMat = Math::Util::rotationMatrix(theta, axis.normalise());
        Math::Transform4D fullRotMat = Math::Util::transMatrix(rotMat,mPosition);
        setTransform(fullRotMat);
    }
    void Transform::updatePosition(const Math::Point3D& position)
    {
        auto Transform = Math::Util::transMatrix(mRotation, position);
        setTransform(Transform);
    }
    void Transform::updateRotation(const Math::Matrix3D& rot)
    {
        auto Transform = Math::Util::transMatrix(rot, mPosition);
        setTransform(Transform);
    }
    void Transform::updatePosition(Math::Point3D&& position)
    {
        auto Transform = Math::Util::transMatrix(mRotation, position);
        setTransform(Transform);
    }
    Transform::Transform(Math::Point3D& p, Math::Matrix3D& rot)
        :mPosition(p), mRotation(rot) {mType = Type::Transform;}
}}}
