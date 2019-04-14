#pragma once

#include "RendererComponent.h"

namespace Library
{
	class Camera;

	class DrawableComponent : public RendererComponent
	{
		RTTI_DECLARATIONS(DrawableComponent, RendererComponent)

	public:
		DrawableComponent();
		DrawableComponent(Renderer& renderer);
		DrawableComponent(Renderer& renderer, Camera& camera);
		virtual ~DrawableComponent();

		bool Visible() const;
		void SetVisible(bool visible);

		Camera* GetCamera();
		void SetCamera(Camera* camera);

		virtual void Draw(const RendererTime& rendererTime);

	protected:
		bool mVisible;
		Camera* mCamera;

	private:
		DrawableComponent(const DrawableComponent& rhs);
		DrawableComponent& operator=(const DrawableComponent& rhs);
	};
}