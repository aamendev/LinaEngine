#include "../VertexArray.h"
#include "../glad.h"
namespace Lina{namespace Graphics{
	VertexArray::VertexArray(){
		glGenVertexArrays(1, &mRenderId);
	}
	VertexArray::~VertexArray(){
        unbind();
		glDeleteVertexArrays(1, &mRenderId);
	}
	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
		bind();
		vb.bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++){
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type,
			 element.normalised, layout.getStride(),reinterpret_cast<const void*>(offset));
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}
	void VertexArray::addAccurateBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
		bind();
		vb.bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++){
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribIPointer(i, element.count, element.type,
			 layout.getStride(),reinterpret_cast<const void*>(offset));
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}
	void VertexArray::bind() const{
		glBindVertexArray(mRenderId);
	}
	void VertexArray::unbind() const{
		glBindVertexArray(0);
	}
}}
