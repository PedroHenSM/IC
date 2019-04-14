#pragma once

#include "Material.h"
#include "DrawableNanotube.h"

namespace Library
{
    class DrawableNanotube;

    class LineMaterial
    {
    public:
        LineMaterial();
		~LineMaterial();

		void Initialize();
		void Setup(DrawableNanotube& dn);
		void Use(const RendererTime& rendererTime, DrawableNanotube& dn);

    private:
        GLuint mVertexPositionAttrib;

		GLuint mMVPUniform;
		GLuint mMVUniform;

		Shader* mShader;

    };
}
