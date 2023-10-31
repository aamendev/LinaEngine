#pragma once
#include "../../../Memory/include/MemoryOverload.h"
#include "../../../Types.h"
#include "../../../main/LinaMath.h"
#include "../../../main/LinaGraphics.h"
#include "../../../ECS/include/Entity.h"
namespace Lina{ namespace Planetarium{
    class Planet
    {
        public:
            b8 spawn();
            b8 destroy();
            b8 toggleVisible();
        private:
    };
}}
