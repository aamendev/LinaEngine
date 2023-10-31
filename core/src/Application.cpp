#include "../headers/Application.h"
#include "../../PlanetarySystem/Celestials/include/Shuttle.h"
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
    }
    void Application::run()
    {
        std::vector<ECS::Entity> entities = mRoot->mECSManager->getEntities();
        std::vector<ECS::Component::Transform*> trans;
        for (auto& E : entities)
        {
          trans.push_back(dynamic_cast<ECS::Component::Transform*>(E.findComponent(ECS::Component::Type::Transform)));
        }
        std::vector<std::pair<Lina::Manager::IndexedDrawingSpecifications, Lina::Manager::DrawData>> drawing;
        for (auto& E: entities)
        {
            drawing.push_back(mRoot->mRenderManager->setup(E));
        }
        float theta = 0.0f;
        Planetarium::Shuttle* shuttle = lnew<Planetarium::Shuttle>();
        shuttle->init();
        mGUILayer->onAttach();
        while (mRunning)
        {
            mWindow->clear();
            shuttle->update();
            mGUILayer->begin();
            for (int i = 0; i < drawing.size(); i++)
            {
            mRoot->mRenderManager->bind(drawing[i].second);
            mRoot->mRenderManager->drawIndexed(drawing[i].first);

            Math::Transform4D orientation = shuttle->getMatrix() * trans[i]->getTransform();

            drawing[i].second.shader->setUniformMat4("rotationMat",
                     Math::Util::projMatrix(90.0f, mWindow->getWidth() / mWindow-> getHeight())
                     * orientation);
            trans[i]->updateRotation(theta, Math::Vector3D(0,1,0));
            theta += 0.05f;
            }
            mGUILayer->end();

            mWindow->update();


            if (Manager::Input::isKeyPressed(Key::Q))
            {
                std::cout<<"Closing Now...";
                mGUILayer->onDetach();
                ldelete(mGUILayer);
                //mRoot->mRenderManager->freeLina::Manager::DrawData(drawing.second);
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
