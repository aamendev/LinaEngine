#pragma once
#include <vector>
#include "../../main/LinaMath.h"
#include "./Entity.h"
namespace Lina{ namespace Manager{
    class ECSManager
    {
        public:
            void addEntity(ECS::Entity* entity) {Entities.push_back(*entity); EntityIDs.push_back(entity->getID());}
            void pushToTransform(ECS::Component::Transform* transform) {Transforms.push_back(*transform);}
            void pushToRenders(ECS::Component::Render* render) {Renders.push_back(*render);}
            void pushToTags(ECS::Component::Tag* tag) {Tags.push_back(*tag);}
            std::vector<ECS::Entity> getEntities() const { return Entities;}
        public:
            std::vector<ECS::Component::Render> getRenders() const {return Renders;}
        private:
            std::vector<ECS::Component::Render> Renders;
            std::vector<ECS::Component::Transform> Transforms;
            std::vector<ECS::Component::Tag> Tags;
            std::vector<ECS::Entity> Entities;
            std::vector<ulong> EntityIDs;
    };
}}
