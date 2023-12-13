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
                mRenderManager = &(gRenderManager);
                mECSManager = &(gECSManager);
                mMemoryManager = &(gMemoryManager);
                return true;
            }
        private:
            Manager::Renderer* mRenderManager;
            Manager::ECSManager* mECSManager;
            Manager::Memory* mMemoryManager;
            friend class Application;
            /*std::std::make_unique_ptr<Manager::File> mFileManager;
              std::std::make_unique_ptr<Manager::Scene> mSceneManager;
              std::std::make_unique_ptr<Manager::Physics> mPhysicsManager;
              std::std::make_unique_ptr<Manager::ParticleSystem> mParticleSystemManager;
              std::std::make_unique_ptr<Manager::Memory> mMemoryManager;*/
    };
}}
