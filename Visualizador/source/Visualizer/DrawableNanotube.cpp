#include "DrawableNanotube.h"
#include "Shader.h"
#include "RendererTime.h"
#include "Camera.h"
#include "Material.h"

#include <iostream>

#include <cstdlib>
#include <cmath>
#include <ctime>

namespace Library
{
	RTTI_DEFINITIONS(DrawableNanotube)

	DrawableNanotube::DrawableNanotube(Renderer& renderer, Camera& camera, CatmullRom* interpolator, NanotubeMaterial* solidMaterial, double radius) :
	    DrawableComponent(renderer, camera),
        mInterpolator(interpolator),
        mTransform(),
        mVertexData(),
        mIndexData(),
        mSolidMaterial(solidMaterial),
        mVertexBuffer(0),
        mIndexBuffer(0),
        mVertexArray(0),
        mDrawLine(false),
        mRadius(radius)
	{
	}

	DrawableNanotube::~DrawableNanotube()
	{
		glDeleteBuffers(1, &mVertexBuffer);
		glDeleteBuffers(1, &mIndexBuffer);
		glDeleteVertexArrays(1, &mVertexArray);

		delete mInterpolator;
		//delete mNormalTexture;
		//delete mWireTexture;
	}

	const Transform& DrawableNanotube::GetTransform() const
	{
        return mTransform;
	}

	vec3 DrawableNanotube::StartPosition() const
	{
        return mStartPosition;
	}

