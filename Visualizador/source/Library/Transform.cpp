#include "Transform.h"
#include "Camera.h"
#include "VectorHelper.h"

namespace Library
{
	Transform::Transform()
		: mPosition(0), mScale(1), mRotation(),
		mForward(VectorHelper::Forward), mRight(VectorHelper::Right), mUp(VectorHelper::Up),
		mMatrixNeedUpdate(false), mLocalToWorldMatrix(1.0), mLocalToViewMatrix(1.0), mLocalToScreenMatrix(1.0)
	{
	}

	Transform::Transform(vec3 position)
		: mPosition(position), mScale(1), mRotation(),
		  mForward(VectorHelper::Forward), mRight(VectorHelper::Right), mUp(VectorHelper::Up), mMatrixNeedUpdate(false),
		  mLocalToWorldMatrix(translate(mat4(1.0),position)), mLocalToViewMatrix(mLocalToWorldMatrix), mLocalToScreenMatrix(mLocalToWorldMatrix)
	{
	}

	Transform::Transform(vec3 position, vec3 eulerAngles)
		: mPosition(position), mScale(1), mRotation(eulerAngles),
		  mForward(VectorHelper::Forward), mRight(VectorHelper::Right), mUp(VectorHelper::Up), mMatrixNeedUpdate(false),
		  mLocalToWorldMatrix(1.0), mLocalToViewMatrix(1.0), mLocalToScreenMatrix(1.0)
	{
		UpdateMatrix();
	}

	Transform::Transform(vec3 position, quat rotation)
		: mPosition(position), mScale(1), mRotation(rotation),
		  mForward(VectorHelper::Forward), mRight(VectorHelper::Right), mUp(VectorHelper::Up), mMatrixNeedUpdate(false),
		  mLocalToWorldMatrix(1.0), mLocalToViewMatrix(1.0), mLocalToScreenMatrix(1.0)
	{
		UpdateMatrix();
	}

	Transform::Transform(vec3 position, vec3 eulerAngles, vec3 scale)
		: mPosition(position), mScale(scale), mRotation(eulerAngles),
		  mForward(VectorHelper::Forward), mRight(VectorHelper::Right), mUp(VectorHelper::Up), mMatrixNeedUpdate(false),
		  mLocalToWorldMatrix(1.0), mLocalToViewMatrix(1.0), mLocalToScreenMatrix(1.0)
	{
		UpdateMatrix();
	}

	Transform::Transform(vec3 position, quat rotation, vec3 scale)
		: mPosition(position), mScale(scale), mRotation(rotation),
		  mForward(VectorHelper::Forward), mRight(VectorHelper::Right), mUp(VectorHelper::Up), mMatrixNeedUpdate(false),
		  mLocalToWorldMatrix(1.0), mLocalToViewMatrix(1.0), mLocalToScreenMatrix(1.0)
	{
		UpdateMatrix();
	}

	Transform::~Transform()
	{
	}

	void Transform::Translate(vec3 translation)
	{
		mPosition += translation;
		mMatrixNeedUpdate = true;
	}

	void Transform::SetPosition(vec3 position)
	{
		mPosition = position;
		mMatrixNeedUpdate = true;
	}

	vec3 Transform::GetPosition() const
	{
		return mPosition;
	}

	void Transform::Scale(vec3 scale)
	{
	    mScale *= scale;
	    mMatrixNeedUpdate = true;
	}

	void Transform::Scale(float scale)
	{
	    mScale *= scale;
	    mPosition *= scale;
	    mMatrixNeedUpdate = true;
	}

	void Transform::Rotate(const vec3& eulerAngles)
	{
		mRotation = quat(eulerAngles * VectorHelper::DegreeToRadian) * mRotation;
		mMatrixNeedUpdate = true;
	}

	void Transform::Rotate(const quat& rotation)
	{
		mRotation = rotation * mRotation;
		mMatrixNeedUpdate = true;
	}

	void Transform::SetRotation(const vec3& eulerAngles)
	{
		mRotation = quat(eulerAngles);
		mMatrixNeedUpdate = true;
	}

	void Transform::SetRotation(const quat& rotation)
	{
		mRotation = rotation;
		mMatrixNeedUpdate = true;
	}

	quat Transform::GetRotation() const
	{
		return mRotation;
	}

	vec3 Transform::GetEulerAngles() const
	{
		return eulerAngles(mRotation);
	}

	void Transform::LookAt(vec3 center)
	{
		quat rotation = VectorHelper::RotationFromTo(mForward, center - mPosition);
		mRotation *= rotation;
		UpdateMatrix();
	}

	void Transform::RotateAround(vec3 center, vec3 axis, float angle)
	{
		angle *= 0.01745329251994329576923690768489f;
		vec4 distance = vec4(mPosition - center, 0.0f);
		mat4 rotate = glm::rotate(mat4(), angle, axis);

		mPosition = vec3(rotate * distance) + center;
		mRotation = glm::rotate(mRotation, angle, axis);
		UpdateMatrix();
	}

	const mat4 & Transform::LocalToWorldMatrix()
	{
		if (mMatrixNeedUpdate)
			UpdateMatrix();

		return mLocalToWorldMatrix;
	}

	const mat4 & Transform::LocalToViewMatrix()
	{
		return mLocalToViewMatrix;
	}

	const mat4 & Transform::LocalToScreenMatrix()
	{
		return mLocalToScreenMatrix;
	}

	void Transform::UpdateCameraMatrix(Camera & camera)
	{
		if (mMatrixNeedUpdate)
			UpdateMatrix();

		mLocalToViewMatrix = camera.ViewMatrix() * mLocalToWorldMatrix;
		mLocalToScreenMatrix = camera.ProjectionMatrix() * mLocalToViewMatrix;
	}


	void Transform::UpdateMatrix()
	{
		mat4 lScale = scale(mat4(1.0), mScale);
		mat4 lTranslation(translate(mat4(1.0), mPosition));
		mat4 lRotation = mat4(mRotation);

		mat3 rotationMatrix = mat3(lRotation);
		mRight = rotationMatrix * mRight;
		mUp = rotationMatrix * mUp;
		mForward = rotationMatrix * mForward;

		mLocalToWorldMatrix = lTranslation*lRotation*lScale;
		mMatrixNeedUpdate = false;
	}

}
