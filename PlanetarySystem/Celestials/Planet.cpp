#include "../../Graphics/glad.h"
#include "./include/Planet.h"
#include "../../ECS/include/ECSManager.h"
extern Lina::Manager::ECSManager gECSManager;
namespace Lina{ namespace Planetarium{
    b8 Planet::spawn()
    {
      auto* planet = lnew<ECS::Entity>();
      auto* ico = lnew<Graphics::Shapes::Icosphere>();
      ico->constructSphere(0.5f);
      ico->subdivide(3);

      auto* texture = lnew<Graphics::Texture>();
      texture->setTextureFromPath("../Assets/Universe/SolarSystem/2k_earth_daymap.jpg");

      auto* shader = lnew(Graphics::Shader());
      shader->setShaderFromPath("../Graphics/shaders/basic.shader");

      auto* mesh = lnew(ECS::Component::Render(ico, texture, shader));

      Math::Matrix3D rotation = Math::Util::rotationMatrix(0, Math::Util::zAxis());
      Math::Point3D position = Math::Point3D(0.0f,0.0f,3.0f);

      auto* transform = lnew(ECS::Component::Transform(position, rotation));

      planet->addComponent(mesh);
      planet->addComponent(transform);

      gECSManager.addEntity(planet);
      return true;
    }
    b8 Planet::onSpawnEvent(Events::Spawn s)
    {
       if (s.getSpawnable() == Events::Spawnable::Planet)
       {
            //Planet::spawn();
           std::cout<<"SpawnPlanet!\n";
            return true;
       }
       return false;
    }
}}
