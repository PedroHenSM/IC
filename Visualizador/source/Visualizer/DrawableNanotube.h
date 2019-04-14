#pragma once

#include "DrawableComponent.h"
#include "NanotubeMaterial.h"
//#include "LineMaterial.h"
#include "Transform.h"
#include "CatmullRom.h"
#include "Texture.h"

namespace Library
{
	class Shader;
	class NanotubeMaterial;
	class LineMaterial;

	class DrawableNanotube : public DrawableComponent
	{
        friend class NanotubeMaterial;
        friend class LineMaterial;

		RTTI_DECLARATIONS(DrawableNanotube, DrawableComponent)

	public:
		DrawableNanotube(Renderer& renderer, Camera& camera, CatmullRom* interpolator, NanotubeMaterial* solidMaterial, double radius);
		~DrawableNanotube();

		void Initialize() override;
		void Draw(const RendererTime& rendererTime) override;

		bool DrawLine() const;
		void SetDrawLine(bool drawLine);

		const Transform& GetTransform() const;

		double Radius() const;
		void AddOverlapPoint(int index, vec3 color = vec3(1, 0, 0));
		void ClearOverlapPoints();
		void Update(const RendererTime& rendererTime);
        void NeedUpdate(bool needUpdate);

		vec3 StartPosition() const;

		CatmullRom *mInterpolator;
        void BuildNanotubes();

	private:
        void BuildLines();

		Transform mTransform;
		std::vector<vec3> mVertexData;
		std::vector<GLushort> mIndexData;

        NanotubeMaterial* mSolidMaterial;

		Texture* mNormalTexture;
		Texture* mWireTexture;

		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLuint mVertexArray;
		GLuint mIndexNumber;

		float mTilling;

		bool mDrawLine;

		vec3 mStartPosition;

		float mRadius;

		/// ALLAN - TEMPORARIO
		vec3 mColor;
		std::vector<float> mOverlapSegments;
		std::vector<vec3> mOverlapColor;
		bool mNeedUpdate;

	};
}
