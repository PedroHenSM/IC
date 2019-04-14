#pragma once

#include "Common.h"

namespace Library
{
	enum ImageFormat
	{
		ImageFormatR = 1,
		ImageFormatRG = 2,
		ImageFormatRGB = 3,
		ImageFormatRGBA = 4
	};

	class Image
	{
	public:
		Image(std::string texturePath);
		~Image();

		const unsigned char* GetData() const;
		int Width() const;
		int Height() const;

		GLenum Format() const;

	private:
		int mWidth;
		int mHeight;

		unsigned char* mData;

		ImageFormat mImageFormat;


	private:
	};
}