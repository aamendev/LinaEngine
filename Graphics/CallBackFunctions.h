#pragma once
#include <GLFW/glfw3.h>
#include "../Events/Events.h"
#include "window.h"
using EventCallBackFunction = std::function<void(Lina::Events::Event&)>;
namespace Lina{namespace Graphics{
    void WindowResize(GLFWwindow* window, int width, int height);
    void WindowClose(GLFWwindow* window);
}}
