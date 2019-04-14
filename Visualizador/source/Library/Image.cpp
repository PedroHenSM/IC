#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Image.h"

namespace Library
{
	Image::Image(std::string texturePath)
		: mWidth(0), mHeight(0), mData(nullptr), mImageFormat(ImageFormatRGB)
	{
		int channels;
		mData = stbi_load(texturePath.c_str(), &mWidth, &mHeight, &channels, 0);

		mImageFormat = (ImageFormat)channels;
	}

	Image::~Image()
	{
		stbi_image_free(mData);
	}
	const unsigned char * Image::GetData() const
	{
		return mData;
	}
	int Image::Width() const
	{
		return mWidth;
	}
	int Image::Height() const
	{
		return mHeight;
	}

	GLenum Image::Format() const
	{
		switch (mImageFormat)
		{
		case ImageFormatR:
			return GL_R;
		case ImageFormatRG:
			return GL_RG;
		case ImageFormatRGB:
			return GL_RGB;
		case ImageFormatRGBA:
			return GL_RGBA;
		default:
			return 0;
		}
	}
}
