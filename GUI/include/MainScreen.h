#pragma once
#include "Screen.h"
#include "../../Graphics/Texture.h"
#include "../../Memory/include/MemoryOverload.h"
namespace Lina{ namespace GUI{
    class MainScreen : public Screen
    {
        public:
            virtual b8 Load() override;
            virtual b8 Unload() override;
            virtual b8 Setup() override;
    };
}}
