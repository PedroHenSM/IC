#pragma once

#include "Common.h"

namespace Library
{
	enum TextureType
	{
		TextureTypeTexture2D = 0x0DE1,
		TextureTypeCubemap = 0x8513
	};

	enum TextureFormat
	{
		TextureFormatRGB = GL_RGB8,
		TextureFormatRGBA = GL_RGBA8,
		TextureFormatRGB32F = 0,
		TextureFormatRGBA32F = 0,
		TextureFormatRGB16F = GL_RGB16,
		TextureFormatRGBA16F = GL_RGBA16,
		TextureFormatDepth16 = GL_DEPTH_COMPONENT16,
		TextureFormatDepth24 = GL_DEPTH_COMPONENT24,
		TextureFormatDepth32 = GL_DEPTH_COMPONENT32
	};

	class Image;

	class Texture
	{
	public:
		Texture(int width, int height, TextureType type, TextureFormat format);
		Texture(std::string& texturePath, TextureFormat format);
		Texture(std::string* cubemapPath, TextureFormat format);
		~Texture();

		TextureType GetTextureType() const;

		void Use();
		void Release();

		GLuint ID() const;

	private:
		GLuint mID;
		TextureType mTextureType;
		TextureFormat mTextureFormat;
		GLenum mGLTextureType;

		Texture(const Texture& rhs);
		Texture& operator=(const Texture& rhs);
	};
}
