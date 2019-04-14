#include "RendererClock.h"
#include "RendererTime.h"

using namespace std::chrono;

namespace Library
{
	RendererClock::RendererClock() : mStartTime(), mCurrentTime(), mLastTime()
	{
		Reset();
	}

	const timePoint& RendererClock::StartTime() const
	{
		return mStartTime;
	}

	const timePoint& RendererClock::CurrentTime() const
	{
		return mCurrentTime;
	}

	const timePoint& RendererClock::LastTime() const
	{
		return mLastTime;
	}

	void RendererClock::Reset()
	{
		GetTime(mStartTime);
		mCurrentTime = mStartTime;
		mLastTime = mCurrentTime;
	}

	void RendererClock::GetTime(timePoint& time) const
	{
		time = high_resolution_clock::now();
	}

	void RendererClock::UpdateRendererTime(RendererTime& rendererTime)
	{
		GetTime(mCurrentTime);

		duration<double> elapsed = duration_cast<duration<double>> (mCurrentTime - mLastTime);
		duration<double> total = duration_cast<duration<double>>(mCurrentTime - mStartTime);

		rendererTime.SetTotalRendererTime(total.count());
		rendererTime.SetElapsedRendererTime(elapsed.count());
		
		mLastTime = mCurrentTime;
	}
}
