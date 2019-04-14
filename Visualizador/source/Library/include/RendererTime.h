#pragma once

namespace Library
{
	class RendererTime
	{
	public:
		RendererTime();

		double TotalRendererTime() const;
		void SetTotalRendererTime(double totalRendererTime);

		double ElapsedRendererTime() const;
		void SetElapsedRendererTime(double elapsedRendererTime);

	private:
		double mTotalRendererTime;
		double mElapsedRendererTime;
	};
}