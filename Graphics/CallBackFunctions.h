#pragma once
#include <GLFW/glfw3.h>
#include "../Events/Events.h"
#include "window.h"
using EventCallBackFunction = std::function<void(Lina::Events::Event&)>;
namespace Lina{namespace Callbacks{
    void WindowResize(GLFWwindow* window, int width, int height);
    void WindowClose(GLFWwindow* window);
    void Key(GLFWwindow* window, int key, int scancode, int action, int mods);
    void Char(GLFWwindow* window, unsigned int keycode);
    void MouseButton(GLFWwindow* window, int button, int action, int mod);
    void Scroll(GLFWwindow* window, double x, double y);
    void CursorPosition(GLFWwindow* window, double x, double y);
}}
