#pragma once
#include <memory>
#include "../../Graphics/Renderer.h"
#include "../../Managers/include/Input.h"
namespace Lina{ namespace Core{
    class Root
    {
        public:
            Root() = default;
            Root(Manager::Renderer& renderer, Manager::Input& manager)
            {
                mRenderManager = std::make_unique<Manager::Renderer>(renderer);
                mInputManager = std::make_unique<Manager::Input>(manager);
            }
            std::unique_ptr<Manager::Renderer> mRenderManager;
            std::unique_ptr<Manager::Input> mInputManager;
        private:
            /*std::unique_ptr<Manager::File> mFileManager;
            std::unique_ptr<Manager::Scene> mSceneManager;
            std::unique_ptr<Manager::Physics> mPhysicsManager;
            std::unique_ptr<Manager::ParticleSystem> mParticleSystemManager;
            std::unique_ptr<Manager::Memory> mMemoryManager;*/
    };
}}
