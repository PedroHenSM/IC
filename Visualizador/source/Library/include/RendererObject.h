//NEED MATERIAL

#pragma once

#include "DrawableComponent.h"
#include "Transform.h"

namespace Library
{

	class Material;
	class Shader;

	class RendererObject : public DrawableComponent
	{
        friend class Material;
		RTTI_DECLARATIONS(RendererObject, DrawableComponent)

	public:
		RendererObject(Renderer& renderer, Camera& camera, Shader& shader);
		~RendererObject();

		void Initialize() override;
		void Draw(const RendererTime& rendererTime) override;

	private:
		Transform mTransform;
		std::vector<vec3> mVertexData;
		std::vector<GLushort> mIndexData;

		Material* mMaterial;
		Shader* mShader;

		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLuint mVertexArray;

	private:

	};
}
