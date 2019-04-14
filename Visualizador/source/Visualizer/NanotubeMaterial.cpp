#include "NanotubeMaterial.h"
#include "Shader.h"

namespace Library
{
    NanotubeMaterial::NanotubeMaterial() : Material("", ""), mDrawMode(DrawModeContacts)
    {

    }

    void NanotubeMaterial::Initialize()
    {
        mShader = new Shader("../../content/vert.glsl", "../../content/frag.glsl");
        mShader->Use();

        mVertexPositionAttrib = mShader->GetAttribute(ShaderAttributesPosition);
        mNormalAttribPosition = mShader->GetAttribute(ShaderAttributesNormal);
        mColorAttribPosition = mShader->GetAttribute(ShaderAttributesColor);
        mUVAttribPosition = mShader->GetAttribute(ShaderAttributesTexCoodinates);

        mMVPUniform = mShader->GetUniform("MVP");
        mMVUniform = mShader->GetUniform("MV");
        mNormalMapUniform = mShader->GetUniform("NormalMap");
        mWireMapUniform = mShader->GetUniform("WireMap");
        mTillingUniform = mShader->GetUniform("tilling");
        mDrawModeUniform = mShader->GetUniform("DrawMode");
        mMaterialColor = mShader->GetUniform("MaterialColor");
        glUseProgram(0);
    }

    void NanotubeMaterial::Setup(DrawableNanotube &dn)
    {
        // Setup Shader Attribute Array
        mShader->Use();
        glBindVertexArray(dn.mVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, dn.mVertexBuffer);

		glVertexAttribPointer(
			mVertexPositionAttrib,
			3,
			GL_FLOAT,
			GL_FALSE,
			(48),
			(void*) 0
			);

        glVertexAttribPointer(
			mNormalAttribPosition,
			3,
			GL_FLOAT,
			GL_FALSE,
			(48),
			(void*) (12)
			);

        glVertexAttribPointer(
            mColorAttribPosition,
            3,
            GL_FLOAT,
            GL_FALSE,
            (48),
            (void*) (24)
        );

        glVertexAttribPointer(
            mUVAttribPosition,
            2,
            GL_FLOAT,
            GL_FALSE,
            (48),
            (void*) (36)
        );

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		glUniform1d(mDrawModeUniform, mDrawMode);
    }

    void NanotubeMaterial::Use(const RendererTime& rendererTime, DrawableNanotube &dn)
    {
        mShader->Use();
		const mat4 &MVP = dn.mTransform.LocalToScreenMatrix();
		const mat4 &MV = dn.mTransform.LocalToViewMatrix();

		glUniformMatrix4fv(mMVPUniform, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(mMVUniform, 1, GL_FALSE, &MV[0][0]);
		glUniform1f(mTillingUniform, dn.mTilling);

		/*glUniform1i(mNormalMapUniform, 0);
        glActiveTexture(GL_TEXTURE0);
        mNormalTexture->Use();

        glUniform1i(mWireMapUniform, 1);
        glActiveTexture(GL_TEXTURE1);
        mWireTexture->Use();*/

		glBindVertexArray(dn.mVertexArray);

		glEnableVertexAttribArray(mVertexPositionAttrib);
		glEnableVertexAttribArray(mNormalAttribPosition);
		glEnableVertexAttribArray(mColorAttribPosition);
		glEnableVertexAttribArray(mUVAttribPosition);

		glBindBuffer(GL_ARRAY_BUFFER, dn.mVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dn.mIndexBuffer);

		glDrawElements(GL_TRIANGLES, dn.mIndexNumber, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(mVertexPositionAttrib);
		glDisableVertexAttribArray(mNormalAttribPosition);
		glDisableVertexAttribArray(mColorAttribPosition);
		glDisableVertexAttribArray(mUVAttribPosition);

		glBindVertexArray(0);
		glUseProgram(0);
    }

    DrawMode NanotubeMaterial::GetDrawMode()
    {
        return mDrawMode;
    }

    void NanotubeMaterial::SetDrawMode(DrawMode drawmode)
    {
        mShader->Use();
        mDrawMode = drawmode;
        glUniform1i(mDrawModeUniform, mDrawMode);
    }

    void NanotubeMaterial::SetColor(vec3 color)
    {
        mShader->Use();
        glUniform3fv(mMaterialColor, 1, &color[0]);
    }
}
