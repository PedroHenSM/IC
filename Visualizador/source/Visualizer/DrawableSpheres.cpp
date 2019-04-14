#include "DrawableSpheres.h"
#include <GL/glu.h>

#include <iostream>

namespace Library
{

    RTTI_DEFINITIONS(DrawableSpheres)

    DrawableSpheres::DrawableSpheres(Renderer& renderer, Camera& camera, int slices, int stacks)
      : DrawableComponent(renderer, camera),
        mSphereData(),
        mVertexBuffer(0),
        mIndexBuffer(0),
        mVertexArray(0),
        mTransform(),
        mSlices(slices),
        mStacks(stacks),
        mTotalSpheres(0)
    {

    }

    DrawableSpheres::~DrawableSpheres()
    {

    }

    void DrawableSpheres::Initialize()
    {
        mShader = new Shader("../../content/sphereVert.glsl", "../../content/sphereFrag.glsl");
        mShader->Use();

        glGenVertexArrays(1, &mVertexArray);
        glBindVertexArray(mVertexArray);

		glGenBuffers(1, &mVertexBuffer);
		glGenBuffers(1, &mIndexBuffer);

        // Create the sphere vertices

        int samples = mStacks;
        float radius = 1.0;
        int definition = mSlices;

        // Sphere vertices
        std::vector<vec3> vertices;
        // Sphere indices
        std::vector<GLushort> indices;

        float dArc = glm::pi<float>() / samples;
		for(int i = 0; i < samples+1; i++)
        {
            float phi = -glm::pi<float>() + i*dArc;
            float h = cos(phi);
            float r = radius * sin(phi);
            for(int j = 0; j < definition+1; j++)
            {
                float theta = -j * (2.0f * glm::pi<float>() / definition);
                vec3 n(r*std::cos(theta), h, r*std::sin(theta));

                vertices.push_back(n);
                if(i > 0 && j > 0)
                {
                    indices.push_back((i-1)*(definition+1) + j-1);
                    indices.push_back((i-1)*(definition+1) + j);
                    indices.push_back( i*(definition+1) + j);

                    indices.push_back((i-1)*(definition+1) + j-1);
                    indices.push_back( i*(definition+1) + j);
                    indices.push_back( i*(definition+1) + j-1);
                }
            }
        }

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*indices.size(), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		mIndexNumber = indices.size();


        mPositionLocation = mShader->GetAttribute(ShaderAttributesPosition);
        mMVPUniform = mShader->GetUniform("MVP");
        mMVUniform = mShader->GetUniform("MV");

        mOffsetUniform = mShader->GetUniform("offset");
        mColorUniform = mShader->GetUniform("uColor");
        mRadiusUniform = mShader->GetUniform("radius");

        mShader->Use();
        glBindVertexArray(mVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

		glVertexAttribPointer(
			mPositionLocation,
			3,
			GL_FLOAT,
			GL_FALSE,
			(0),
			(void*) 0
			);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

        mTransform.Scale(0.002f);
    }

    void DrawableSpheres::Draw(const RendererTime& rendererTime)
    {
        mTransform.UpdateCameraMatrix(*mCamera);

        mShader->Use();
		const mat4 &MVP = mTransform.LocalToScreenMatrix();
		const mat4 &MV = mTransform.LocalToViewMatrix();

		glUniformMatrix4fv(mMVPUniform, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(mMVUniform, 1, GL_FALSE, &MV[0][0]);
		//glUniform3f(mShader->GetUniform("offset"), mSphereData[0], mSphereData[1], mSphereData[2]);

        glBindVertexArray(mVertexArray);

		glEnableVertexAttribArray(mPositionLocation);

		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

        int spheres = mSphereData.size()/7;
        for(int i = 0; i < spheres; i++)
        {
            glUniform3f(mOffsetUniform, mSphereData[i*7 + 0], mSphereData[i*7 + 1], mSphereData[i*7 + 2]);
            glUniform3f(mColorUniform, mSphereData[i*7 + 3], mSphereData[i*7 + 4], mSphereData[i*7 + 5]);
            glUniform1f(mRadiusUniform, mSphereData[i*7 + 6]);
            glDrawElements(GL_TRIANGLES, mIndexNumber, GL_UNSIGNED_SHORT, 0);
        }

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(mPositionLocation);

		glBindVertexArray(0);
		glUseProgram(0);


    }

    void DrawableSpheres::Upload()
    {
        glBindBuffer(GL_ARRAY_BUFFER, mSphereDataBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mSphereData.size(), NULL, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*mSphereData.size(), mSphereData.data());
    }

    void DrawableSpheres::PushSphere(vec3 position, vec3 color, float radius)
    {
        mSphereData.push_back(position.x);
        mSphereData.push_back(position.y);
        mSphereData.push_back(position.z);
        mSphereData.push_back(color.x);
        mSphereData.push_back(color.y);
        mSphereData.push_back(color.z);
        mSphereData.push_back(radius);
        mTotalSpheres++;
    }

    void DrawableSpheres::PopSphere()
    {
        for(int i = 0; i < 7; i++)
        {
            mSphereData.pop_back();
        }
        mTotalSpheres--;
    }

    void DrawableSpheres::UpdateSpherePosition(int index, vec3 position)
    {
        mSphereData[7*index] = position.x;
        mSphereData[7*index+1] = position.y;
        mSphereData[7*index+2] = position.z;
    }
    void DrawableSpheres::TraslateSpherePosition(int index, vec3 position)
    {
        mSphereData[7*index] += position.x;
        mSphereData[7*index+1] += position.y;
        mSphereData[7*index+2] += position.z;
    }
    void DrawableSpheres::UpdateSphereColor(int index, vec3 color)
    {
        mSphereData[7*index+3] = color.x;
        mSphereData[7*index+4] = color.y;
        mSphereData[7*index+5] = color.z;
    }
    void DrawableSpheres::DeleteSphereAt(int index)
    {
        if(index < 0 || index >= (int)mSphereData.size()/7) return;

        std::vector<float>::iterator iter = mSphereData.begin()+7*index;
        for(int i = 0; i < 7; i++)
        {
            iter = mSphereData.erase(iter);
        }
        mTotalSpheres--;
    }

}
