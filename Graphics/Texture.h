#pragma once
#include <string>
#include <iostream>
#include "glad.h"
namespace Lina{ namespace Graphics{
   class Texture{
       public:
        Texture() {}
        Texture(const std::string& path, bool flip = false);
        Texture(Texture&& tex)
        {
            Texture(std::move(tex.mPath), true);
        }
        Texture(const Texture& tex)
        {
            Texture(tex.mPath, true);
        }
        ~Texture();
        void setTextureFromPath(const std::string& path, bool flip = false);
        unsigned int getWidth() const { return mWidth;}
        unsigned int getHeight() const {return mHeight;}
        unsigned int getRenderId() const {return mRenderId;}
        const std::string& getPath() const{return mPath;}
        void setData(void * data, unsigned int size);
        void bind(unsigned int slot) const;
        void bind() const;
        void unbind() const;
       private:
        unsigned int mRenderId;
        unsigned int mWidth, mHeight;
        std::string mPath;
        GLenum mInternalFormat, mDataFormat;
   };
}}
