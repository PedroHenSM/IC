#include "DrawableComponent.h"

namespace Library
{
	RTTI_DEFINITIONS(DrawableComponent)

	DrawableComponent::DrawableComponent() : RendererComponent(), mVisible(true), mCamera(nullptr)
	{}

	DrawableComponent::DrawableComponent(Renderer& renderer) : RendererComponent(renderer), mVisible(true), mCamera(nullptr)
	{}

	DrawableComponent::DrawableComponent(Renderer& renderer, Camera& camera) : RendererComponent(renderer), mVisible(true), mCamera(&camera)
	{}

	DrawableComponent::~DrawableComponent()
	{}

	bool DrawableComponent::Visible() const
	{
		return mVisible;
	}

	void DrawableComponent::SetVisible(bool visible)
	{
		mVisible = visible;
	}

	Camera * DrawableComponent::GetCamera()
	{
		return mCamera;
	}

	void DrawableComponent::SetCamera(Camera * camera)
	{
		mCamera = camera;
	}

	void DrawableComponent::Draw(const RendererTime& rendererTime)
	{}
}