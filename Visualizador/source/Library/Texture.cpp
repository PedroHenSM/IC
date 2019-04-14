#include "Texture.h"
#include "Image.h"
#include "Utility.h"

namespace Library
{
	Texture::Texture(int width, int height, TextureType type, TextureFormat format)
		: mID(0),
		  mTextureType(type),
		  mTextureFormat(format)
	{
		glGenTextures(1, &mID);
		glBindTexture(type, mID);


		if (mTextureType == TextureTypeTexture2D)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}



		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(std::string& texturePath, TextureFormat format)
		: mID(0),
          mTextureType(TextureTypeTexture2D),
          mTextureFormat(format)
	{
		Image image(Utility::GetPath(texturePath));

		glGenTextures(1, &mID);
		glBindTexture(GL_TEXTURE_2D, mID);

		glTexImage2D(GL_TEXTURE_2D, 0, format, image.Width(), image.Height(), 0, image.Format(), GL_UNSIGNED_BYTE, image.GetData());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(std::string* cubemapPath, TextureFormat format)
		: mID(0),
          mTextureType(TextureTypeCubemap),
          mTextureFormat(format)
	{
		glGenTextures(1, &mID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mID);

		for (int i = 0; i < 6; i++)
		{
			Image image(Utility::GetPath(cubemapPath[i]));

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, image.Format(), image.Width(), image.Height(), 0, image.Format(), GL_UNSIGNED_BYTE, image.GetData());
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mID);
	}

	TextureType Texture::GetTextureType() const
	{
		return mTextureType;
	}

	void Texture::Use()
	{
		glBindTexture(mTextureType, mID);
	}

	void Texture::Release()
	{
		glBindTexture(mTextureType, 0);
	}
}
