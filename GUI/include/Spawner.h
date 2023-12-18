#pragma once
#include "../../lhf.h"
#include "../../Memory/include/MemoryOverload.h"
#include "Screen.h"
#include "../../Types.h"
#include "../../Events/Events.h"
namespace Lina{ namespace GUI{
    class SpawnerScreen : public Screen
    {
        public:
            virtual b8 Load() override;
            virtual b8 Unload() override;
            virtual b8 Setup() override;
    };
}}
