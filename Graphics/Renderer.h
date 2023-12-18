#pragma once
#include "../main/LinaGraphics.h"
#include "../Graphics/Renderable.h"
#include "../ECS/include/Entity.h"
namespace Lina{ namespace Manager{
    struct IndexedDrawingSpecifications
    {
	    GLenum primitive;
        unsigned int size;
        GLenum dataType;
        const void *dataPointer;
    };
    struct DrawData
    {
        Graphics::Texture* tex;
        Graphics::VertexArray* va;
        Graphics::VertexBuffer* vb;
        Graphics::IndexBuffer* ib;
        Graphics::Shader* shader;
    };
    struct ArrayDrawingSpecifications
    {
	    GLenum primitive;
        unsigned int count;
        unsigned int first;
    };
    class Renderer
    {
        public:
            Renderer() = default;
            void drawIndexed(const IndexedDrawingSpecifications& ispec);
            std::pair<IndexedDrawingSpecifications, DrawData> setup(const ECS::Entity& entity);
            std::pair<IndexedDrawingSpecifications, DrawData> setup(const ECS::Entity&& entity);
            std::pair<IndexedDrawingSpecifications, DrawData> setup(Graphics::Renderable&& r);
            std::pair<IndexedDrawingSpecifications, DrawData> setup(Graphics::Renderable& r);
            void draw(const ECS::Entity& obj);

            void bind(const DrawData&);
            void loadGL() {gladLoadGL();}
            void freeDrawData(DrawData& data);
            void drawArray(const ArrayDrawingSpecifications& aspec);
            void enableCulling();
            void disableCulling();
            void setFrontFace(GLenum face);
            void enableBlending(GLenum blendFunction1, GLenum blendFunction2);
            void disableBlending();
            void setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int heigth);
    };
}}
