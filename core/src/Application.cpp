#include "../headers/Application.h"

namespace Lina{ namespace Core{
    Application::Application(Graphics::Window& window, Root& root)
    {
        mWindow = &window;
        mRoot = &root;
        mWindow->setEventCallBack(FORWARD_CALL(Application::onEvent));
        mRunning = true;
    }
    void Application::onEvent(Events::Event& e)
    {
        Events::Dispatcher dispatcher(e);
        dispatcher.dispatch<Events::WindowClose>(FORWARD_CALL(Application::onWindowClose));
        dispatcher.dispatch<Events::WindowResize>(FORWARD_CALL(Application::onWindowResize));
    }
    void Application::run()
    {
        while (mRunning)
        {
            mWindow->clear();
            mWindow->update();
            if (mRoot->mInputManager->isKeyPressed(Key::Q))
            {
                std::cout<<"Closing Now...";
                mRunning = false;
            }
        }
    }
    bool Application::onWindowClose(Events::WindowClose& e)
    {
        mRunning = false;
        return true;
    }
    bool Application::onWindowResize(Events::WindowResize& e)
    {
       mRoot->mRenderManager->setViewPort(0, 0, e.getWidth(), e.getHeight());
    }
}}
