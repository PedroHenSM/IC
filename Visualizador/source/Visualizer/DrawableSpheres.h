#pragma once

#include "DrawableComponent.h"
#include "Shader.h"
#include "Transform.h"

namespace Library
{
    class DrawableSpheres : public DrawableComponent
    {
        RTTI_DECLARATIONS(DrawableSpheres, DrawableComponent)

    public:
        DrawableSpheres(Renderer& renderer, Camera& camera, int slices = 6, int stacks = 4);
        ~DrawableSpheres();

        void Initialize() override;
        void Draw(const RendererTime& rendererTime) override;

        void Upload();

        void PushSphere(vec3 position, vec3 color, float radius);

        void PopSphere();

        int GetTotalSpheres() { return mTotalSpheres; }

        void UpdateSpherePosition(int index, vec3 position);
        void TraslateSpherePosition(int index, vec3 position);
        void UpdateSphereColor(int index, vec3 color);
        void DeleteSphereAt(int index);

    private:
        std::vector<float> mSphereData;

        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        GLuint mVertexArray;
        GLuint mIndexNumber;

        GLuint mSphereDataArray;
        GLuint mSphereDataBuffer;

        Shader *mShader;
        GLuint mPositionLocation;
        GLuint mOffsetLocation;
        GLuint mColorLocation;
        GLuint mMVPUniform;
        GLuint mMVUniform;
        GLuint mOffsetUniform;
        GLuint mColorUniform;
        GLuint mRadiusUniform;

        Transform mTransform;

        int mSlices;
        int mStacks;

        int mTotalSpheres;


        //Temporario
        GLUquadric* mShape;

    };
}
