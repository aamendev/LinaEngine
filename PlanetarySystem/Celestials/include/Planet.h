#pragma once
#include "../../../Memory/include/MemoryOverload.h"
#include "../../../Types.h"
#include "../../../main/LinaMath.h"
#include "../../../main/LinaGraphics.h"
#include "../../../ECS/include/Entity.h"
#include "../../../Events/Events.h"
namespace Lina{ namespace Planetarium{
    class Planet
    {
        public:
            static b8 spawn();
            b8 destroy();
            b8 toggleVisible();
            static b8 onSpawnEvent(Events::Spawn s);
        private:
    };
}}
