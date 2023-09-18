#include <iostream>
#include "../CallBackFunctions.h"
namespace Lina{ namespace Graphics{
    void WindowResize(GLFWwindow* window, int width, int height)
    {
        WindowPointer& p = *(WindowPointer*)glfwGetWindowUserPointer(window);
        p.mWidth;
        p.mHeight;

        Lina::Events::WindowResize event(width, height);
        p.EventCallBack(event);
    }
    void WindowClose(GLFWwindow* window)
    {
        WindowPointer& p = *reinterpret_cast<WindowPointer *>(glfwGetWindowUserPointer(window));

        Events::WindowClose event;
        p.EventCallBack(event);
        std::cout<<"Closed";
    }
}}
