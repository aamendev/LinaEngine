#pragma once
namespace Lina { namespace ECS{ namespace Component{

    enum class Type
    {
        ID,
        Transform,
        Tag,
        Render,
        Camera,
        Collider,
        Physics,
        NativeScript
    };
    class Component
    {
        public:
            virtual Type getType() {return mType;}
            virtual long getEntityID() const {return mEntityID;}
            virtual void setEntityID(long id) { mEntityID = id;}
        protected:
            long mEntityID;
            Type mType;
    };
}}}
