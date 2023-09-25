#include "../headers/Application.h"

namespace Lina{ namespace Core{
    Application::Application(Graphics::Window& window, Root& root)
    {
        mWindow = &window;
        mRoot = &root;
        mWindow->setEventCallBack(FORWARD_CALL(Application::onEvent));
        mRunning = true;
    }
    void Application::onEvent(Events::Event& e)
    {
        Events::Dispatcher dispatcher(e);
        dispatcher.dispatch<Events::WindowClose>(FORWARD_CALL(Application::onWindowClose));
        dispatcher.dispatch<Events::WindowResize>(FORWARD_CALL(Application::onWindowResize));
    }
    void Application::run()
    {
        std::vector<ECS::Entity> entities= mRoot->mECSManager->getEntities();
        ECS::Entity entity = entities[0];
        ECS::Component::Type renderType = ECS::Component::Type::Render;
        ECS::Component::Type transformType = ECS::Component::Type::Transform;
        ECS::Component::Render* render = dynamic_cast<ECS::Component::Render*>(entity.findComponent(renderType));
        ECS::Component::Transform* trans = dynamic_cast<ECS::Component::Transform*>(entity.findComponent(transformType));
        Graphics::VertexArray va;
        Graphics::Texture tex = render->getTexture();
        Graphics::Renderable obj = render->getRenderable();
        Graphics::VertexBufferLayout layout;
        std::vector<float> vertices = obj.getFullVertices();
        std::vector<unsigned int> indices = obj.getIndices();
        Lina::Graphics::VertexBuffer vb(&vertices[0], vertices.size() * sizeof(vertices[0]));
        Lina::Graphics::IndexBuffer ib(&indices[0], indices.size() * sizeof(indices[0]));
        Lina::Graphics::Shader shader = render->getShader();
        layout.push<float>(3);
        layout.push<float>(2);
        shader.bind();
        vb.bind();
        va.addBuffer(vb, layout);
        va.bind();
        ib.bind();
        tex.bind();
        mRoot->mRenderManager->enableCulling();
        mRoot->mRenderManager->setFrontFace(GL_CCW);
        Manager::IndexedDrawingSpecifications ispec = {GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, nullptr};
        float theta = 0.0f;

        while (mRunning)
        {
            mWindow->clear();
            mRoot->mRenderManager->drawIndexed(ispec);


            Math::Transform4D orientation = trans->getTransform();
            shader.setUniformMat4("rotationMat", orientation);
            trans->updateRotation(theta, Math::Vector3D(0,1,0));
            theta += 0.05f;
            mWindow->update();
            if (mRoot->mInputManager->isKeyPressed(Key::Q))
            {
                std::cout<<"Closing Now...";
                mRunning = false;
            }
        }
    }
    bool Application::onWindowClose(Events::WindowClose& e)
    {
        mRunning = false;
        return true;
    }
    bool Application::onWindowResize(Events::WindowResize& e)
    {
       mRoot->mRenderManager->setViewPort(0, 0, e.getWidth(), e.getHeight());
    }
}}
