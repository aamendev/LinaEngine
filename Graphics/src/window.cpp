#include "../glad.h"
#include "../../Events/Events.h"
#include "../CallBackFunctions.h"
#include "../window.h"
#include <iostream>
namespace Lina{namespace Graphics{
	Window::Window(const char * name, float width, float height)
    {
        mWindowPointer = WindowPointer{ .mWidth = width, .mHeight = height, .mName = name,.EventCallBack = NULL};
		if (!init())
			glfwTerminate();
	}
	Window::~Window(){
		glfwTerminate();
	}
	bool Window::init(){
		if (!glfwInit()){
			return false;
		}
		mWindow = glfwCreateWindow(mWindowPointer.mWidth, mWindowPointer.mHeight
                                ,mWindowPointer.mName,nullptr, nullptr);
		if (!mWindow){
			glfwTerminate();
			std::cout<<"Error creating the screen\n";
			return false;
		}
		glfwMakeContextCurrent(mWindow);
		glfwSwapInterval(4);
        handleEvents();
		gladLoadGL();
		std::cout<< glGetString(GL_VERSION)<<'\n';
		return true;
	}
    void Window::handleEvents()
    {
        glfwSetWindowUserPointer(mWindow, &mWindowPointer);

        glfwSetWindowSizeCallback(mWindow, WindowResize);

        glfwSetWindowCloseCallback(mWindow, WindowClose);

        /*glfwSetKeyCallback(mWindow, [](GLFWWindow * window, int key, int scancode,
                                        int action, int mode);
                {
                    WindowPointer& p = *reinterpret_cast<WindowPointer *>(glfwGetWindowUserPointer(window));

                    Events::KeyPressed event(key);
                    p.EventCallBack(event);
                });

        glfwSetCharCallback(mWindow, [](GLFWWindow * window, unsigned int keycode)
                {
                    WindowPointer& p = *reinterpret_cast<WindowPointer *>(glfwGetWindowUserPointer(window));

                    Events::KeyTyped event(keycode);
                    p.EventCallBack(event);
                });

        glfwSetMouseButtonCallback(mWindow, [](GLFWWindow * window, int button, int action, int mods)
                {
                    WindowPointer& p = *reinterpret_cast<WindowPointer *>(glfwGetWindowUserPointer(window));

                    Events::MouseReleased event(button);
                    p.EventCallBack(event);
                });

        glfwSetScrollCallback(mWindow, [](GLFWWindow * window, double xOffset, double yOffset)
                {
                    WindowPointer& p = *reinterpret_cast<WindowPointer *>(glfwGetWindowUserPointer(window));

                    Events::MouseScrolled event(static_cast<float>(xOffset), static_cast<float>(yOffset));
                    p.EventCallBack(event);
                });

        glfwSetCursorPosCallback(mWindow, [](mWidnow, [](GLFWwindow* window, double xPos, double yPos)
                    {
                        WindowPointer& p = *reinterpret_cast<WindowPointer *>(glfwGetWindowUserPointer(window));
                        Events::MouseMoves event(static_cast<float>xPos, static_cast<float>yPos);
                        p.EventCallBack(event);
                    });*/

    }
	void Window::clear() const{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Window::setColour(float r, float g, float b, float a){
		glClearColor(r, g, b, a);
	}
	bool Window::closed() const{
		return glfwWindowShouldClose(mWindow);
	}
	void Window::update(){
		glfwPollEvents();
		glfwGetFramebufferSize(mWindow, &mWindowPointer.mWidth, &mWindowPointer.mHeight);
		glfwSwapBuffers(mWindow);
	}
}}
