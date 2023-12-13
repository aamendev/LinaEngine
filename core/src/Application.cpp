#include "../headers/Application.h"
#include "../../PlanetarySystem/Celestials/include/Shuttle.h"
#include "../../PlanetarySystem/Celestials/include/Planet.h"
#include "../../lhf.h"
namespace Lina{ namespace Core{
    Application* Application::gApplication = nullptr;
    Application::Application(Graphics::Window* window, Root& root)
    {
        gApplication = this;
        mWindow = window;
        mRoot = &root;
        mRoot->Init();
        mWindow->setEventCallBack(FORWARD_CALL(Application::onEvent));
        mGUILayer = lnew(Lina::Layer::GUI());
        mRunning = true;
    }
    void Application::onEvent(Events::Event& e)
    {
        Events::Dispatcher dispatcher(e);
        dispatcher.dispatch<Events::WindowClose>(FORWARD_CALL(Application::onWindowClose));
        dispatcher.dispatch<Events::WindowResize>(FORWARD_CALL(Application::onWindowResize));
        dispatcher.dispatch<Events::KeyPressed>(FORWARD_CALL(Application::onKeyPressed));
    }
    void Application::run()
    {
        Planetarium::Planet::spawn();
        Planetarium::Planet::spawn();
        std::vector<ECS::Entity*> entities = mRoot->mECSManager->getEntities();
        Planetarium::Shuttle* shuttle = lnew<Planetarium::Shuttle>();
        shuttle->init();
        std::vector<ECS::Component::Transform*> trans;
        std::pair
            <Manager::IndexedDrawingSpecifications, Manager::DrawData> drawing
            = mRoot->mRenderManager->setup(*(entities[0]));

        mGUILayer->onAttach();
        while (mRunning)
        {
            for (auto& E : entities)
            {
                trans.push_back(dynamic_cast<ECS::Component::Transform*>(E->findComponent(ECS::Component::Type::Transform)));
            }
            mWindow->clear();
            shuttle->update();
            mGUILayer->begin();

            mRoot->mRenderManager->bind(drawing.second);
            {
            Math::Transform4D orientation = shuttle->getMatrix() * trans[0]->getTransform();

            drawing.second.shader->setUniformMat4("rotationMat",
                     Math::Util::projMatrix(90.0f, mWindow->getWidth() / mWindow-> getHeight())
                     * orientation);
            trans[0]->updatePosition(Math::Point3D(0.0f,0.0f,3.0f));
            mRoot->mRenderManager->bind(drawing.second);
            mRoot->mRenderManager->drawIndexed(drawing.first);
            }

            {
            Math::Transform4D orientation = shuttle->getMatrix()
                * trans[1]->getTransform();

            drawing.second.shader->setUniformMat4("rotationMat",
                     Math::Util::projMatrix(
                         90.0f,
                         mWindow->getWidth() / mWindow-> getHeight())
                     * orientation);
            trans[1]->updatePosition(Math::Point3D(2.0f,2.0f,3.0f));
            mRoot->mRenderManager->bind(drawing.second);
            mRoot->mRenderManager->drawIndexed(drawing.first);
            }
            mGUILayer->end();

            mWindow->update();


           /* if (Manager::Input::isKeyPressed(Key::Q))
            {
                std::cout<<"Closing Now...";
                mGUILayer->onDetach();
                ldelete(mGUILayer);
                //mRoot->mRenderManager->freeLina::Manager::DrawData(drawing.second);
                mRunning = false;
            }*/
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
       return true;
    }

    bool Application::onKeyPressed(Events::KeyPressed& e)
    {
        switch(e.getKeyCode())
        {
            case Key::Q:
                mRunning = false;
            case Key::M:
                std::cout<<"M\n";
        }
        return true;
    }
}}
