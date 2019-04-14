#include "LineMaterial.h"
#include "Shader.h"

namespace Library
{
    LineMaterial::LineMaterial()
    {

    }

	LineMaterial::~LineMaterial()
	{
        delete mShader;
	}

    void LineMaterial::Initialize()
    {
        mShader = new Shader("../../content/lineVert.glsl", "../../content/lineFrag.glsl");

        mShader->Use();
        mVertexPositionAttrib = mShader->GetAttribute(ShaderAttributesPosition);

        mMVPUniform = mShader->GetUniform("MVP");
        mMVUniform = mShader->GetUniform("MV");
        glUseProgram(0);
    }

    void LineMaterial::Setup(DrawableNanotube &dn)
    {
        // Setup Shader Attribute Array
        mShader->Use();
        glBindVertexArray(dn.mLineVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, dn.mLineVertexBuffer);

		glVertexAttribPointer(
			mVertexPositionAttrib,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*) 0
			);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
        glUseProgram(0);
    }

    void LineMaterial::Use(const RendererTime& rendererTime, DrawableNanotube &dn)
    {
        mShader->Use();
		const mat4 &MVP = dn.mTransform.LocalToScreenMatrix();
		const mat4 &MV = dn.mTransform.LocalToViewMatrix();

		glUniformMatrix4fv(mMVPUniform, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(mMVUniform, 1, GL_FALSE, &MV[0][0]);

		//glUniform1i(mNormalMapUniform, 0);
        //glActiveTexture(GL_TEXTURE0);
        //mNormalTexture->Use();

        //glUniform1i(mWireMapUniform, 1);
        //glActiveTexture(GL_TEXTURE1);
        //mWireTexture->Use();

		glBindVertexArray(dn.mLineVertexArray);

		glEnableVertexAttribArray(mVertexPositionAttrib);

		glBindBuffer(GL_ARRAY_BUFFER, dn.mLineVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dn.mLineIndexBuffer);

		glDrawElements(GL_LINE_STRIP, dn.mLineIndexNumber, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(mVertexPositionAttrib);

		glBindVertexArray(0);
    }
}
