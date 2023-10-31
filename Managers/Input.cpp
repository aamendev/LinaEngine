#include "../core/headers/Application.h"
#include "include/Input.h"
namespace Lina { namespace Manager{
    bool Input::isKeyPressed(const KeyCode key)
    {
        auto* window = Core::Application::Get().getWindow().getWindow();
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS;
    }
    bool Input::isMouseButtonPressed(const MouseCode but)
    {
        auto* window = Core::Application::Get().getWindow().getWindow();
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(but));
        return state == GLFW_PRESS;
    }
    std::pair<float, float> Input::getMousePosition()
    {
        auto* window = Core::Application::Get().getWindow().getWindow();
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return {static_cast<float>(x), static_cast<float>(y)};
    }
}}
