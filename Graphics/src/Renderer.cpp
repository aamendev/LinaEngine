#include "../Renderer.h"
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
    void Renderer::drawArray(const ArrayDrawingSpecifications& aspec){
	    glDrawArrays(aspec.primitive, aspec.first, aspec.count);
    }
    void Renderer::setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int heigth)
    {
        glViewport(x, y, width, heigth);
    }
}}
