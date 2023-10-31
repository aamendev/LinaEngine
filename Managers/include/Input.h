#pragma once
#include "../../Graphics/window.h"
#include "../../Events/Events.h"
namespace Lina { namespace Manager{
   class Input
   {
       public:
            static bool isKeyPressed(const KeyCode key);
            static bool isMouseButtonPressed(const MouseCode mouse);
            static std::pair<float, float> getMousePosition();
            static float getMouseX() {return getMousePosition().first;}
            static float getMouseY() {return getMousePosition().second;}
   };
}}
