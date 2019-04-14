#include "Camera.h"
#include "RendererTime.h"
#include "Renderer.h"

namespace Library
{
	RTTI_DEFINITIONS(Camera)

	const float Camera::DefaultFieldOfView = glm::quarter_pi<float>();
	const float Camera::DefaultNearPlaneDistance = 0.001f;
	const float Camera::DefaultFarPlaneDistance = 1000.0f;

	Camera::Camera(Renderer& renderer)
		: RendererComponent(renderer),
		mFieldOfView(DefaultFieldOfView), mAspectRatio(renderer.AspectRatio()), mNearPlaneDistance(DefaultNearPlaneDistance), mFarPlaneDistance(DefaultFarPlaneDistance),
		mPosition(), mDirection(), mUp(), mRight(), mViewMatrix(1.0), mProjectionMatrix(1.0), mViewProjectionMatrix(1.0),
		mCameraHasChanged(false), mViewMatrixNeedUpdate(false), mProjectionMatrixNeedUpdate(false)
	{}

	Camera::Camera(Renderer& renderer, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
		: RendererComponent(renderer),
		mFieldOfView(fieldOfView), mAspectRatio(aspectRatio), mNearPlaneDistance(nearPlaneDistance), mFarPlaneDistance(farPlaneDistance),
		mPosition(), mDirection(), mUp(), mRight(), mViewMatrix(1.0), mProjectionMatrix(1.0), mViewProjectionMatrix(1.0),
		mCameraHasChanged(false), mViewMatrixNeedUpdate(false), mProjectionMatrixNeedUpdate(false)
	{}

	Camera::~Camera()
	{}

	const bool Camera::HasChanged() const
	{
		return mCameraHasChanged;
	}

	void Camera::SetHasChanged(bool hasChanged)
	{
		mCameraHasChanged = hasChanged;
	}

	const vec3 & Camera::Position() const
	{
		return mPosition;
	}

	const vec3 & Camera::Direction() const
	{
		return mDirection;
	}

	const vec3 & Camera::Up() const
	{
		return mUp;
	}

	const vec3 & Camera::Right() const
	{
		return mRight;
	}

	float Camera::AspectRatio() const
	{
		return mAspectRatio;
	}

	float Camera::FieldOfView() const
	{
		return mAspectRatio;
	}

	float Camera::NearPlaneDistance() const
	{
		return mNearPlaneDistance;
	}

	float Camera::FarPlaneDistance() const
	{
		return mFarPlaneDistance;
	}

	mat4 Camera::ViewMatrix() const
	{
		return mViewMatrix;
	}

	mat4 Camera::ProjectionMatrix() const
	{
		return mProjectionMatrix;
	}

	mat4 Camera::ViewProjectionMatrix() const
	{
		return mViewProjectionMatrix;
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		mPosition = vec3(x, y, z);
		mViewMatrixNeedUpdate = true;
	}

	void Camera::SetPosition(const vec3 & position)
	{
		mPosition = position;
		mViewMatrixNeedUpdate = true;
	}

	void Camera::Reset()
	{
		mPosition = vec3(0.0f, 0.0f, 0.0f);
		mDirection = vec3(0.0f, 0.0f, -1.0f);
		mUp = vec3(0.0f, 1.0f, 0.0f);
		mRight = vec3(1.0f, 0.0f, 0.0f);

		UpdateViewMatrix();
		UpdateViewProjectionMatrix();
	}

	void Camera::Initialize()
	{
		UpdateProjectionMatrix();
		Reset();
	}

	void Camera::Update(const RendererTime & rendererTime)
	{
		if (mViewMatrixNeedUpdate)
		{
			UpdateViewMatrix();
			if (!mProjectionMatrixNeedUpdate)
			{
				UpdateViewProjectionMatrix();
			}
		}
		if (mProjectionMatrixNeedUpdate)
		{
			UpdateProjectionMatrix();
			UpdateViewProjectionMatrix();
		}
	}

	void Camera::UpdateViewMatrix()
	{
	    vec3 focus = mPosition + mDirection;
		mViewMatrix = lookAt(mPosition, focus, mUp);
		mViewMatrixNeedUpdate = false;
	}

	void Camera::UpdateProjectionMatrix()
	{
		mProjectionMatrix = perspectiveFov(mFieldOfView, (float)mRenderer->ScreenWidth(), (float)mRenderer->ScreenHeight(), mNearPlaneDistance, mFarPlaneDistance);
		mProjectionMatrixNeedUpdate = false;
	}

	void Camera::UpdateViewProjectionMatrix()
	{
		mat4 viewMat(mViewMatrix);
		mat4 projectionMat(mProjectionMatrix);

		mViewProjectionMatrix = (projectionMat * viewMat);

		mCameraHasChanged = true;
	}

	void Camera::ApplyRotation(const mat4 & transform)
	{
		vec3 direction(mDirection);
		vec3 up(mUp);

		direction = normalize(vec3(transform * vec4(direction, 0.0f)));
		up = normalize(vec3(transform * vec4(up, 0.0f)));

		vec3 right = cross(direction, up);

		mDirection = direction;
		mUp = up;
		mRight = right;

		mViewMatrixNeedUpdate = true;
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
	    mAspectRatio = aspectRatio;
	    UpdateProjectionMatrix();
	    UpdateViewProjectionMatrix();
	}

}
