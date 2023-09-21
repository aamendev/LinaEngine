#include "include/Input.h"

namespace Lina { namespace Manager{
    Input::Input(Graphics::Window& window)
    {
        mWindow = window.getWindow();
    }
    bool Input::isKeyPressed(const KeyCode key)
    {
        auto state = glfwGetKey(mWindow, static_cast<int32_t>(key));
        return state == GLFW_PRESS;
    }
    bool Input::isMouseButtonPressed(const MouseCode but)
    {
        auto state = glfwGetMouseButton(mWindow, static_cast<int32_t>(but));
        return state == GLFW_PRESS;
    }
    std::pair<float, float> Input::getMousePosition()
    {
        double x, y;
        glfwGetCursorPos(mWindow, &x, &y);
        return {static_cast<float>(x), static_cast<float>(y)};
    }
}}
