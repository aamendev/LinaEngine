#include "../Texture.h"
#include "../stb_image.h"
namespace Lina { namespace Graphics{
    static int slotCounter = 0;
    Texture::Texture(const std::string& path, bool flip):mRenderId(0), mPath(path)
    {
        setTextureFromPath(path, flip);
    }
    void Texture::setTextureFromPath(const std::string& path, bool flip)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(flip);
		stbi_uc* data = nullptr;
        {
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }
        if (data)
        {
            mWidth = width;
            mHeight = height;
            GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}
            mInternalFormat = internalFormat;
            mDataFormat = dataFormat;
            glGenTextures(1, &mRenderId);
            glActiveTexture(GL_TEXTURE0 + slotCounter++);
            glBindTexture(GL_TEXTURE_2D, mRenderId);
            std::cout<<"\nCurrent SlotL "<<slotCounter<<'\n';

            glTextureParameteri(mRenderId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(mRenderId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(mRenderId, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(mRenderId, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexImage2D(GL_TEXTURE_2D,
                            0, mInternalFormat,
                            mWidth, mHeight,
                            0, mDataFormat,
                            GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            std::cout<<"Generated\n";
                }
    }
    Texture::~Texture(){
        glDeleteTextures(1, &mRenderId);
    }
    void Texture::setData(void * data, unsigned int size){
        unsigned int depth = 4 * (mDataFormat == GL_RGBA) + 3 * !(mDataFormat == GL_RGBA);
        if (size == depth * mWidth * mHeight){

            glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0, 0,
                    mWidth, mHeight,
                    mDataFormat, GL_UNSIGNED_BYTE,
                    data);
                }
        else{
            std::cerr<<"Size must be entire image!\n";
        }
    }
    void Texture::bind(unsigned int slot) const{
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, mRenderId);
    }
    void Texture::bind() const{
        for (int i = 0; i < slotCounter; i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, mRenderId);
        }
    }
    void Texture::unbind() const{
    }
}}
