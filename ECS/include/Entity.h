#pragma once
#include "./component.h"
#include "./components.h"
#include <unordered_map>
namespace Lina { namespace ECS{
    class Entity
    {
        public:
            void addComponent(Component::Component* component)
            {
                mComponents.push_back(component);
                component->setEntityID(mID);
                Component::Type type = component->getType();
            }
            Component::Component* findComponent(Component::Type& type) const
            {
                for (auto i: mComponents)
                {
                    if (i->getType() == type)
                        return i;
                }
                std::cout<<"Not Found\n";
            }
            long getID() const {return mID;}
        protected:
            long mID;
            std::vector<Component::Component*> mComponents;
    };
}}
