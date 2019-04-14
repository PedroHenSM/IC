#include "RendererObject.h"
#include "Shader.h"
#include "RendererTime.h"
#include "Camera.h"
#include "Material.h"

namespace Library
{
	RTTI_DEFINITIONS(RendererObject)

	RendererObject::RendererObject(Renderer& renderer, Camera& camera, Shader& shader) :
	    DrawableComponent(renderer, camera),
        mTransform(),
        mVertexData(),
        mIndexData(),
        mMaterial(nullptr),
        mShader(&shader),
        mVertexBuffer(0),
        mIndexBuffer(0),
        mVertexArray(0)
	{
	}

	RendererObject::~RendererObject()
	{
		glDeleteBuffers(1, &mVertexBuffer);
		glDeleteBuffers(1, &mIndexBuffer);
		glDeleteVertexArrays(1, &mVertexArray);
	}

	void RendererObject::Initialize()
	{
		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);

		glGenBuffers(1, &mVertexBuffer);
		glGenBuffers(1, &mIndexBuffer);

		mVertexData.push_back(vec3(0.0, 0.5, 0.0));
		mVertexData.push_back(vec3(-0.5, -0.5, 0.5));
		mVertexData.push_back(vec3(0.5, -0.5, 0.5));
		mVertexData.push_back(vec3(0.5, -0.5, -0.5));
		mVertexData.push_back(vec3(-0.5, -0.5, -0.5));

		mIndexData.push_back(0);
		mIndexData.push_back(1);
		mIndexData.push_back(2);
		mIndexData.push_back(0);
		mIndexData.push_back(2);
		mIndexData.push_back(3);
		mIndexData.push_back(0);
		mIndexData.push_back(3);
		mIndexData.push_back(4);
		mIndexData.push_back(0);
		mIndexData.push_back(4);
		mIndexData.push_back(1);

		mIndexData.push_back(1);
		mIndexData.push_back(3);
		mIndexData.push_back(2);

		mIndexData.push_back(1);
		mIndexData.push_back(4);
		mIndexData.push_back(3);


		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * mVertexData.size(), mVertexData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*mIndexData.size(), mIndexData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		mTransform.Translate(vec3(0, 0, -3));

		mMaterial = new Material("../../content/vert.glsl", "../../content/frag.glsl");
		mMaterial->Initialize();
		mMaterial->Setup(*this);
	}

	void RendererObject::Draw(const RendererTime& rendererTime)
	{
		mTransform.Rotate(vec3(0.0f, 45.0f * rendererTime.ElapsedRendererTime(), 0.0f));
		mTransform.UpdateCameraMatrix(*mCamera);
		mMaterial->Use(rendererTime, mTransform, *this);
	}
}
