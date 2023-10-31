#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
namespace Lina{namespace Graphics{
	class VertexArray{
	private:
		unsigned int mRenderId;
	public:
		VertexArray();
		~VertexArray();
        unsigned int getId() {return mRenderId;}
		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void addAccurateBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void bind() const;
		void unbind() const;
	};
}}
