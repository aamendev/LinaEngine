#pragma once
#include "../../main/LinaGraphics.h"
#include "../../Events/Events.h"
#include "../headers/Root.h"
#include "../../Memory/include/MemoryOverload.h"
#include "Macros.h"
#include "../../Layers/include/GUI.h"
#include "../headers/Layer.h"
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
            Application(Graphics::Window* window, Root& root);
            virtual ~Application() = default;

            void onEvent(Events::Event& e);

            void checkForEvent();
            Graphics::Window& getWindow() { return *mWindow; }

            void close();
            const ApplicationSpecifications getSpecifications() const { return mSpecs; }
            void run();
            Graphics::Window* mWindow;
            static Application& Get() {return *gApplication;}
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
            Root* mRoot;
            static Application* gApplication;
            Lina::Layer::GUI* mGUILayer;
            //friend int ::main();
    };
    Application* CreateApplication();
}}
