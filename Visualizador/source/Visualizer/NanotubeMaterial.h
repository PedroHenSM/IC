#pragma once

#include "Material.h"
#include "DrawableNanotube.h"

namespace Library
{
    class DrawableNanotube;

    typedef enum _DrawMode
    {
        DrawModeContacts = 0,
        DrawModeSolidColor = 1
    } DrawMode;

    class NanotubeMaterial : public Material
    {
    public:
        NanotubeMaterial();
		//~NanotubeMaterial();

		void Initialize();
		void Setup(DrawableNanotube& dn);
		void Use(const RendererTime& rendererTime, DrawableNanotube& dn);

		void SetColor(vec3 color);

		void SetDrawMode(DrawMode drawmode);
		DrawMode GetDrawMode();

    private:
        GLuint mVertexPositionAttrib;
		GLuint mNormalAttribPosition;
		GLuint mColorAttribPosition;
		GLuint mUVAttribPosition;

		GLuint mMVPUniform;
		GLuint mMVUniform;
		GLuint mNormalMapUniform;
		GLuint mWireMapUniform;
		GLuint mTillingUniform;
		GLuint mDrawModeUniform;
		GLuint mMaterialColor;

		DrawMode mDrawMode;

    };
}
