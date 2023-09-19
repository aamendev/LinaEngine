#pragma once

namespace Lina { namespace Core{
    struct ApplicationSpecifications
    {
        std::string sName = "Lina Engine";
        std::string SWorkingDirectory;
    };
    class Application
    {
        public:
            Root(const RootSpecifications& specs);
            virtual ~Root();

            void onEvent(Events::Event& e);

            void pushLayer(Layer& layer);
            void popLayer();

            Window& getWindow() { return mWindow; }

            void close();
            const getSpecifications() const { return mSepcs; }
        private:
            void run();
            bool onWindowClose(Events::WindowClose& e);
            bool onWindowResize(Events::WindowResize& e);

        private:
            ApplicationSpecifications mSpecs;
            std::unique_ptr<Window> mWindow;
            bool mRunning;
            bool mMinimized;
            std::vector<Layer> mLayers;
            float mLastFrameTime = 0.0f;
        prviate:
            static Root* mRootInstance;
            friend int ::main(int argc, char** argv);
    };
}}
