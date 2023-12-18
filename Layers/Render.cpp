#include "./include/Render.h"
extern Lina::Manager::Renderer gRenderManager;
extern Lina::Manager::ECSManager gEcsManager;
namespace Lina{ namespace Layer{
    Render::Render(){}

    void Render::onAttach()
    {
        mDrawing = gRenderManager.setup(Graphics::Shapes::Icosphere(3));
        gRenderManager.bind(mDrawing.second);
    }
    void Render::onUpdate(Core::TimeStep t)
    {
        auto entities = gEcsManager.getEntities();
        for (auto& e : entities)
        {
            auto render =  dynamic_cast<ECS::Component::Render*>(e->findComponent(ECS::Component::Type::Render));
            auto tex = render->getTexture();
            auto shader = render->getShader();
            tex->bind();
            shader->bind();
        }
    }
    void Render::onDetach()
    {
        std::cout<<"Detached!\n";
    }

    void Render::onEvent(Events::Event& e)
    {
        std::cout<<"Event\n";
    }
}}