	void DrawableNanotube::Initialize()
	{
		glGenVertexArrays(1, &mVertexArray);

		glGenBuffers(1, &mVertexBuffer);
		glGenBuffers(1, &mIndexBuffer);

        mColor = vec3(rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX));
        //Remove cores proximas do vermelho
        while(mColor.x >= 0.8 && mColor.y <= 0.30 && mColor.z <= 0.30)
        {
            mColor = vec3(rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX));
        }

        BuildNanotubes();

        mTransform.Scale(0.002);

        mSolidMaterial->Setup(*this);

		// Calculate the start position of the spline
		mStartPosition = vec3(vec4(mInterpolator->vPointAt(0.0f), 1.0) * mTransform.LocalToWorldMatrix());
	}


	void DrawableNanotube::Draw(const RendererTime& rendererTime)
	{
		mTransform.UpdateCameraMatrix(*mCamera);
		mSolidMaterial->SetColor(mColor);

        // Bug no shader com linha, tendo que usar modo imediato
        if(mDrawLine)
        {
            glDisable(GL_DEPTH_TEST);
            glEnable (GL_CULL_FACE);
            glEnable (GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            mSolidMaterial->Use(rendererTime, *this);
            glDisable(GL_BLEND);

            glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf(&mTransform.LocalToScreenMatrix()[0][0]);

            auto cPoints = mInterpolator->ControlPoints();

            glBegin(GL_LINE_STRIP);

            // Volta a cor da linha do nanotubo
            glColor3fv(&mColor[0]);

            //float dArc = mInterpolator->ArcLength() / samples;
            //for(int i = 0; i < samples; i++)
            for(unsigned int i = 1; i < cPoints.size()-1; i++) /// LILIANE não desenha o ultimo ponto pois ele não faz parte dos dados do CNT salvos no arquivo
            {
                //vec3 p = mInterpolator->vPointAt(i * dArc);
                vec3 p(cPoints[i].x, cPoints[i].y, cPoints[i].z);
                glVertex3fv(&p[0]);
            }
            glEnd();
            /// Desenhando splines em linhas
            /*glBegin(GL_LINE_STRIP);

            // Volta a cor da linha do nanotubo
            glColor3fv(&mColor[0]);

            // Primeiro ponto
            vec3 p(cPoints[1].x, cPoints[1].y, cPoints[1].z);
            glVertex3fv(&p[0]);

            int samples = 10; // 10 pontos amostrados em cada segmento
            for(int i = 1; i < cPoints.size()-2; i++)
            {
                float arcPos1 = mInterpolator->ArcPosition(i);
                float arcPos2 = mInterpolator->ArcPosition(i+1);
                float dArc = (arcPos2-arcPos1) / samples;
                for(int i = 1; i < samples; i++)
                {
                    vec3 p = mInterpolator->vPointAt((i * dArc)+arcPos1);
                    glVertex3fv(&p[0]);
                }
            }
            // ultimo ponto
            p.x = cPoints[cPoints.size()-2].x;
            p.y = cPoints[cPoints.size()-2].y;
            p.z = cPoints[cPoints.size()-2].z;
            glVertex3fv(&p[0]);
            glEnd();*/

            glPopMatrix();
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);
            mSolidMaterial->Use(rendererTime, *this);
        }
	}

	void DrawableNanotube::BuildNanotubes()
	{
        //float color = 0.8;//rand() / static_cast<float>(RAND_MAX);

        int samples = 10 * (mInterpolator->ControlPointsNumber()-2);
        double radius = mRadius;
        int definition = 16;
        mTilling = 1.0f;

        float dArc = mInterpolator->ArcLength() / samples;

		for(int i = 0; i < samples; i++)
        {
            mat4 tMatrix = mInterpolator->TransformMatrix(i * dArc);

            for(int j = 0; j < definition+1; j++)
            {
                float theta = -j * (2.0f * glm::pi<float>() / definition);
                vec3 n(radius*std::cos(theta), 0.0, radius*std::sin(theta));
                vec4 p;
                p = vec4(n, 1.0) * tMatrix;
                n = vec3(vec4(n, 0.0) * tMatrix);


                // Flat the bottom of the cylinder
                if(i == 0) p.y = 0;

                mVertexData.push_back(vec3(p));
                mVertexData.push_back(normalize(n));

                bool overlap = false;
                for(unsigned int k = 0; k < mOverlapSegments.size() / 2; k++)
                {
                    if(i * dArc >= mOverlapSegments[k*2] && i * dArc <=  mOverlapSegments[k*2+1])
                    {
                        //mVertexData.push_back(vec3(1.0f, 0.0f, 0.0f)); ///ALLAN
                        mVertexData.push_back(mOverlapColor[k]);
                        overlap = true;
                        break;
                    }
                }
                if(!overlap)
                    mVertexData.push_back(/*mColor*/ vec3(0.8));

                mVertexData.push_back(vec3(i*((dArc / 10.0f)), j*(8.0f / (float)definition), 0.0f));
                if(i > 0 && j > 0)
                {
                    mIndexData.push_back((i-1)*(definition+1) + j-1);
                    mIndexData.push_back((i-1)*(definition+1) + j);
                    mIndexData.push_back( i*(definition+1) + j);

                    mIndexData.push_back((i-1)*(definition+1) + j-1);
                    mIndexData.push_back( i*(definition+1) + j);
                    mIndexData.push_back( i*(definition+1) + j-1);
                }
            }
        }


		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * mVertexData.size(), 0, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * mVertexData.size(), mVertexData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*mIndexData.size(), 0, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*mIndexData.size(), mIndexData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		mIndexNumber = mIndexData.size();
		mIndexData.clear();
		mVertexData.clear();
	}


	bool DrawableNanotube::DrawLine() const
	{
        return mDrawLine;
	}

    void DrawableNanotube::SetDrawLine(bool drawLine)
    {
        mDrawLine = drawLine;
    }

    void DrawableNanotube::AddOverlapPoint(int index, vec3 color)
    {
        float aMin = mInterpolator->ArcPosition(index-1);
        float aMax = mInterpolator->ArcPosition(index);

        mOverlapSegments.push_back(aMin);
        mOverlapSegments.push_back(aMax);
        mOverlapColor.push_back(color);

        mNeedUpdate = true;
    }

    void DrawableNanotube::ClearOverlapPoints()
    {
        mOverlapSegments.clear();
        mOverlapColor.clear();
        mNeedUpdate = true;
    }

    void DrawableNanotube::Update(const RendererTime& rendererTime)
    {
        if(mNeedUpdate)
        {
            BuildNanotubes();
            mNeedUpdate = false;
        }
    }

    double DrawableNanotube::Radius() const
    {
        return mRadius;
    }
    void DrawableNanotube::NeedUpdate(bool needUpdate)
    {
        mNeedUpdate = needUpdate;
    }

}

