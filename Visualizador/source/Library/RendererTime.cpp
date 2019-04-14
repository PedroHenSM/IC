#include "RendererTime.h"

namespace Library
{
	RendererTime::RendererTime() : mTotalRendererTime(0.0), mElapsedRendererTime(0.0)
	{
	}

	double RendererTime::TotalRendererTime() const
	{
		return mTotalRendererTime;
	}

	void RendererTime::SetTotalRendererTime(double totalRendererTime)
	{
		mTotalRendererTime = totalRendererTime;
	}

	double RendererTime::ElapsedRendererTime() const
	{
		return mElapsedRendererTime;
	}

	void RendererTime::SetElapsedRendererTime(double elapsedRendererTime)
	{
		mElapsedRendererTime = elapsedRendererTime;
	}
}