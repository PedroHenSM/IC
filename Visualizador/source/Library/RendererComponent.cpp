#include "RendererComponent.h"
#include "RendererTime.h"

namespace Library
{
	RTTI_DEFINITIONS(RendererComponent)

	RendererComponent::RendererComponent() : mRenderer(nullptr), mEnabled(true)
	{}

	RendererComponent::RendererComponent(Renderer& renderer) : mRenderer(&renderer), mEnabled(true)
	{}

	RendererComponent::~RendererComponent()
	{}

	Renderer* RendererComponent::GetRenderer()
	{
		return mRenderer;
	}

	void RendererComponent::SetRenderer(Renderer& renderer)
	{
		mRenderer = &renderer;
	}

	bool RendererComponent::Enabled() const
	{
		return mEnabled;
	}

	void RendererComponent::SetEnabled(bool enabled)
	{
		mEnabled = enabled;
	}

	void RendererComponent::Initialize()
	{}

	void RendererComponent::Update(const RendererTime& rendererTime)
	{}
}