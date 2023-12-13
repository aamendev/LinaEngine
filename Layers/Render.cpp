#include "./include/Render.h"
extern Lina::Manager::Renderer gRenderManager;
namespace Lina{ namespace Layer{
    void onAttach()
    {

    }
    void onUpdate()
    {

    }
    void onDetach()
    {
        std::cout<<"Detached!\n";
    }

    void onEvent()
    {
        std::cout<<"Event\n";
    }
}}
