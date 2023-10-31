#include <iostream>
#include "./include/MainScreen.h"
#include "./include/Spawner.h"
#include "../core/headers/Application.h"
namespace Lina{ namespace GUI{
    static ScreenSpecs mSpecs;
    static b8 remainOpen = true;
    static b8 alreadyLoaded = false;
    static u32 BGImage = 0;
    static Lina::Graphics::Texture* bg;
    static ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
    b8 MainScreen::Setup()
    {
        auto* BG = lnew<Lina::Graphics::Texture>();
        bg = BG;
        BG->setTextureFromPath("../Assets/GUI/BG2.png");
        BGImage = BG->getRenderId();
    }
    b8 MainScreen::Load()
    {
        Core::Application& app = Core::Application::Get();
        mSpecs.sWidth = app.getWindow().getWidth();
        mSpecs.sHeight = app.getWindow().getHeight();
        mSpecs.sIsTransparent = false;
        mSpecs.sTitle = "Main Screen";
        ImGui::SetNextWindowSize(ImVec2(mSpecs.sWidth, mSpecs.sHeight));
        if (remainOpen)
        {
            alreadyLoaded = true;
            ImGui::PushStyleColor(ImGuiCol_WindowBg, color);
            ImGui::Begin(mSpecs.sTitle.c_str(), nullptr,
                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
            //ImGui::SetCursorPos(ImVec2(0,0));
            //ImGui::Image((void*)(intptr_t)BGImage, ImVec2(mSpecs.sWidth, mSpecs.sHeight));
            ImGui::SetCursorPos(ImVec2(mSpecs.sWidth / 2, mSpecs.sHeight/2));
            if (ImGui::Button("Begin"))
            {
                MainScreen::Unload();
            }
            ImGui::End();
            ImGui::PopStyleColor();
        }
        return true;
    }
    b8 MainScreen::Unload()
    {
        ldelete(bg);
        alreadyLoaded = false;
        remainOpen = false;
    }
}}
