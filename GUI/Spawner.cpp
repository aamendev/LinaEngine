#include <iostream>
#include "../core/headers/Application.h"
#include "./include/Spawner.h"
#include "../PlanetarySystem/Celestials/include/Planet.h"
namespace Lina { namespace GUI{
    static ScreenSpecs specs;
    static b8 remainOpen = true;
    static b8 alreadyLoaded = false;
    static ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    b8 SpawnerScreen::Setup()
    {
        return true;
    }
    b8 SpawnerScreen::Load()
    {
        Core::Application& app = Core::Application::Get();
        specs.sWidth = app.getWindow().getWidth();
        specs.sHeight = app.getWindow().getHeight() * 0.15f;
        specs.sIsTransparent = false;
        specs.sTitle = "SpawnerScreen Screen";
        ImGui::SetNextWindowSize(ImVec2(specs.sWidth, specs.sHeight));
        if (remainOpen)
        {
            alreadyLoaded = true;
            ImGui::PushStyleColor(ImGuiCol_WindowBg, color);
            ImGui::SetNextWindowPos(ImVec2(0, specs.sHeight / 0.15f - specs.sHeight));
            ImGui::Begin(specs.sTitle.c_str(), nullptr,
                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
            //ImGui::SetCursorPos(ImVec2(0,0));
            //ImGui::Image((void*)(intptr_t)BGImage, ImVec2(specs.sWidth, specs.sHeight));
            ImGui::SetCursorPos(ImVec2(specs.sWidth / 2, specs.sHeight/2));
            if (ImGui::Button("Planet"))
            {
                Planetarium::Planet::onSpawnEvent(Events::Spawnable::Planet);
            }
            ImGui::End();
            ImGui::PopStyleColor();
        }
        return true;
    }

    b8 SpawnerScreen::Unload()
    {
        alreadyLoaded = false;
        remainOpen = false;
    }
}}
