#pragma once
#include "../../lhf.h"
#include "../../Types.h"
#include <string>
#include <vector>
#include "../../Events/Event.h"
namespace Lina{ namespace GUI{
    struct ScreenSpecs
    {
        f32 sWidth;
        f32 sHeight;
        std::string sTitle;
        b8 sIsTransparent;
    };
    class Screen
    {
        public:
            virtual ~Screen() {};
            virtual b8 Setup() {};
            virtual b8 Load() {};
            virtual b8 Unload() {};
            virtual std::vector<Events::Event> getEvents() {};
    };
}}
