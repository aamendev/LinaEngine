#pragma once

#include "component.h"
#include "../../main/LinaMath.h"
#include "../../Graphics/Renderable.h"
#include "../../Graphics/Texture.h"
#include "../../Graphics/shaders.h"
namespace Lina{ namespace ECS{ namespace Component{
    class Transform : public Component
    {
        public:
            Transform()
            {
                mRotation = Math::Util::rotationMatrix(0.0f, Math::Vector3D(0,1,0));
                mPosition = Math::Point3D(0,0,0);
            }
            Transform(Math::Point3D& p, Math::Matrix3D& rot);
            Transform(Math::Transform4D& transform);
            Math::Transform4D getTransform() const {return mTransform;};
            void setTransform(Math::Transform4D& transform);
            void updatePosition(const Math::Point3D& position);
            void updatePosition(Math::Point3D&& position);
            void updateRotation(float theta, const Math::Vector3D& axis);
            void updateRotation(const Math::Matrix3D& rot);
        private:
            Math::Point3D mPosition;
            Math::Matrix3D mRotation;
            Math::Transform4D mTransform;
    };
    class Tag : public Component
    {
        public:
            Tag(const std::string& label): mLabel(label){mType = Type::Tag;}
            void setLabel(std::string& label) { mLabel = label;}
        public:
            std::string getLabel() const {return mLabel;}
        private:
            std::string mLabel;
    };
    class Render : public Component
    {
        public:
            Render(Graphics::Renderable* renderable, Graphics::Texture* tex, Graphics::Shader* shader)
                : mRenderable(renderable), mTexture(tex), mShader(shader) {mType = Type::Render;}
        public:
            Graphics::Texture* getTexture() const {return mTexture;}
            Graphics::Renderable* getRenderable() const {return mRenderable;}
            Graphics::Shader* getShader() const {return mShader;}
        private:
            Graphics::Renderable* mRenderable;
            Graphics::Texture* mTexture;
            Graphics::Shader* mShader;
    };
}}}
