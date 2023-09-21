#pragma once
#include "../../main/LinaGraphics.h"
#include "../../Events/Events.h"
#include "../headers/Root.h"
#include "Macros.h"
//#include "../headers/Layer.h"
namespace Lina { namespace Core{
    struct ApplicationSpecifications
    {
        std::string sName = "Lina Engine";
        std::string SWorkingDirectory;
    };
    class Application
    {
        public:
            Application();
            Application(Graphics::Window& window);
            virtual ~Application() = default;

            void onEvent(Events::Event& e);


            Graphics::Window& getWindow() { return *mWindow; }

            void close();
            const ApplicationSpecifications getSpecifications() const { return mSpecs; }
            void run();
            Graphics::Window* mWindow;
        private:
            bool onWindowClose(Events::WindowClose& e);
            bool onWindowResize(Events::WindowResize& e);

        private:
            ApplicationSpecifications mSpecs;
            bool mRunning;
            bool mMinimized;
          //  std::vector<Layer> mLayers;
            float mLastFrameTime = 0.0f;
        private:
            Root mRoot;
            //friend int ::main();
    };
    Application* CreateApplication();
}}
