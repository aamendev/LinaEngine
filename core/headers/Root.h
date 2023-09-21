#pragma once
#include <memory>
#include "../../Graphics/Renderer.h"
namespace Lina{ namespace Core{
    class Root
    {
        public:
            Root() = default;
            Root(Manager::Renderer& renderer)
            {
                mRenderManager = std::make_unique<Manager::Renderer>(renderer);
            }
            std::unique_ptr<Manager::Renderer> mRenderManager;
        private:
            /*std::unique_ptr<Manager::File> mFileManager;
            std::unique_ptr<Manager::Scene> mSceneManager;
            std::unique_ptr<Manager::Physics> mPhysicsManager;
            std::unique_ptr<Manager::ParticleSystem> mParticleSystemManager;
            std::unique_ptr<Manager::Memory> mMemoryManager;*/
    };
}}
