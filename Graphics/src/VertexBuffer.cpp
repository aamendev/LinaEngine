#include "../VertexBuffer.h"
namespace Lina{namespace Graphics{
	VertexBuffer::VertexBuffer(const void* data, unsigned int size){
		glGenBuffers(1, &mRenderId);
		glBindBuffer(GL_ARRAY_BUFFER, mRenderId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	VertexBuffer::~VertexBuffer(){
        unbind();
		glDeleteBuffers(1, &mRenderId);
	}
	void VertexBuffer::bind() const{
		glBindBuffer(GL_ARRAY_BUFFER, mRenderId);
	}
	void VertexBuffer::unbind() const{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}}
