#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <string_view>
#include "../Events/WindowEvent.h"
namespace Lina{ namespace Graphics{
    using EventCallBackFunction = std::function<void(Events::Event&)>;
    struct WindowPointer
    {
        int mWidth;
        int mHeight;
        const char* mName;
        EventCallBackFunction EventCallBack;
    };
    class Window{
        public:
            Window(const char * name, float width, float height);
            ~Window();
            bool closed() const;
            void clear() const;
            void update();

            void setColour(float r, float g, float b, float a);
            void setEventCallBack(const EventCallBackFunction& callBack) {mWindowPointer.EventCallBack = callBack;}
            void getWidth() const;
            void getHeight() const;
            void getWindow() const;
            void getWindowTitle() const;
            bool init();
        private:
            GLFWwindow *mWindow;
            bool mClosed;
            WindowPointer mWindowPointer;
        private:
            void handleEvents();
    };
}}
