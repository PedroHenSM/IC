#pragma once

#include "RendererComponent.h"

namespace Library
{
	class Camera : public RendererComponent
	{
		RTTI_DECLARATIONS(Camera, RendererComponent)

	public:
		Camera(Renderer& renderer);
		Camera(Renderer& renderer, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

		virtual ~Camera();

		const bool HasChanged() const;
		void SetHasChanged(bool hasChanged);

		const vec3& Position() const;
		const vec3& Direction() const;
		const vec3& Up() const;
		const vec3& Right() const;

		float AspectRatio() const;
		void SetAspectRatio(float aspectRatio);
		float FieldOfView() const;
		float NearPlaneDistance() const;
		float FarPlaneDistance() const;

		mat4 ViewMatrix() const;
		mat4 ProjectionMatrix() const;
		mat4 ViewProjectionMatrix() const;

		virtual void SetPosition(float x, float y, float z);
		virtual void SetPosition(const vec3& position);

		virtual void Reset();
		virtual void Initialize() override;
		virtual void Update(const RendererTime& rendererTime) override;
		virtual void UpdateViewMatrix();
		virtual void UpdateProjectionMatrix();
		virtual void UpdateViewProjectionMatrix();

		void ApplyRotation(const mat4& transform);

		static const float DefaultFieldOfView;
		static const float DefaultNearPlaneDistance;
		static const float DefaultFarPlaneDistance;

	protected:
		float mFieldOfView;
		float mAspectRatio;
		float mNearPlaneDistance;
		float mFarPlaneDistance;

		vec3 mPosition;
		vec3 mDirection;
		vec3 mUp;
		vec3 mRight;

		mat4 mViewMatrix;
		mat4 mProjectionMatrix;
		mat4 mViewProjectionMatrix;

		bool mCameraHasChanged;

		bool mViewMatrixNeedUpdate;
		bool mProjectionMatrixNeedUpdate;

	private:
		Camera();
		Camera(const Camera& rhs);
		Camera& operator=(const Camera& rhs);
	};
}
