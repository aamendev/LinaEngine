#pragma once
#include "../../../Memory/include/MemoryOverload.h"
#include "../../../Types.h"
#include "../../../main/LinaMath.h"
#include "../../../main/LinaGraphics.h"
#include "../../../ECS/include/Entity.h"
#include "../../../Events/Events.h"
#include <json/utils.hpp>
namespace Lina{ namespace Planetarium{
    struct specs
    {
        std::string sTexturePath;
        float sRadius;
        Lina::Math::Point3D sPosition;
    };
    class Planet
    {
        public:
            static b8 spawn();
            static b8 spawn(Lina::Math::Point3D& pos);
            static b8 spawn(Lina::Math::Point3D&& pos);
            static b8 spawn(nlohmann::json& j);
            static
            b8 destroy();
            b8 toggleVisible();
            static b8 onSpawnEvent(Events::Spawn s);
        private:
    };
}}
