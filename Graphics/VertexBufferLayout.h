#pragma once
#include <vector>
#include <iostream>
#include "glad.h"
namespace Lina{namespace Graphics{
	struct VertexBufferElement{
		unsigned int type;
		unsigned int count;
		unsigned char normalised;
		static unsigned int getSizeOfType(unsigned int type){
			switch (type){
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			}
			return 0;
		}
	};
	class VertexBufferLayout{
	private:
		std::vector<VertexBufferElement> mElements;
		unsigned int mStride;
	public:
		VertexBufferLayout() :mStride(0){};

		template<typename T>
		void push(unsigned int count);
		inline const std::vector<VertexBufferElement> getElements() const {return mElements;}
		inline unsigned int getStride() const {return mStride;}
	};
}}