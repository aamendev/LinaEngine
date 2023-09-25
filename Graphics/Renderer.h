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
            IndexedDrawingSpecifications setup(const ECS::Entity& entity);
            void draw(const ECS::Entity& obj);

            void drawArray(const ArrayDrawingSpecifications& aspec);
            void enableCulling();
            void disableCulling();
            void setFrontFace(GLenum face);
            void enableBlending(GLenum blendFunction1, GLenum blendFunction2);
            void disableBlending();
            void setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int heigth);
    };
}}
