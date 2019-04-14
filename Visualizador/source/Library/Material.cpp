#include "Material.h"
#include "Shader.h"
#include "Transform.h"
#include "RendererObject.h"

namespace Library
{
    unsigned int Material::IDgen = 0;

	Material::Material(std::string vertexShader, std::string fragmentShader)
		: mID(IDgen++), mPosition(0), mTexCoord(0), mNormal(0), mTangent(0), mBitangent(0), mMVP(0), mMV(0),
		  mShader(nullptr), mName(), mNeedToDeleteShader(true), mVertexShaderPath(vertexShader), mFragmentShaderPath(fragmentShader),
		  mMeshUsing(0)
	{
	}

	Material::Material(std::string name)
		: mID(IDgen++),
		  mPosition(0),
		  mTexCoord(0),
		  mNormal(0),
		  mTangent(0),
		  mBitangent(0),
		  mMVP(0),
		  mMV(0),
		  mShader(nullptr),
		  mName(name),
		  mNeedToDeleteShader(true),
		  mVertexShaderPath("../../content/vert.glsl"),
		  mFragmentShaderPath("../../content/frag.glsl"),
		  mMeshUsing(0)
	{
	}

	Material::Material(Shader * shader)
		: mID(IDgen++), mPosition(0), mTexCoord(0), mNormal(0), mTangent(0), mBitangent(0), mMVP(0), mMV(0),
		  mShader(shader), mName(), mNeedToDeleteShader(false) ,mVertexShaderPath(""), mFragmentShaderPath(""),
          mMeshUsing(0)
	{
	}

	Material::~Material()
	{
		if (mNeedToDeleteShader)
			delete mShader;
	}

	void Material::Initialize()
	{
		if (mShader == nullptr)
			mShader = new Shader(mVertexShaderPath, mFragmentShaderPath);

		mPosition = mShader->GetAttribute(ShaderAttributesPosition);
		mTexCoord = mShader->GetAttribute(ShaderAttributesTexCoodinates);
		mNormal = mShader->GetAttribute(ShaderAttributesNormal);
		mTangent = mShader->GetAttribute(ShaderAttributesTangent);
		mBitangent = mShader->GetAttribute(ShaderAttributesBitangents);

		mMVP = mShader->GetUniform("MVP");
		mMV = mShader->GetUniform("MV");
	}

	void Material::Setup(RendererObject &ro)
	{
        glBindVertexArray(ro.mVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, ro.mVertexBuffer);

		glVertexAttribPointer(
			mPosition,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glDisableVertexAttribArray(pos);
		glBindVertexArray(0);
	}

	void Material::Use(const RendererTime& rendererTime, Transform& transform, RendererObject &ro)
	{
		mShader->Use();
		const mat4 &MVP = transform.LocalToScreenMatrix();
		const mat4 &MV = transform.LocalToViewMatrix();

		glUniformMatrix4fv(mMVP, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(mMV, 1, GL_FALSE, &MV[0][0]);

		glBindVertexArray(ro.mVertexArray);
		glEnableVertexAttribArray(mPosition);
		glBindBuffer(GL_ARRAY_BUFFER, ro.mVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro.mIndexBuffer);

		glDrawElements(GL_TRIANGLES, ro.mIndexData.size(), GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(mPosition);
		glBindVertexArray(0);
	}

	GLuint Material::Position() const
	{
		return mPosition;
	}
	GLuint Material::TexCoord() const
	{
		return mTexCoord;
	}
	GLuint Material::Normal() const
	{
		return mNormal;
	}
	GLuint Material::Tangent() const
	{
		return mTangent;
	}
	GLuint Material::Bitangent() const
	{
		return mBitangent;
	}
	unsigned int Material::ID() const
	{
		return mID;
	}

	const std::string Material::Name() const
	{
	    return mName;
	}
}
