#pragma once
#include <string>
#include "../dependencies/glfw/include/GLFW/glfw3.h"
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
            Window() {}
            Window(const char * name, float width, float height);
            ~Window();
            bool closed() const;
            void clear() const;
            void update();

            void Create(const char* name, float width, float height);
            void setColour(float r, float g, float b, float a);
            void setEventCallBack(const EventCallBackFunction& callBack) {mWindowPointer.EventCallBack = callBack;}
            float getWidth() const {return mWindowPointer.mWidth;}
            float getHeight() const {return mWindowPointer.mHeight;}
            GLFWwindow* getWindow() const {return mWindow;}
            const char* getWindowTitle() const {return mWindowPointer.mName;};
            bool init();
        private:
            GLFWwindow *mWindow;
            bool mClosed;
            WindowPointer mWindowPointer;
        private:
            void handleEvents();
    };
}}
