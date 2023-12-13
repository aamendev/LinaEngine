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
            virtual ~Screen() = 0;
            virtual std::vector<Events::Event> getEvents() = 0;
    };
}}
