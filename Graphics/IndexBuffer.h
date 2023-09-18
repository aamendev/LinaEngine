#pragma once
#include "glad.h"
namespace Lina{namespace Graphics{

	class IndexBuffer{
	private:
		unsigned int mRenderId;
		unsigned int mCount;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;
		inline unsigned int getCount() {return mCount;}
	};
}}
