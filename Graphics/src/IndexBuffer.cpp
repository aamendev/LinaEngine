#include "../IndexBuffer.h"
namespace Lina{namespace Graphics{
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count){
        constructFromDataPointer(data, count);
	}
	IndexBuffer::~IndexBuffer(){
        unbind();
		glDeleteBuffers(1, &mRenderId);
	}
    void IndexBuffer::constructFromDataPointer(const unsigned int* data, unsigned int count)
    {
        mCount = count;
		glGenBuffers(1, &mRenderId);
		glBindBuffer(GL_ARRAY_BUFFER, mRenderId);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }
	void IndexBuffer::bind() const{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderId);
	}
	void IndexBuffer::unbind() const{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}}
