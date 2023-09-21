#pragma once
#include "../Graphics/window.h"
#include "../Graphics/Renderer.h"
namespace Lina { namespace Default{
    Graphics::Window Window()
    {
        Graphics::Window window("Lina::Engine", 720, 720);
        return window;
    }
    Manager::Renderer Renderer()
    {
        Manager::Renderer renderer;
        renderer.enableCulling();
        renderer.enableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        renderer.setFrontFace(GL_CCW);
        return renderer;
    }
}}
