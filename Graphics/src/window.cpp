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

        glfwSetWindowSizeCallback(mWindow, Callbacks::WindowResize);

        glfwSetWindowCloseCallback(mWindow, Callbacks::WindowClose);

        glfwSetKeyCallback(mWindow, Callbacks::Key);

        glfwSetCharCallback(mWindow, Callbacks::Char);

        glfwSetMouseButtonCallback(mWindow, Callbacks::MouseButton);

        glfwSetScrollCallback(mWindow, Callbacks::Scroll);

        glfwSetCursorPosCallback(mWindow, Callbacks::CursorPosition);

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
