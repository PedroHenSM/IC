#pragma once

#include <chrono>

typedef std::chrono::high_resolution_clock::time_point timePoint;

namespace Library
{
	class RendererTime;

	class RendererClock
	{
	public:
		RendererClock();

		const timePoint& StartTime() const;
		const timePoint& CurrentTime() const;
		const timePoint& LastTime() const;

		void Reset();
		void GetTime(timePoint& time) const;
		void UpdateRendererTime(RendererTime& rendererTime);

	private:
		RendererClock(const RendererClock& rhs);
		RendererClock& operator=(const RendererClock& rhs);

		timePoint mStartTime;
		timePoint mCurrentTime;
		timePoint mLastTime;
	};
}