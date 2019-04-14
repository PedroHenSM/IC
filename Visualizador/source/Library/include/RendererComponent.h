#pragma once

#include "Common.h"

namespace Library
{
	class Renderer;
	class RendererTime;

	class RendererComponent : public RTTI
	{
		RTTI_DECLARATIONS(RendererComponent, RTTI)

	public:
		RendererComponent();
		RendererComponent(Renderer& renderer);
		virtual ~RendererComponent();

		Renderer* GetRenderer();
		void SetRenderer(Renderer& renderer);
		bool Enabled() const;
		void SetEnabled(bool enabled);

		virtual void Initialize();
		virtual void Update(const RendererTime& rendererTime);

	protected:
		Renderer* mRenderer;
		bool mEnabled;

	private:
		RendererComponent(const RendererComponent& rhs);
		RendererComponent& operator=(const RendererComponent& rhs);
	};
}