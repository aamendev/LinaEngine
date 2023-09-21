#pragma once
#include "../../Graphics/window.h"
#include "../../Events/Events.h"
namespace Lina { namespace Manager{
   class Input
   {
       public:
            Input(Graphics::Window& window);
            bool isKeyPressed(const KeyCode key);
            bool isMouseButtonPressed(const MouseCode mouse);
            std::pair<float, float> getMousePosition();
            float getMouseX() {return getMousePosition().first;}
            float getMouseY() {return getMousePosition().second;}
        private:
            GLFWwindow* mWindow;
   };
}}
