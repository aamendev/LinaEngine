#include "../utilities.h"
namespace Lina{namespace Graphics{
	void clearGL(){
		glUseProgram(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
		}
	// void bindBufferWithLayout(const VertexBuffer& vb, const VertexBufferLayout& layout){
	// 	vb.bind();
	// 	const auto& elements = layout.getElements();
	// 	unsigned int offset = 0;
	// 	for (unsigned int i = 0; i < elements.size(); i++){
	// 		const auto& element = elements[i];
	// 		glEnableVertexAttribArray(i);
	// 		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), offset);
	// 		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	// 	}
	// }
}}
