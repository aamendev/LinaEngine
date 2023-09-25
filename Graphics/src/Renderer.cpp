#include "../Renderer.h"
#include "../../ECS/include/ECSManager.h"
#include "../../ECS/include/component.h"
#include "../../ECS/include/components.h"
namespace Lina{ namespace Manager{

    void Renderer::enableCulling(){
        glEnable(GL_CULL_FACE);
    }
    void Renderer::enableBlending(GLenum blendingFunction1, GLenum blendingFunction2){
        glEnable(GL_BLEND);
        glBlendFunc(blendingFunction1, blendingFunction2);
    }
    void Renderer::disableBlending(){
        glDisable(GL_BLEND);
    }
    void Renderer::disableCulling(){
        glDisable(GL_CULL_FACE);
    }
    void Renderer::setFrontFace(GLenum face){
      glFrontFace(face);
    }
    void Renderer::drawIndexed(const IndexedDrawingSpecifications& ispec){
	    glDrawElements(ispec.primitive, ispec.size, ispec.dataType, ispec.dataPointer);
    }
    IndexedDrawingSpecifications Renderer::setup(const ECS::Entity& entity)
    {
        ECS::Component::Type renderType = ECS::Component::Type::Render;
        ECS::Component::Render* render = dynamic_cast<ECS::Component::Render*>(entity.findComponent(renderType));
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
        //Lina::Graphics::clearGL();
        enableCulling();
        setFrontFace(GL_CCW);
        return {GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr};
    }
    void Renderer::drawArray(const ArrayDrawingSpecifications& aspec){
	    glDrawArrays(aspec.primitive, aspec.first, aspec.count);
    }
    void Renderer::setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int heigth)
    {
        glViewport(x, y, width, heigth);
    }
}}
