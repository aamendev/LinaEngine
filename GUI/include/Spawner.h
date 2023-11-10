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
            static b8 Load();
            static b8 Unload();
            static b8 Setup();
    };
}}
