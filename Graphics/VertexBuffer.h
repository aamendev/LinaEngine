#pragma once
#include "glad.h"
namespace Lina{namespace Graphics{

	class VertexBuffer{
	private:
		unsigned int mRenderId;
	public:
        VertexBuffer() {}
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

        void constructFromDataPointer(const void* data, unsigned int size);
		void bind() const;
		void unbind() const;
	};
}}
