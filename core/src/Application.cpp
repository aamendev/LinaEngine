#include "../headers/Application.h"
#include "../../PlanetarySystem/Celestials/include/Shuttle.h"
#include "../../PlanetarySystem/Celestials/include/Planet.h"
#include "../../Layers/include/Render.h"
#include "../../lhf.h"
#define JSONIMPL
#include <json/utils.hpp>
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
        std::vector<nlohmann::json> jsons = json::csvToJson("../data/planets.csv");
        for (auto j : jsons)
        {
            Planetarium::Planet::spawn(j);
        }
        std::vector<ECS::Entity*> entities = mRoot->mECSManager->getEntities();
        Planetarium::Shuttle* shuttle = lnew<Planetarium::Shuttle>();
        shuttle->init();
        std::vector<ECS::Component::Transform*>* trans =
            lnew<std::vector<ECS::Component::Transform*> >();

        std::vector<ECS::Component::Render*>* renders =
            lnew<std::vector<ECS::Component::Render*> >();
        std::pair
            <Manager::IndexedDrawingSpecifications, Manager::DrawData> drawing
            = mRoot->mRenderManager->setup(*(entities[0]));

        for (auto& E : entities)
        {
            trans->push_back(dynamic_cast<ECS::Component::Transform*>
                    (E->findComponent(ECS::Component::Type::Transform)));
            renders->push_back(dynamic_cast<ECS::Component::Render*>
                    (E->findComponent(ECS::Component::Type::Render)));
        }
        mGUILayer->onAttach();
        float theta = 0.2f;
        while (mRunning)
        {
            mWindow->clear();
            shuttle->update();
            mGUILayer->begin();

            int index = 0;
            for (auto t: *trans)
            {
            Math::Transform4D orientation = shuttle->getMatrix() * t->getTransform();

            drawing.second.shader->setUniformMat4("rotationMat",
                     Math::Util::projMatrix(90.0f, mWindow->getWidth() / mWindow-> getHeight())
                     * orientation);
            drawing.second.tex = renders->at(index++)->getTexture();
            std::cout<<renders->at(index - 1)->getTexture()->getPath();
            t->updateRotation(theta += 0.01f, Math::Util::yAxis());
            mRoot->mRenderManager->bind(drawing.second);
            mRoot->mRenderManager->drawIndexed(drawing.first);
            }
            mGUILayer->end();

            mWindow->update();
        }
        for (auto e : entities)
        {
            ldelete(e);
        }
        ldelete(renders);
        ldelete(trans);
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
                break;
            case Key::M:
                std::cout<<"M\n";
                break;
        }
        return true;
    }
}}
