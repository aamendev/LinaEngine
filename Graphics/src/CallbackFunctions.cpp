#include <iostream>
#include "../CallBackFunctions.h"
namespace Lina{ namespace Callbacks{
    void WindowResize(GLFWwindow* window, int width, int height)
    {
        Graphics::WindowPointer& p = *(Graphics::WindowPointer*)glfwGetWindowUserPointer(window);
        p.mWidth;
        p.mHeight;

        Lina::Events::WindowResize event(width, height);
        p.EventCallBack(event);
    }
    void WindowClose(GLFWwindow* window)
    {
        Graphics::WindowPointer& p = *reinterpret_cast<Graphics::WindowPointer *>(glfwGetWindowUserPointer(window));

        Events::WindowClose event;
        p.EventCallBack(event);
    }

    void Key(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Graphics::WindowPointer& p = *reinterpret_cast<Graphics::WindowPointer*>(glfwGetWindowUserPointer(window));
        switch (action)
        {
            case GLFW_PRESS:
                {
                    Events::KeyPressed event(key, false);
                    p.EventCallBack(event);
                    break;
                }
            case GLFW_REPEAT:
                {
                    Events::KeyPressed event(key, true);
                    p.EventCallBack(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    Events::KeyReleased event(key);
                    p.EventCallBack(event);
                    break;
                }
        }
    }

    void Char(GLFWwindow* window, unsigned int keycode)
    {

        Graphics::WindowPointer& p = *reinterpret_cast<Graphics::WindowPointer*>(glfwGetWindowUserPointer(window));
        Events::KeyTyped event(keycode);
        p.EventCallBack(event);
    }

    void MouseButton(GLFWwindow* window, int button, int action, int mod)
    {

        Graphics::WindowPointer& p = *reinterpret_cast<Graphics::WindowPointer*>(glfwGetWindowUserPointer(window));
        switch(action)
        {
            case GLFW_PRESS:
                {
                    Events::MouseButtonPressed event(button);
                    p.EventCallBack(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    Events::MouseButtonReleased event(button);
                    p.EventCallBack(event);
                    break;
                }
        }
    }

    void Scroll(GLFWwindow* window, double x, double y)
    {

        Graphics::WindowPointer& p = *reinterpret_cast<Graphics::WindowPointer*>(glfwGetWindowUserPointer(window));
        Events::MouseScrolled event(static_cast<float>(x), static_cast<float>(y));
        p.EventCallBack(event);
    }
    void CursorPosition(GLFWwindow* window, double x, double y)
    {

        Graphics::WindowPointer& p = *reinterpret_cast<Graphics::WindowPointer*>(glfwGetWindowUserPointer(window));
        Events::MouseMoved event(static_cast<float>(x), static_cast<float>(y));
        p.EventCallBack(event);
    }
}}
