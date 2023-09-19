#pragma once
#include "../main/LinaGraphics.h"
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
            void drawArray(const ArrayDrawingSpecifications& aspec);
            void enableCulling();
            void disableCulling();
            void setFrontFace(GLenum face);
            void enableBlending(GLenum blendFunction1, GLenum blendFunction2);
            void disableBlending();
    };
}}
