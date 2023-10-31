#pragma once
#include "Screen.h"
#include "../../Graphics/Texture.h"
#include "../../Memory/include/MemoryOverload.h"
namespace Lina{ namespace GUI{
    class MainScreen : public Screen
    {
        public:
            static b8 Load();
            static b8 Unload();
            static b8 Setup();
    };
}}
