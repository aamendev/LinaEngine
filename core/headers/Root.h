#pragma once
#include <memory>
#include "../../Types.h"
#include "../../Memory/include/Memory.h"
#include "../../Graphics/Renderer.h"
#include "../../Managers/include/Input.h"
#include "../../ECS/include/ECSManager.h"
extern Lina::Manager::Renderer gRenderManager;
extern Lina::Manager::Memory gMemoryManager;
extern Lina::Manager::ECSManager gECSManager;
namespace Lina{ namespace Core{
    class Root
    {
        public:
            Root() {}
            b8 Init()
            {
                mRenderManager = std::make_unique<Manager::Renderer>(gRenderManager);
                mECSManager = std::make_unique<Manager::ECSManager>(gECSManager);
                mMemoryManager = std::make_unique<Manager::Memory>(gMemoryManager);
            }
        private:
            std::unique_ptr<Manager::Renderer> mRenderManager;
            std::unique_ptr<Manager::ECSManager> mECSManager;
            std::unique_ptr<Manager::Memory> mMemoryManager;
            friend class Application;
            /*std::std::make_unique_ptr<Manager::File> mFileManager;
              std::std::make_unique_ptr<Manager::Scene> mSceneManager;
              std::std::make_unique_ptr<Manager::Physics> mPhysicsManager;
              std::std::make_unique_ptr<Manager::ParticleSystem> mParticleSystemManager;
              std::std::make_unique_ptr<Manager::Memory> mMemoryManager;*/
    };
}}
