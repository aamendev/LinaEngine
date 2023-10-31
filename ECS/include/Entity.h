#pragma once
#include "./component.h"
#include "./components.h"
#include <unordered_map>
namespace Lina { namespace ECS{
    static int topPointer = 0;
    class Entity
    {
        public:
            Entity()
            {
                mComponents = {};
                mID = 0;
                mComponents.reserve(20);
            }
            void addComponent(Component::Component* component)
            {
                if (component)
                {
                mComponents.emplace_back(component);
                component->setEntityID(0);
                Component::Type type = component->getType();
                }
                else
                {
                    std::cout<<"Invalid Component!\n";
                }
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
            Component::Component* findComponent(Component::Type&& type) const
            {
                for (auto i: mComponents)
                {
                    if (i->getType() == type)
                        return i;
                }
                std::cout<<"Not Found\n";
            }
            long getID() const {return mID;}
            int getComponentNumber() const {return mComponents.size();}
        protected:
            long mID;
            std::vector<Component::Component*> mComponents;
    };
}}
