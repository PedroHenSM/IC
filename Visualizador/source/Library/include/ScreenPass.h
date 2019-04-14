#pragma once

#include "Common.h"
#include "DrawableComponent.h"
#include "Shader.h"

namespace Library
{
    class ScreenPass : public DrawableComponent
    {
    RTTI_DECLARATIONS(ScreenPass, DrawableComponent)

	public:
		ScreenPass();
		ScreenPass(Renderer& renderer);
		ScreenPass(Renderer& renderer, Camera& camera, Shader& shader);
		virtual ~ScreenPass();

		bool Visible() const;
		void SetVisible(bool visible);

		Camera* GetCamera();
		void SetCamera(Camera* camera);

        virtual void Initialize();
		virtual void Draw(const RendererTime& rendererTime);

	protected:
		bool mVisible;
		Camera* mCamera;
		Shader* mShader;

		GLuint mVertexArray;

	private:
		ScreenPass(const ScreenPass& rhs);
		ScreenPass& operator=(const ScreenPass& rhs);
    };
}
