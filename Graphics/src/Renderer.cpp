#include "../../Memory/include/MemoryOverload.h"
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
    std::pair<IndexedDrawingSpecifications, DrawData> Renderer::setup(const ECS::Entity& entity)
    {
        enableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        ECS::Component::Type renderType = ECS::Component::Type::Render;
        ECS::Component::Render* render = dynamic_cast<ECS::Component::Render*>(entity.findComponent(renderType));
        Graphics::VertexArray* va = lnew<Graphics::VertexArray>();
        Graphics::Texture* tex = render->getTexture();
        Graphics::Renderable* obj = render->getRenderable();
        Graphics::VertexBufferLayout layout;
        std::vector<float> vertices = obj->getFullVertices();
        std::vector<unsigned int> indices = obj->getIndices();
        Lina::Graphics::VertexBuffer* vb = lnew<Lina::Graphics::VertexBuffer>();
        vb->constructFromDataPointer(&vertices[0], vertices.size() * sizeof(vertices[0]));
        Lina::Graphics::IndexBuffer* ib = lnew<Lina::Graphics::IndexBuffer>();
        ib->constructFromDataPointer(&indices[0], indices.size() * sizeof(indices[0]));
        Lina::Graphics::Shader* shader = render->getShader();
        layout.push<float>(3);
        layout.push<float>(2);
        va->addBuffer(*vb, layout);
        enableCulling();
        setFrontFace(GL_CCW);
        IndexedDrawingSpecifications ispec =
        {
            GL_TRIANGLES, (unsigned int)indices.size(),
            GL_UNSIGNED_INT, nullptr
        };
        DrawData data = {tex, va, vb, ib, shader};
        return {ispec, data};
    }

    std::pair<IndexedDrawingSpecifications, DrawData> Renderer::setup(const ECS::Entity&& entity)
    {
        enableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        ECS::Component::Type renderType = ECS::Component::Type::Render;
        ECS::Component::Render* render = dynamic_cast<ECS::Component::Render*>(entity.findComponent(renderType));
        Graphics::VertexArray* va = lnew<Graphics::VertexArray>();
        Graphics::Texture* tex = render->getTexture();
        Graphics::Renderable* obj = render->getRenderable();
        Graphics::VertexBufferLayout layout;
        std::vector<float> vertices = obj->getFullVertices();
        std::vector<unsigned int> indices = obj->getIndices();
        Lina::Graphics::VertexBuffer* vb = lnew<Lina::Graphics::VertexBuffer>();
        vb->constructFromDataPointer(&vertices[0], vertices.size() * sizeof(vertices[0]));
        Lina::Graphics::IndexBuffer* ib = lnew<Lina::Graphics::IndexBuffer>();
        ib->constructFromDataPointer(&indices[0], indices.size() * sizeof(indices[0]));
        Lina::Graphics::Shader* shader = render->getShader();
        layout.push<float>(3);
        layout.push<float>(2);
        va->addBuffer(*vb, layout);
        enableCulling();
        setFrontFace(GL_CCW);
        IndexedDrawingSpecifications ispec =
        {
            GL_TRIANGLES, (unsigned int)indices.size(),
            GL_UNSIGNED_INT, nullptr
        };
        DrawData data = {tex, va, vb, ib, shader};
        return {ispec, data};
    }

    std::pair<IndexedDrawingSpecifications, DrawData> Renderer::setup(Graphics::Renderable& r)
    {
        enableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        Graphics::VertexArray* va = lnew<Graphics::VertexArray>();
        Graphics::Renderable* obj = &r;
        Graphics::VertexBufferLayout layout;
        std::vector<float> vertices = obj->getFullVertices();
        std::vector<unsigned int> indices = obj->getIndices();
        Lina::Graphics::VertexBuffer* vb = lnew<Lina::Graphics::VertexBuffer>();
        vb->constructFromDataPointer(&vertices[0], vertices.size() * sizeof(vertices[0]));
        Lina::Graphics::IndexBuffer* ib = lnew<Lina::Graphics::IndexBuffer>();
        ib->constructFromDataPointer(&indices[0], indices.size() * sizeof(indices[0]));
        layout.push<float>(3);
        layout.push<float>(2);
        va->addBuffer(*vb, layout);
        enableCulling();
        setFrontFace(GL_CCW);
        IndexedDrawingSpecifications ispec =
        {
            GL_TRIANGLES, (unsigned int)indices.size(),
            GL_UNSIGNED_INT, nullptr
        };
        DrawData data = {nullptr, va, vb, ib, nullptr};
        return {ispec, data};
    }

    std::pair<IndexedDrawingSpecifications, DrawData> Renderer::setup(Graphics::Renderable&& r)
    {
        enableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        Graphics::VertexArray* va = lnew<Graphics::VertexArray>();
        Graphics::Renderable* obj = &r;
        Graphics::VertexBufferLayout layout;
        std::vector<float> vertices = obj->getFullVertices();
        std::vector<unsigned int> indices = obj->getIndices();
        Lina::Graphics::VertexBuffer* vb = lnew<Lina::Graphics::VertexBuffer>();
        vb->constructFromDataPointer(&vertices[0], vertices.size() * sizeof(vertices[0]));
        Lina::Graphics::IndexBuffer* ib = lnew<Lina::Graphics::IndexBuffer>();
        ib->constructFromDataPointer(&indices[0], indices.size() * sizeof(indices[0]));
        layout.push<float>(3);
        layout.push<float>(2);
        va->addBuffer(*vb, layout);
        enableCulling();
        setFrontFace(GL_CCW);
        IndexedDrawingSpecifications ispec =
        {
            GL_TRIANGLES, (unsigned int)indices.size(),
            GL_UNSIGNED_INT, nullptr
        };
        DrawData data = {nullptr, va, vb, ib, nullptr};
        return {ispec, data};
    }

    void Renderer::bind(const DrawData& d)
    {
        d.va->bind();
        d.tex->bind();
        d.vb->bind();
        d.ib->bind();
        d.shader->bind();
    }
    void Renderer::freeDrawData(DrawData& data)
    {
        ldelete(data.va);
        ldelete(data.vb);
        ldelete(data.ib);
    }
    void Renderer::drawArray(const ArrayDrawingSpecifications& aspec){
	    glDrawArrays(aspec.primitive, aspec.first, aspec.count);
    }
    void Renderer::setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int heigth)
    {
        glViewport(x, y, width, heigth);
    }
}}
