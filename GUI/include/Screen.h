#pragma once
#include "../../lhf.h"
#include "../../Types.h"
#include <string>
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
    };
}}
